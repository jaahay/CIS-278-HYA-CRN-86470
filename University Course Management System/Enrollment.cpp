#include "Enrollment.hpp"

Course Enrollment::NewCourse(const std::string title, const std::string name)
{
	return Course(title, name);
}
Student Enrollment::NewStudent(const std::string name)
{
	return Student(name);
}
CourseStudent AddStudentToCourse(const Course &course, const Student &student)
{
	return CourseStudent(course, student);
}

//Course& Enrollment::AddCourse(const Course& course) {
	//return course;
//}
