cmake_minimum_required(VERSION 3.10.0)
project(ElevatorSimulator VERSION 0.1.0 LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 20)
add_subdirectory(${PROJECT_SOURCE_DIR}/include)
add_subdirectory(${PROJECT_SOURCE_DIR}/src)
add_subdirectory(${PROJECT_SOURCE_DIR}/app)
add_executable(ElevatorSimulator ${PROJECT_SOURCE_DIR}/app/main.cpp)
target_compile_features(ElevatorSimulator PRIVATE cxx_std_20)
target_include_directories(ElevatorSimulator PRIVATE 
	${PROJECT_SOURCE_DIR}/include
	${PROJECT_SOURCE_DIR}/src
	${PROJECT_SOURCE_DIR}/app
)
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
