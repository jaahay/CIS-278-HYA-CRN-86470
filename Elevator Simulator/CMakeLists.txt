cmake_minimum_required(VERSION 3.10.0)
set(CMAKE_CXX_STANDARD 20)
project(ElevatorSimulator VERSION 0.1.0 LANGUAGES CXX)
add_executable(ElevatorSimulator)
set(
	HEADERS 
	./include/ActiveState.h
	./include/Bank.h
	./include/DoorState.h
	./include/Elevator.h
	./include/Heading.h
	./include/Panel.h
	./include/Passenger.h
)
target_sources(
	ElevatorSimulator
	PUBLIC
		FILE_SET public_headers
		TYPE HEADERS
		BASE_DIRS "include/"
		FILES
			${HEADERS}
)
set(
	SRC 
	./src/ActiveState.cpp
	./src/Bank.cpp
	./src/DoorState.cpp
	./src/Elevator.cpp
	./src/Heading.cpp
	./src/Panel.cpp
	
)
target_sources(
	ElevatorSimulator
	PRIVATE
		#BASE_DIRS "src/"
		./app/main.cpp
		${SRC}
)

#add_subdirectory(include)
#add_subdirectory(src)
#add_subdirectory(app)
#add_subdirectory(test)
#target_compile_features(ElevatorSimulator PRIVATE cxx_std_20)
#target_link_libraries(ElevatorSimulator PRIVATE include src)
#set(CPACK_PROJECT_NAME ${PROJECT_NAME})
#set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
#include(CPack)