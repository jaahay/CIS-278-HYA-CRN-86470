cmake_minimum_required(VERSION 3.10.0)
set(CMAKE_CXX_STANDARD 20)
project(ElevatorSimulator VERSION 0.1.0 LANGUAGES C CXX)

add_subdirectory(${PROJECT_SOURCE_DIR}/include)
add_subdirectory(${PROJECT_SOURCE_DIR}/src)
add_subdirectory(${PROJECT_SOURCE_DIR}/app)

add_executable(ElevatorSimulator ${PROJECT_SOURCE_DIR}/app/main.cpp)
target_link_libraries(ElevatorSimulator PUBLIC app src)


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
