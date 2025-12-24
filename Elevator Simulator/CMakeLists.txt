cmake_minimum_required(VERSION 3.15)
project(ElevatorSimulator LANGUAGES CXX)

# Optionally set global C++ standard here
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add subdirectories for modules
add_subdirectory(src/core)
add_subdirectory(src/elevator)

# Optionally define an overall executable or tests here linking elevator (and core transitively)
# add_executable(app src/app/main.cpp)
# target_link_libraries(app PRIVATE elevator)