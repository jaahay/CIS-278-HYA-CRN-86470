cmake_minimum_required(VERSION 4.1.1)
set(CMAKE_CXX_STANDARD 20)
project(UniversityCourseManagementSystem VERSION 1.0 LANGUAGES CXX)
add_executable(UniversityCourseManagementSystem)
set(
	HEADERS
	Utils.hpp
	Student.hpp
	Course.hpp
	CourseStudent.hpp
	Enrollment.hpp
	App.hpp
)
target_sources(
	UniversityCourseManagementSystem
	PUBLIC
		FILE_SET public_headers
		TYPE HEADERS
		FILES
			${HEADERS}
)
set(
	SRC
	Utils.cpp
	Student.cpp
	Course.cpp
	CourseStudent.cpp
	Enrollment.cpp
	App.cpp
)
target_sources(
	UniversityCourseManagementSystem
	PRIVATE
		UniversityCourseManagementSystem.cpp
		${SRC}
)
#add_library(Lib
#	Utils.hpp Student.hpp Course.hpp CourseStudent.hpp Enrollment.hpp App.hpp
#	Utils.cpp Student.cpp Course.cpp CourseStudent.cpp Enrollment.cpp App.cpp
#)
#target_link_libraries(UniversityCourseManagementSystem PRIVATE Lib)