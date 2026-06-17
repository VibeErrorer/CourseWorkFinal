// =============================================================================
// statistic.cpp — обновление счётчиков по типу события
// =============================================================================
#include "statistics/statistic.h"
#include "employees/employee.h"
#include "events/event.h"
#include "events/event_types.h"

void Statistic::AddCompletedTask(Event* event, Employee* employee)
{
    AddSuccess(event, employee);
}

void Statistic::AddSuccess(Event* event, Employee* employee)
{
    if (event == nullptr || employee == nullptr) {
        return;
    }
    const int quantity = event->GetQuantity();
    const std::string fullName = employee->GetFullName();

    // Обновляем общую статистику
    switch (event->GetType()) {
    case TypeEvent::PrintRequest:
        lettersWritten += quantity;
        break;
    case TypeEvent::DeliveryRequest:
        lettersDelivered += quantity;
        break;
    case TypeEvent::BusinessTrip:
        businessTrip++;
        if (employee->GetName() == "Violet") {
            violetTraveled = true;
        }
        break;
    }

    // Обновляем статистику по сотруднику
    EmployeeStatistic& empStat = employeeStats[fullName];
    switch (event->GetType()) {
    case TypeEvent::PrintRequest:
        empStat.lettersWritten += quantity;
        break;
    case TypeEvent::DeliveryRequest:
        empStat.lettersDelivered += quantity;
        break;
    case TypeEvent::BusinessTrip:
        empStat.businessTrips++;
        {
            const auto* trip = dynamic_cast<const BusinessTrip*>(event);
            if (trip) {
                empStat.tripLocations.push_back(trip->GetLocation());
            }
        }
        break;
    }
}