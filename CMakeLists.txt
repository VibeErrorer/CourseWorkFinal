cmake_minimum_required(VERSION 3.5)

project(CHCompany LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(CHCompany
    src/main.cpp

    src/core/company.cpp
    src/core/company.h

    src/employees/role.cpp
    src/employees/role.h
    src/employees/employee.cpp
    src/employees/employee.h
    src/employees/boss.cpp
    src/employees/boss.h
    src/employees/auto_memory_doll.cpp
    src/employees/auto_memory_doll.h
    src/employees/mail_man.cpp
    src/employees/mail_man.h

    src/events/event_types.h
    src/events/event.h
    src/events/event.cpp

    src/statistics/statistic.cpp
    src/statistics/statistic.h
)

target_include_directories(CHCompany PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)
