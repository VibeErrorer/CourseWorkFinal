#ifndef COMPANY_H
#define COMPANY_H

#include <list>
#include <memory>
#include <queue>
#include <string>
#include <vector>

#include "employees/boss.h"
#include "employees/employee.h"
#include "events/event.h"
#include "statistics/statistic.h"  // ← ДОБАВЛЕНО

struct CompareEvents
{
    bool operator()(const std::unique_ptr<Event>& first,
        const std::unique_ptr<Event>& second) const;
};

class Company
{
    std::string name;
    std::unique_ptr<Boss> boss;
    std::list<std::unique_ptr<Employee>> employees;
    std::priority_queue<std::unique_ptr<Event>,
        std::vector<std::unique_ptr<Event>>, CompareEvents> events;

    Statistic statistic;  // ← ДОБАВЛЕНО: живёт всё время работы программы

public:
    Company(std::string companyName, std::string bossName, std::string bossSurname);
    void SetBoss(std::unique_ptr<Boss> newBoss) { boss = std::move(newBoss); }
    Boss* const GetBoss() const { return boss.get(); }

    std::string GetName() const;
    std::list<std::unique_ptr<Employee>>& GetEmployees();
    std::priority_queue<std::unique_ptr<Event>,
        std::vector<std::unique_ptr<Event>>, CompareEvents>& GetEvents();

    void AddEmployee(std::unique_ptr<Employee> employee);
    void AddEvent(std::unique_ptr<Event> event);
    std::unique_ptr<Event> TakeNextEvent();

    void SortByRole();
    void Simulate(int day = 1);
};

#endif // COMPANY_H