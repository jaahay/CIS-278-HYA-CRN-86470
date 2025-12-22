cmake_minimum_required(VERSION 3.15)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE elevator_PUBLIC_HEADERS
    #RELATIVE ${CMAKE_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/include/elevator/*.h
)

file(GLOB_RECURSE elevator_PRIVATE_HEADERS
    #RELATIVE ${CMAKE_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/include/elevator/detail/*.h
)

#file(GLOB_RECURSE elevator_PUBLIC_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}
#    ${CMAKE_CURRENT_SOURCE_DIR}/include/elevator/*.h
#)

#file(GLOB_RECURSE elevator_PRIVATE_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}
#    ${CMAKE_CURRENT_SOURCE_DIR}/include/elevator/detail/*.h
#)

add_library(elevator STATIC
    #Elevator.cpp
    #Panel.cpp
    Passenger.cpp
    States.cpp
    # Add other elevator .cpp files here
)

target_sources(elevator
    PRIVATE
        ${elevator_PUBLIC_HEADERS}
        ${elevator_PRIVATE_HEADERS}
)

target_include_directories(elevator
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include/elevator>
        $<INSTALL_INTERFACE:include/elevator>
    PRIVATE
        ${CMAKE_SOURCE_DIR}/include/elevator/detail
)

target_link_libraries(elevator PRIVATE core)

# Install the elevator library and its headers
install(TARGETS elevator
    EXPORT elevatorTargets
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
    INCLUDES DESTINATION include
)

# Install elevator headers (public API)
install(DIRECTORY ${CMAKE_SOURCE_DIR}/include/elevator
    DESTINATION include
    FILES_MATCHING PATTERN "*.h"
    PATTERN "*/" EXCLUDE
)

# Install core headers (public API)
install(DIRECTORY ${CMAKE_SOURCE_DIR}/include/core
    DESTINATION include
    FILES_MATCHING PATTERN "*.h"
    PATTERN "*/" EXCLUDE
)

# Export targets for find_package
install(EXPORT elevatorTargets
    FILE elevatorTargets.cmake
    NAMESPACE elevator::
    DESTINATION lib/cmake/elevator
)