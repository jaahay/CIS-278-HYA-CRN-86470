#include "Enrollment.hpp"

const Course Enrollment::NewCourse(std::string title, std::string name)
{
	return Course(title, name);
}
const Student Enrollment::NewStudent(std::string name)
{
	return Student(name);
}
const CourseStudent Enrollment::Enroll(const Course &course, const Student &student)
{
	return CourseStudent(course, student);
}
const CourseStudent Enrollment::Drop(CourseStudent &courseStudent)
{
	return courseStudent.Drop();
}
const CourseStudent Enrollment::Waitlist(CourseStudent &courseStudent)
{
	return courseStudent.Waitlist();
}
const CourseStudent Enrollment::Accept(CourseStudent &courseStudent)
{
	return courseStudent.Enroll();
}

//Course& Enrollment::AddCourse(const Course& course) {
	//return course;
//}
