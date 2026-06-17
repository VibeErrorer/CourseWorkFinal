// =============================================================================
// auto_memory_doll.cpp — реализация автозапоминающей куклы
// =============================================================================

#include "employees/auto_memory_doll.h"

#include <iostream>

using namespace std::chrono;

AutoMemoryDoll::AutoMemoryDoll(std::string dollName, std::string dollSurname,
    milliseconds mailDuration, milliseconds requestDuration)
    : Employee(std::move(dollName), std::move(dollSurname),
        Role::AutoMemoryDoll, mailDuration, requestDuration)
{}

void AutoMemoryDoll::Print()
{
    std::cout << *this << ", time for printing: "
        << GetMailDuration().count() / 17 << " min/letter" << std::endl;
}
