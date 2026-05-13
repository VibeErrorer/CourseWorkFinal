cmake_minimum_required(VERSION 3.5)

project(CHCompany LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(CHCompany
    main.cpp
    company.h
    company.cpp
    employee.h
    employee.cpp
    event.h
    event.cpp
    )
