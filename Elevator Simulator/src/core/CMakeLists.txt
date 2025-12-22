cmake_minimum_required(VERSION 3.15)
add_library(core INTERFACE)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE core_HEADERS
    #RELATIVE ${CMAKE_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/include/core/*.h
)

#file(GLOB_RECURSE core_HEADERS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
#    ${CMAKE_CURRENT_SOURCE_DIR}/include/core/*.h
#)

#target_sources(core INTERFACE
#    INTERFACE
#        ${core_HEADERS}
#)

target_sources(core
    PRIVATE
        ${core_HEADERS}
)

target_include_directories(core INTERFACE
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

# Optional: export core target for downstream usage if you install core separately
install(TARGETS core EXPORT coreTargets)

install(EXPORT coreTargets
    FILE coreTargets.cmake
    NAMESPACE elevator::core::
    DESTINATION lib/cmake/elevator/core
)