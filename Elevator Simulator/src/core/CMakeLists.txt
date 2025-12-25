cmake_minimum_required(VERSION 3.15)
project(core LANGUAGES CXX)

add_library(core INTERFACE)

# Glob headers for IDE grouping only
file(GLOB_RECURSE core_HEADERS
    ${CMAKE_SOURCE_DIR}/include/core/*.h
)

# Organize headers in IDE (Visual Studio)
source_group(
    TREE "${CMAKE_SOURCE_DIR}/include/core"
    PREFIX "Header Files"
    FILES ${core_HEADERS}
)

# Expose include directory for consumers
target_include_directories(core INTERFACE
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

# Install headers
install(DIRECTORY ${CMAKE_SOURCE_DIR}/include/core
    DESTINATION include
    FILES_MATCHING PATTERN "*.h"
)

# Export target for downstream usage
install(TARGETS core EXPORT coreTargets)

install(EXPORT coreTargets
    FILE coreTargets.cmake
    NAMESPACE elevator::core::
    DESTINATION lib/cmake/elevator/core
)
