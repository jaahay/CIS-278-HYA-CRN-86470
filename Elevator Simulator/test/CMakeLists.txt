cmake_minimum_required(VERSION 3.10.0)
set(CMAKE_CXX_STANDARD 20)
set(
	TEST
	BankTests.cpp
	ElevatorTests.cpp
	PassengerTests.cpp
)
add_executable(test ${TEST})
target_compile_features(test PRIVATE cxx_std_20)
target_link_libraries(test PRIVATE include)
include(CTest)
enable_testing()