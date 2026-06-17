#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <chrono>
#include <iostream>
#include <memory>
#include <string>

#include "employees/role.h"

class Event;

class Employee
{
protected:
    std::string name;
    std::string surname;
    Role role;
    bool isBusy{ false };
    std::chrono::milliseconds mailDuration_min;
    std::chrono::milliseconds requestDuration_min;
    std::chrono::steady_clock::time_point busyUntil;
    std::unique_ptr<Event> currentTask;

    // поля для командировки
    bool isOnBusinessTrip{ false };
    std::string businessTripLocation;

public:
    Employee(std::string name, std::string surname, Role role,
        std::chrono::milliseconds mailDuration,
        std::chrono::milliseconds requestDuration);
    virtual ~Employee();

    std::string GetName() const { return name; }
    std::string GetFullName() const;
    Role GetRole() const { return role; }
    bool GetBusy() const { return isBusy; }

    std::chrono::minutes GetMinutesPerLetter() const;
    void SetBusy(std::chrono::milliseconds realDuration);
    void UpdateBusyStatus();

    void StartTask(std::unique_ptr<Event> task, std::chrono::milliseconds realDuration);
    bool HasCompletedTask() const;
    Event* GetCurrentEvent() const { return currentTask.get(); }
    std::unique_ptr<Event> TakeCompletedTask();

    void SetMailDuration(std::chrono::milliseconds duration) { mailDuration_min = duration; }
    std::chrono::milliseconds GetMailDuration() const { return mailDuration_min; }

    void SetRequestDuration(std::chrono::milliseconds duration) { requestDuration_min = duration; }
    std::chrono::milliseconds GetRequestDuration() const { return requestDuration_min; }

    friend std::ostream& operator<<(std::ostream& os, const Employee& employee);
    virtual void Print() = 0;

    // методы для командировки
    void SetOnBusinessTrip(bool onTrip, const std::string& location = "") {
        isOnBusinessTrip = onTrip;
        businessTripLocation = location;
    }

    bool IsOnBusinessTrip() const { return isOnBusinessTrip; }
    const std::string& GetBusinessTripLocation() const { return businessTripLocation; }
};

#endif // EMPLOYEE_H