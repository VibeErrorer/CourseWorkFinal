#include "employees/role.h"

std::ostream& operator<<(std::ostream& os, Role role) {
    switch (role) {
    case Role::Boss: os << "Boss"; break;
    case Role::AutoMemoryDoll: os << "AutoMemoryDoll"; break;
    case Role::MailMan: os << "MailMan"; break;
    default: os << "Unknown";
    }
    return os;
}