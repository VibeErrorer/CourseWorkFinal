// =============================================================================
// auto_memory_doll.h — сотрудник-автозапоминающая кукла (печать писем)
// Зависит: employee.h
// =============================================================================

#ifndef AUTO_MEMORY_DOLL_H
#define AUTO_MEMORY_DOLL_H

#include <chrono>
#include <string>

#include "employees/employee.h"

class AutoMemoryDoll : public Employee
{
public:
    AutoMemoryDoll(std::string name, std::string surname,
        std::chrono::milliseconds mailDuration,
        std::chrono::milliseconds requestDuration);

    void Print() override;
};

#endif // AUTO_MEMORY_DOLL_H
