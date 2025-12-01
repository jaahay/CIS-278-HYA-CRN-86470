set(SRC Bank.cpp)
add_library(src ${SRC})
target_include_directories(src PUBLIC
    header
    ${CMAKE_CURRENT_SOURCE_DIR}
    )
target_link_libraries(src header)