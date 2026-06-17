// =============================================================================
// mail_man.h — почтальон (доставка писем)
// Зависит: employee.h
// =============================================================================

#ifndef MAIL_MAN_H
#define MAIL_MAN_H

#include <chrono>
#include <string>

#include "employees/employee.h"

class MailMan : public Employee
{
public:
    MailMan(std::string name, std::string surname,
        std::chrono::milliseconds mailDuration,
        std::chrono::milliseconds requestDuration);

    void Print() override;
};

#endif // MAIL_MAN_H
