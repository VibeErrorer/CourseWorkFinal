#include "company.h"
#include <iostream>
#include <memory>
#include <algorithm>

std::string Company::GetName(){return name;}
const std::list<std::unique_ptr<Employee>>& 
Company::GetEmployees() const {
    return employees;
}
std::priority_queue<Event*> Company::GetEvents(){}
void Company::AddEmployee(std::unique_ptr<Employee> emp){
    employees.push_back(std::move(emp));
}
void Company::AddEvent(){}
void Company::SortByRoleEmployees(){
    employees.sort([](const std::unique_ptr<Employee>& a,
    const std::unique_ptr<Employee>& b){
        return static_cast<int>(a->GetRole()) < 
        static_cast<int>(b->GetRole());
    });
}
void Company::WorkDay(){}
