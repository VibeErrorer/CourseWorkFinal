#include "employees/employee.h"
#include "events/event.h"
#include <chrono>

using namespace std::chrono;

Employee::Employee(std::string employeeName, std::string employeeSurname, Role employeeRole,
    milliseconds mailDuration, milliseconds requestDuration)
    : name{ std::move(employeeName) }
    , surname{ std::move(employeeSurname) }
    , role{ employeeRole }
    , mailDuration_min{ mailDuration }
    , requestDuration_min{ requestDuration }
{
}

Employee::~Employee() = default;

std::string Employee::GetFullName() const {
    if (surname.empty()) return name;
    return name + " " + surname;
}

minutes Employee::GetMinutesPerLetter() const {
    return duration_cast<minutes>(mailDuration_min);
}

std::ostream& operator<<(std::ostream& os, const Employee& employee) {
    os << "Role: " << employee.role
        << ", name: " << employee.name
        << ", surname: " << employee.surname;
    return os;
}

void Employee::SetBusy(milliseconds realDuration) {
    isBusy = true;
    busyUntil = steady_clock::now() + realDuration;
}

void Employee::UpdateBusyStatus() {
    if (isBusy && steady_clock::now() >= busyUntil) {
        isBusy = false;
    }
}

void Employee::StartTask(std::unique_ptr<Event> task, milliseconds realDuration) {
    currentTask = std::move(task);
    SetBusy(realDuration);
}

bool Employee::HasCompletedTask() const {
    return !isBusy && currentTask != nullptr;
}

std::unique_ptr<Event> Employee::TakeCompletedTask() {
    return std::move(currentTask);
}