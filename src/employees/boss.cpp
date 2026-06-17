#include "employees/boss.h"
#include <algorithm>
#include <chrono>
#include <fstream>
#include <iostream>
#include "core/company.h"
#include "core/simulation_time.h"
#include "events/event.h"
#include "events/event_types.h"
#include "statistics/statistic.h"

using namespace std::chrono;

Boss::Boss(std::string bossName, std::string bossSurname, Company& comp)
    : Employee(std::move(bossName), std::move(bossSurname), Role::Boss, milliseconds(0), milliseconds(0))
    , company{ comp }
{
}

void Boss::Print() { std::cout << *this << std::endl; }

void Boss::Hire(std::unique_ptr<Employee>&& employee) { company.AddEmployee(std::move(employee)); }
void Boss::Hire(std::unique_ptr<Employee>& employee) { company.AddEmployee(std::move(employee)); }
void Boss::AddTask(std::unique_ptr<Event> event) { company.AddEvent(std::move(event)); }

std::list<std::unique_ptr<Employee>>::iterator Boss::FindFreeEmployeeByRole(Role role) {
    return std::find_if(
        company.GetEmployees().begin(),
        company.GetEmployees().end(),
        [role](const std::unique_ptr<Employee>& employee) {
            return employee->GetRole() == role && !employee->GetBusy();
        });
}

Role Boss::RequiredRoleForEvent(const Event& event) const {
    switch (event.GetType()) {
    case TypeEvent::BusinessTrip:
    case TypeEvent::PrintRequest:
        return Role::AutoMemoryDoll;
    case TypeEvent::DeliveryRequest:
        return Role::MailMan;
    default:
        return Role::AutoMemoryDoll;
    }
}

milliseconds Boss::CalculateRealTaskDuration(const Employee& employee, const Event& event) const {
    const int unitsToProcess = 1;
    const auto simulatedWorkTime = employee.GetMinutesPerLetter() * unitsToProcess;
    auto simulatedTotal = duration_cast<seconds>(simulatedWorkTime);

    if (event.GetType() == TypeEvent::BusinessTrip) {
        simulatedTotal += event.GetDuration();
    }

    return SimTime::ToReal(simulatedTotal);
}

void Boss::ProcessCompletedTasks(Statistic& statistic) {
    std::vector<std::unique_ptr<Event>> remainingEvents;

    for (auto& employee : company.GetEmployees()) {
        employee->UpdateBusyStatus();

        if (!employee->HasCompletedTask()) {
            continue;
        }

        auto completedEvent = employee->TakeCompletedTask();
        if (!completedEvent) {
            continue;
        }

        // Командировка выполнена целиком
        if (completedEvent->GetType() == TypeEvent::BusinessTrip) {
            statistic.AddSuccess(completedEvent.get(), employee.get());
            employee->SetOnBusinessTrip(false, "");
            std::cout << "[TRIP DONE] " << employee->GetFullName()
                << " returned from: " << completedEvent->GetDescription() << std::endl;
            continue;
        }

        // Обычные задачи: выполнена 1 единица
        int remainingQuantity = completedEvent->GetQuantity() - 1;

        if (remainingQuantity > 0) {
            auto remainingEvent = completedEvent->CreateWithQuantity(remainingQuantity);
            if (remainingEvent) {
                remainingEvents.push_back(std::move(remainingEvent));
                std::cout << "[PARTIAL] " << employee->GetFullName()
                    << " completed 1 unit, " << remainingQuantity
                    << " units remaining" << std::endl;
            }
        }

        // в статистику добавляем только 1 выполненную единицу
        auto completedUnit = completedEvent->CreateWithQuantity(1);
        statistic.AddSuccess(completedUnit.get(), employee.get());

        std::cout << "[DONE] " << employee->GetFullName()
            << " finished 1 unit of: " << completedEvent->GetDescription() << std::endl;
    }

    for (auto& event : remainingEvents) {
        std::string desc = event->GetDescription();
        company.AddEvent(std::move(event));
        std::cout << "[REMAINING] Added back to queue: " << desc << std::endl;
    }
}

bool Boss::TryAssignNextEvent() {
    if (company.GetEvents().empty()) {
        return false;
    }

    const Event& nextEvent = *company.GetEvents().top();
    const Role requiredRole = RequiredRoleForEvent(nextEvent);
    const auto employeeIt = FindFreeEmployeeByRole(requiredRole);

    if (employeeIt == company.GetEmployees().end()) {
        return false;
    }

    auto task = company.TakeNextEvent();
    const auto realDuration = CalculateRealTaskDuration(**employeeIt, *task);

    std::cout << "[ASSIGN] " << (*employeeIt)->GetFullName()
        << " -> " << task->GetDescription()
        << " (real " << realDuration.count() << " ms)" << std::endl;

    if (task->GetType() == TypeEvent::BusinessTrip) {
        auto* trip = dynamic_cast<BusinessTrip*>(task.get());
        if (trip) {
            (*employeeIt)->SetOnBusinessTrip(true, trip->GetLocation());
        }
    }

    (*employeeIt)->StartTask(std::move(task), realDuration);
    return true;
}

void Boss::ProcessSimulationTick(Statistic& statistic) {
    ProcessCompletedTasks(statistic);
    while (TryAssignNextEvent()) {}
}

void Boss::CollectFailedTasks(Statistic& statistic) {
    // 1. Переносим все задачи из очереди на следующий день
    std::vector<std::unique_ptr<Event>> pendingTasks;
    while (!company.GetEvents().empty()) {
        auto event = company.TakeNextEvent();
        pendingTasks.push_back(std::move(event));
    }

    for (auto& task : pendingTasks) {
        std::string desc = task->GetDescription();
        company.AddEvent(std::move(task));
        std::cout << "[PENDING] " << desc << " carried over to next day" << std::endl;
    }

    // 2. Обрабатываем задачи сотрудников
    for (auto& employee : company.GetEmployees()) {
        if (employee->GetCurrentEvent() == nullptr) {
            continue;
        }

        // Командировка продолжается
        if (employee->GetCurrentEvent()->GetType() == TypeEvent::BusinessTrip) {
            statistic.employeesOnTrip.push_back(employee->GetFullName());
            std::cout << "[TRIP CONTINUES] " << employee->GetFullName()
                << " is still on business trip: "
                << employee->GetCurrentEvent()->GetDescription() << std::endl;
            continue;
        }

        // PrintRequest / DeliveryRequest — failed
        const std::string description = employee->GetCurrentEvent()->GetDescription();
        int remaining = employee->GetCurrentEvent()->GetQuantity();

        statistic.AddFailedTask(
            description + " (remaining: " + std::to_string(remaining) + " units)");
        std::cout << "[FAILED] " << description
            << " (" << employee->GetFullName()
            << ", remaining: " << remaining << " units)" << std::endl;

        auto event = employee->TakeCompletedTask();
        if (event && event->GetQuantity() > 0) {
            std::string desc = event->GetDescription();
            company.AddEvent(std::move(event));
            std::cout << "[PENDING] " << desc << " returned to queue" << std::endl;
        }
    }
}

void Boss::WriteDailyStatistic(int day, const Statistic& report)
{
    std::ofstream file("hodgins_journal.txt", std::ios::app);
    file << "========================================\n";
    file << "DAY " << day << " REPORT\n";
    file << "========================================\n\n";

    file << "  STATISTICS:\n";
    file << "  Letters written:    " << report.lettersWritten << "\n";
    file << "  Letters delivered:  " << report.lettersDelivered << "\n";
    file << "  Business trips:     " << report.businessTrip << "\n";
    file << "  Failed tasks:       " << report.failedTask.size() << "\n\n";

    // Вывод прогресса по сотрудникам (без C++17 structured bindings)
    file << "  EMPLOYEE PROGRESS:\n";
    for (auto it = report.employeeStats.begin(); it != report.employeeStats.end(); ++it) {
        const std::string& empName = it->first;
        const EmployeeStatistic& empStat = it->second;
        file << "  - " << empName << ":\n";
        file << "      Letters written:   " << empStat.lettersWritten << "\n";
        file << "      Letters delivered: " << empStat.lettersDelivered << "\n";
        file << "      Business trips:    " << empStat.businessTrips << "\n";
        if (!empStat.tripLocations.empty()) {
            file << "      Trip locations:    ";
            for (size_t i = 0; i < empStat.tripLocations.size(); ++i) {
                file << empStat.tripLocations[i];
                if (i < empStat.tripLocations.size() - 1) file << ", ";
            }
            file << "\n";
        }
    }
    file << "\n";

    file << "  EMPLOYEES ON TRIP:\n";
    if (report.employeesOnTrip.empty()) {
        file << "  None\n";
    }
    else {
        for (const auto& name : report.employeesOnTrip) {
            file << "  - " << name << "\n";
        }
    }

    file << "\n  FAILED TASKS:\n";
    if (report.failedTask.empty()) {
        file << "  None\n";
    }
    else {
        for (const auto& task : report.failedTask) {
            file << "  - " << task << "\n";
        }
    }

    file << "\n========================================\n\n";
}