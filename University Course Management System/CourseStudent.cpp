// CourseStudent.cpp
#include "CourseStudent.hpp"

CourseStudent::CourseStudent(const Course& course, const Student& student)
	: course(course), student(student), enrollment(INTERESTED_IN) {}
const Course& CourseStudent::GetCourse() const
{
	return course;
}
const Student& CourseStudent::GetStudent() const
{
	return student;
}
const EnrollmentState* CourseStudent::GetEnrollment() const
{
	return enrollment;
}
const CourseStudent& CourseStudent::Enroll()
{
	enrollment = ENROLLED;
	return *this;
}
const CourseStudent& CourseStudent::Drop()
{
	enrollment = DROPPED;
	return *this;
}
const CourseStudent& CourseStudent::Waitlist()
{
	enrollment = WAITLISTED;
	return *this;
}
