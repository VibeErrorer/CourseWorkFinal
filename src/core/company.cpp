#include "core/company.h"
#include <algorithm>
#include <chrono>
#include <fstream>
#include <iostream>
#include <thread>
#include "core/simulation_time.h"
#include "statistics/statistic.h"

bool CompareEvents::operator()(const std::unique_ptr<Event>& first,
    const std::unique_ptr<Event>& second) const {
    if (!first && !second) return false;
    if (!first) return true;
    if (!second) return false;
    return static_cast<int>(first->GetType()) > static_cast<int>(second->GetType());
}

Company::Company(std::string companyName, std::string bossName, std::string bossSurname)
    : name{ std::move(companyName) } 
{
    boss = std::make_unique<Boss>(bossName, bossSurname, *this);
}

std::string Company::GetName() const { return name; }

std::list<std::unique_ptr<Employee>>& Company::GetEmployees() { return employees; }

std::priority_queue<std::unique_ptr<Event>,
    std::vector<std::unique_ptr<Event>>, CompareEvents>& Company::GetEvents() { return events; }

void Company::AddEmployee(std::unique_ptr<Employee> employee) {
    employees.push_back(std::move(employee));
}

void Company::AddEvent(std::unique_ptr<Event> event) {
    events.push(std::move(event));
}

std::unique_ptr<Event> Company::TakeNextEvent() {
    std::unique_ptr<Event> nextEvent = std::move(
        const_cast<std::unique_ptr<Event>&>(events.top()));
    events.pop();
    return nextEvent;
}

void Company::SortByRole() {
    employees.sort([](const std::unique_ptr<Employee>& left,
        const std::unique_ptr<Employee>& right) {
            return static_cast<int>(left->GetRole()) < static_cast<int>(right->GetRole());
        });
}

void Company::Simulate(int day) {
    Statistic statistic;
    const auto workDayRealDuration = SimTime::WorkDayRealDuration();

    //std::ofstream journalReset("hodgins_journal.txt", std::ios::trunc);
    //(void)journalReset;

    std::cout << "=== " << name << " - work day " << day << " ===" << std::endl;
    std::cout << "Scale: 1 simulated hour = 1 real second" << std::endl;
    std::cout << "Work day: " << SimTime::kWorkDayHours
        << " simulated hours (" << workDayRealDuration.count()
        << " real seconds)" << std::endl;

    const auto dayStart = std::chrono::steady_clock::now();
    const auto dayEnd = dayStart + workDayRealDuration;

    while (std::chrono::steady_clock::now() < dayEnd) {
        GetBoss()->ProcessSimulationTick(statistic);
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
    }

    for (auto& employee : employees) {
        employee->UpdateBusyStatus();
    }
    GetBoss()->ProcessSimulationTick(statistic);

    GetBoss()->CollectFailedTasks(statistic);
    GetBoss()->WriteDailyStatistic(day, statistic);

    std::cout << "=== Day " << day << " complete. Report: hodgins_journal.txt ===" << std::endl;
}