#include "employee.h"

Employee::Employee(std::string n, std::string sn, Role r):
    name{n}, surname{sn}, role{r}{}
Boss::Boss(std::string n, std::string sn):
    Employee(n, sn, Role::Boss){}
AutoMemoryDoll::AutoMemoryDoll(std::string n, std::string sn, 
    double tp):
    Employee(n, sn, Role::AutoMemoryDoll),
    timeprinting{tp}{}
MailMan::MailMan(std::string n, std::string sn, double td):
    Employee(n, sn, Role::MailMan),
    timedelivery{td}{}

void Boss::print(){
    std::cout << "Role: Boss, name: " << name 
    << ", surname: " << surname;
}
void AutoMemoryDoll::print(){
    std::cout << "Role: AutoMemoryDoll, name: " << name 
    << ", surname: " << surname;
}
void MailMan::print(){
    std::cout << "Role: MailMan, name: " << name 
    << ", surname: " << surname;
}

Role Employee::GetRole()const {return role;}

std::ostream& operator<<(std::ostream& os, Role r){
    switch (r){
        case Role::Boss:
            os << "Boss"; break;
        case Role::AutoMemoryDoll:
            os << "AutoMemoryDoll"; break;
        case Role::MailMan:
            os << "MailMan"; break;
        default:
            os<< "Unknow";
    }
    return os;}
std::ostream& operator<<(std::ostream& os, const Employee& emp){
    os << "Role: " << emp.role << ", name: " << emp.name
       << ", surname: " << emp.surname;
    return os;}
