// =============================================================================
// statistic.h — учёт выполненных и проваленных задач за день
// =============================================================================
#ifndef STATISTIC_H
#define STATISTIC_H

#include <map>      
#include <string>
#include <vector>

class Event;
class Employee;

// Статистика по каждому сотруднику
struct EmployeeStatistic {
    int lettersWritten = 0;
    int lettersDelivered = 0;
    int businessTrips = 0;
    std::vector<std::string> tripLocations;
};

class Statistic
{
public:
    int lettersWritten = 0;
    int lettersDelivered = 0;
    int businessTrip = 0;

    std::vector<std::string> employeesOnTrip;
    std::vector<std::string> failedTask;
    bool violetTraveled = false;

    // Прогресс по каждому сотруднику
    std::map<std::string, EmployeeStatistic> employeeStats;

    void AddCompletedTask(Event* event, Employee* employee);
    void AddFailedTask(const std::string& task) { failedTask.push_back(task); }
    void AddSuccess(Event* event, Employee* employee);
};

#endif // STATISTIC_H