cmake_minimum_required(VERSION 3.10.0)
set(CMAKE_CXX_STANDARD 20)
set(
    INCLUDE
    ActiveState.h Bank.h DoorState.h Elevator.h Heading.h Panel.h Passenger.h
)
add_library(include INTERFACE ${INCLUDE})
target_include_directories(include INTERFACE
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)