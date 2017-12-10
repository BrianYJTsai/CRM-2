cmake_minimum_required(VERSION 3.8)
project(CRM2)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp CustomerDB.cpp CustomerDB.h Customer.h String.h Project7.cpp CustomerDB.cpp)
add_executable(CRM2 ${SOURCE_FILES})