cmake_minimum_required(VERSION 3.15)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

## Glob all .cpp files inside src/elevator/
file(GLOB_RECURSE elevator_sources
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
)

list(REMOVE_ITEM elevator_sources
    #"F:/Development/CIS-278-HYA-CRN-86470/Elevator Simulator/src/elevator/Passenger.cpp"
    "F:/Development/CIS-278-HYA-CRN-86470/Elevator Simulator/src/elevator/Elevator.cpp"
    "F:/Development/CIS-278-HYA-CRN-86470/Elevator Simulator/src/elevator/ElevatorController.cpp"
    "F:/Development/CIS-278-HYA-CRN-86470/Elevator Simulator/src/elevator/Bank.cpp"
)

# Glob all public headers: everything in include/elevator except detail/
file(GLOB_RECURSE elevator_public_headers
    RELATIVE ${CMAKE_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/include/elevator/*.h
)

file(GLOB_RECURSE elevator_detail_headers
    RELATIVE ${CMAKE_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/include/elevator/detail/*.h
)

# Remove private headers from public headers
list(FILTER elevator_public_headers EXCLUDE REGEX "^elevator/detail/")

set(elevator_private_headers ${elevator_detail_headers})

#Add library with sources and all headers for IDE visibility
add_library(elevator STATIC ${elevator_sources})

target_sources(elevator PRIVATE
    ${elevator_public_headers}
    ${elevator_private_headers}
)

target_include_directories(elevator
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
    PRIVATE
        ${CMAKE_SOURCE_DIR}/include/elevator/detail
)

message(CMAKE_CURRENT_SOURCE_DIR: ${CMAKE_CURRENT_SOURCE_DIR})

# Organize source files in Visual Studio Solution Explorer
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" PREFIX "src" FILES ${elevator_sources})

message(CMAKE_SOURCE_DIR: ${CMAKE_SOURCE_DIR})
#message(elevator_public_headers: ${elevator_public_headers})
list(GET elevator_public_headers 0 first_public_header)
message(first_public_header: ${first_public_header})

# Organize public headers under Headers/Public
source_group(TREE "${CMAKE_SOURCE_DIR}/include/elevator" PREFIX "headers\\public" FILES ${elevator_public_headers})

# Organize private headers under Headers/Private
source_group(TREE "${CMAKE_SOURCE_DIR}/include/elevator/detail" PREFIX "headers\\private\\detail" FILES ${elevator_detail_headers})

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