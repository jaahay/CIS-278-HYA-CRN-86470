cmake_minimum_required(VERSION 3.10.0)
set(CMAKE_CXX_STANDARD 20)
set(SRC Bank.cpp)
add_library(src STATIC ${SRC})
target_compile_features(src PRIVATE cxx_std_20)
target_link_libraries(src PUBLIC include)
target_include_directories(src PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>
    $<INSTALL_INTERFACE:src>
)
include(CTest)
enable_testing()