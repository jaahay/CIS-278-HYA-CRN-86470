set(HEADER
    Bank.h
    Elevator.h
    Panel.h
    Passenger.h
    )
add_library(header INTERFACE ${HEADER})
target_include_directories(header INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})