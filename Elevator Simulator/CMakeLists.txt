cmake_minimum_required(VERSION 3.15)
project(ElevatorSimulator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(src/core)      # header-only core (optional, see below)
add_subdirectory(src/elevator)

#add_subdirectory(examples)

# Optionally install executables (uncomment when ready)
# install(TARGETS ElevatorSimulator
#     RUNTIME DESTINATION bin
# )

#add_executable(ElevatorSimulator app/main.cpp)

#target_compile_features(ElevatorSimulator PRIVATE cxx_std_20)

#target_link_libraries(ElevatorSimulator PRIVATE elevator)

#target_include_directories(ElevatorSimulator
#    PRIVATE
#        ${CMAKE_CURRENT_SOURCE_DIR}/include
#)