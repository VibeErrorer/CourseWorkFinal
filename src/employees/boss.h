#ifndef BOSS_H
#define BOSS_H

#include <chrono>
#include <list>
#include <memory>

#include "employees/employee.h"

class Company;
class Event;
class Statistic;

class Boss : public Employee
{
    Company& company;
    std::chrono::milliseconds CalculateRealTaskDuration(const Employee& employee,
        const Event& event) const;
    Role RequiredRoleForEvent(const Event& event) const;
    void ProcessCompletedTasks(Statistic& statistic);
    bool TryAssignNextEvent();

public:
    Boss(std::string name, std::string surname, Company& company);
    void Print() override;

    void Hire(std::unique_ptr<Employee>&& employee);
    void Hire(std::unique_ptr<Employee>& employee);
    void AddTask(std::unique_ptr<Event> event);

    std::list<std::unique_ptr<Employee>>::iterator FindFreeEmployeeByRole(Role role);
    void ProcessSimulationTick(Statistic& statistic);
    void CollectFailedTasks(Statistic& statistic);
    void WriteDailyStatistic(int day, const Statistic& report);
};

#endif // BOSS_H