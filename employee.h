#ifndef EMPLOYEES_H
#define EMPLOYEES_H
#include<iostream>
#include <string>

enum class Role {
    Boss,
    AutoMemoryDoll,
    MailMan
};
std::ostream& operator<<(std::ostream& os, Role r);
class Employee
{
protected:
    std::string name;
    std::string surname;
    Role role;
public:
    Employee(std::string n, std::string sn, Role r);
    virtual ~Employee() = default;
    friend std::ostream& operator<<(std::ostream& os, const Employee& emp);
    virtual void print() = 0;
    Role GetRole()const;
};
class Boss : public Employee
{
public:
    Boss(std::string n, std::string sn);
    void print() override;
    void GetWork();
};
class AutoMemoryDoll : public Employee
{
    double timeprinting;
public:
    AutoMemoryDoll(std::string n, std::string sn, double tp);
    void print() override;
};
class MailMan : public Employee
{
    double timedelivery;
public:
    MailMan(std::string n, std::string sn, double td);
    void print() override;
};

#endif // EMPLOYEES_H
