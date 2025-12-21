cmake_minimum_required(VERSION 3.10.0)
project(ElevatorSimulator VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED <CONFIG>_OUTPUT_NAME)

add_library(elevator
	#./src/Bank.cpp
	./src/elevator/Elevator.cpp
	"src/elevator/Panel.cpp"
	"src/elevator/Passenger.cpp"
)

file(GLOB_RECURSE elevator_PUBLIC_HEADERS CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/include/elevator/*.h
)

file(GLOB_RECURSE elevator_PRIVATE_HEADERS CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/include/elevator/detail/*.h
)

target_sources(elevator
    PRIVATE
        ${elevator_PUBLIC_HEADERS}
        ${elevator_PRIVATE_HEADERS}
)

target_include_directories(elevator
	PUBLIC
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
		$<INSTALL_INTERFACE:include>
	PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR}/include/elevator/detail
)

#add_executable(ElevatorSimulator
#	app/main.cpp
#)

#target_compile_features(ElevatorSimulator PRIVATE cxx_std_20)

#target_link_libraries(ElevatorSimulator PRIVATE elevator)

#target_include_directories(ElevatorSimulator
#    PRIVATE
#        ${CMAKE_CURRENT_SOURCE_DIR}/include
#)

# Installation rules for library
install(TARGETS elevator
    EXPORT elevatorTargets
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
    INCLUDES DESTINATION include
)

install(DIRECTORY include/elevator
    DESTINATION include
    FILES_MATCHING 
    PATTERN "*.h"
    PATTERN "*/" EXCLUDE
)

# Installation rules for executable
#install(TARGETS ElevatorSimulator
#    RUNTIME DESTINATION bin
#)

# Export the targets for downstream projects
install(EXPORT elevatorTargets
    FILE elevatorTargets.cmake
    NAMESPACE elevator::
    DESTINATION lib/cmake/elevator
)