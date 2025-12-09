#include "Enrollment.hpp"

Course Enrollment::NewCourse(std::string title, std::string name)
{
	return Course(title, name);
}
Student Enrollment::NewStudent(std::string name)
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
