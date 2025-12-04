cmake_minimum_required(VERSION 3.10.0)
set(CMAKE_CXX_STANDARD 20)
set(APP main.cpp)
add_library(app STATIC ${APP})
target_link_libraries(app PRIVATE src include)
target_compile_features(app PRIVATE cxx_std_20)
target_include_directories(app PRIVATE 
	${PROJECT_SOURCE_DIR}/include
	${PROJECT_SOURCE_DIR}/src
)