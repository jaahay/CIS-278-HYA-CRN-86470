cmake_minimum_required(VERSION 3.10.0)

set(CMAKE_CXX_STANDARD 20)

project(ElevatorSimulator VERSION 0.1.0 LANGUAGES C CXX)

add_executable(ElevatorSimulator main.cpp)

include(CTest)
enable_testing()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
