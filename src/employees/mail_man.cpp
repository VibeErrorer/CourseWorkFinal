// =============================================================================
// mail_man.cpp — реализация почтальона
// =============================================================================

#include "employees/mail_man.h"

#include <iostream>

using namespace std::chrono;

MailMan::MailMan(std::string mailManName, std::string mailManSurname,
    milliseconds mailDuration, milliseconds requestDuration)
    : Employee(std::move(mailManName), std::move(mailManSurname),
        Role::MailMan, mailDuration, requestDuration)
{}

void MailMan::Print()
{
    std::cout << *this << ", time for delivery: "
        << GetMailDuration().count() / 17 << " min/letter" << std::endl;
}
