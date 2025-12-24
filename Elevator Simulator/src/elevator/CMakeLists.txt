cmake_minimum_required(VERSION 3.15)
project(elevator LANGUAGES CXX)

# Collect source files
file(GLOB_RECURSE elevator_SOURCES
    ${CMAKE_SOURCE_DIR}/src/elevator/*.cpp
)

list(REMOVE_ITEM elevator_SOURCES
    #"F:/Development/CIS-278-HYA-CRN-86470/Elevator Simulator/src/elevator/Passenger.cpp"
    "F:/Development/CIS-278-HYA-CRN-86470/Elevator Simulator/src/elevator/Elevator.cpp"
    "F:/Development/CIS-278-HYA-CRN-86470/Elevator Simulator/src/elevator/ElevatorController.cpp"
    "F:/Development/CIS-278-HYA-CRN-86470/Elevator Simulator/src/elevator/Bank.cpp"
)

# Collect elevator headers for IDE grouping
file(GLOB_RECURSE elevator_HEADERS
    ${CMAKE_SOURCE_DIR}/include/elevator/*.h
)

# Collect core headers for IDE grouping inside elevator project
file(GLOB_RECURSE core_HEADERS
    ${CMAKE_SOURCE_DIR}/include/core/*.h
)

add_library(elevator STATIC
    ${elevator_SOURCES}
    ${elevator_HEADERS}  # Add elevator headers here for IDE visibility
    ${core_HEADERS}      # Add core headers here for IDE visibility only
)

# Organize elevator headers in IDE
source_group(
    TREE "${CMAKE_SOURCE_DIR}/include/elevator"
    PREFIX "Header Files\\Elevator"
    FILES ${elevator_HEADERS}
)

# Organize core headers in IDE under elevator project
source_group(
    TREE "${CMAKE_SOURCE_DIR}/include/core"
    PREFIX "Header Files\\Core"
    FILES ${core_HEADERS}
)

# Organize elevator sources in IDE
source_group(
    TREE "${CMAKE_SOURCE_DIR}/src/elevator"
    PREFIX "Source Files\\Elevator"
    FILES ${elevator_SOURCES}
)

# Include directories
target_include_directories(elevator PUBLIC
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

# Link elevator against core (header-only)
target_link_libraries(elevator PRIVATE core)

# Set C++ standard explicitly if needed
target_compile_features(elevator PUBLIC cxx_std_20)

# Install headers and library
install(TARGETS elevator EXPORT elevatorTargets)

install(DIRECTORY ${CMAKE_SOURCE_DIR}/include/elevator
    DESTINATION include
    FILES_MATCHING PATTERN "*.h"
)

install(EXPORT elevatorTargets
    FILE elevatorTargets.cmake
    NAMESPACE elevator::
    DESTINATION lib/cmake/elevator
)
