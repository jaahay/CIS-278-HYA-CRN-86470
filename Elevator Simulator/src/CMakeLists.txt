set(SRC Bank.cpp)
add_library(src STATIC ${SRC})
target_link_libraries(src PRIVATE include)