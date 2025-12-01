cmake_minimum_required(VERSION 3.10.0)
set(CMAKE_CXX_STANDARD 20)
project(ElevatorSimulator VERSION 0.1.0 LANGUAGES C CXX)

add_subdirectory(${PROJECT_SOURCE_DIR}/include)
add_subdirectory(${PROJECT_SOURCE_DIR}/src)

add_executable(ElevatorSimulator main.cpp)
target_compile_features(ElevatorSimulator PRIVATE cxx_std_20)
target_link_libraries(ElevatorSimulator PUBLIC src include)

include(CTest)
enable_testing()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
