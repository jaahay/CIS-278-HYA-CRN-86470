cmake_minimum_required(VERSION 3.10.0)
set(CMAKE_CXX_STANDARD 20)
project(ElevatorSimulator VERSION 0.1.0 LANGUAGES CXX)
add_executable(ElevatorSimulator)
target_compile_features(ElevatorSimulator PRIVATE cxx_std_20)
set(
	INCLUDE 
	./include/ActiveState.h
	./include/Bank.h
	./include/DoorState.h
	./include/Elevator.h
	./include/ElevatorConcepts.h
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
			${INCLUDE}
)
set(
	SRC 
	./src/ActiveState.cpp
	./src/Bank.cpp
	./src/DoorState.cpp
	./src/Elevator.cpp
	./src/ElevatorConcepts.cpp
	./src/Heading.cpp
	./src/Panel.cpp
	./src/Passenger.cpp	
)
target_sources(
	ElevatorSimulator
	PRIVATE
		./app/main.cpp
		${SRC}
)