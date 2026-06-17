// =============================================================================
// role.h — роли сотрудников компании
// =============================================================================

#ifndef ROLE_H
#define ROLE_H

#include <iostream>

enum class Role {
    Boss,
    AutoMemoryDoll,
    MailMan
};

std::ostream& operator<<(std::ostream& os, Role role);

#endif // ROLE_H
