cmake_minimum_required(VERSION 3.10.0)
set(CMAKE_CXX_STANDARD 20)
project(ElevatorSimulatorTest VERSION 0.1.0 LANGUAGES CXX)
add_executable(ElevatorSimulatorTest)
target_compile_features(ElevatorSimulatorTest PRIVATE cxx_std_20)
#target_sources(
#	ElevatorSimulatorTest
#	PUBLIC
#		FILE_SET public_headers
#		TYPE HEADERS
#		BASE_DIRS "include/"
#		FILES
#			${INCLUDE}
#)
set(
	TESTS
	./test/ElevatorTests.cpp
)
target_sources(
	ElevatorSimulatorTest
	PRIVATE
		${TESTS}
)