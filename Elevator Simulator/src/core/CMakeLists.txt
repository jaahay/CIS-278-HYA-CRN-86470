cmake_minimum_required(VERSION 3.15)
project(core LANGUAGES CXX)

add_library(core INTERFACE)

set_target_properties(core PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
)

# Adjust path to project root include directory
file(GLOB_RECURSE core_HEADERS
    RELATIVE ${CMAKE_SOURCE_DIR}   # Use project root
    ${CMAKE_SOURCE_DIR}/include/core/*.h
)

# Add headers as INTERFACE sources so IDEs and consumers see them
target_sources(core INTERFACE
    ${core_HEADERS}
)

# Include directory for consumers
target_include_directories(core INTERFACE
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

# Optional: export core target for downstream usage if you install core separately
install(TARGETS core EXPORT coreTargets)

install(DIRECTORY ${CMAKE_SOURCE_DIR}/include/core
    DESTINATION include
    FILES_MATCHING PATTERN "*.h"
)

install(EXPORT coreTargets
    FILE coreTargets.cmake
    NAMESPACE elevator::core::
    DESTINATION lib/cmake/elevator/core
)