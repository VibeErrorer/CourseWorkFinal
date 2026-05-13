#ifndef COMPANY_H
#define COMPANY_H

#include <iostream>
#include <string>
#include <list>
#include <queue>

#include "employee.h"
#include "event.h"

class Company
{
    std::string name;
    std::list<std::unique_ptr<Employee>> employees;
    std::priority_queue<std::unique_ptr<Event>> events;
public:
    explicit Company (std::string n) : name{n} {};
    std::string GetName();
    const std::list<std::unique_ptr<Employee>>& 
    GetEmployees() const;
    std::priority_queue<Event*> GetEvents();
    void AddEmployee(std::unique_ptr<Employee> emp);
    void AddEvent();
    void SortByRoleEmployees();
    void WorkDay();
};

#endif // COMPANY_H
