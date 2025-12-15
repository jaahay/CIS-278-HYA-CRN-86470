cmake_minimum_required(VERSION 3.10.0)
set(CMAKE_CXX_STANDARD 20)
set(SRC 
	ActiveState.cpp
	Bank.cpp
	DoorState.cpp
	Elevator.cpp
	Heading.cpp
	Panel.cpp
	Passenger.cpp
)
add_library(src STATIC ${SRC})
target_compile_features(src PRIVATE cxx_std_20)
target_link_libraries(src PRIVATE include)
target_include_directories(src PRIVATE ${PROJECT_SOURCE_DIR}/include)
#include(CTest)
#enable_testing()