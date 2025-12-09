// CourseStudent.cpp
#include "CourseStudent.hpp"

static const EnrollmentState* ENROLLED = new Enrolled();
static const EnrollmentState* DROPPED = new Dropped();
static const EnrollmentState* WAITLISTED = new Waitlisted();
static const EnrollmentState* INTERESTED_IN = new InterestedIn();

CourseStudent::CourseStudent(Course const &course, Student const &student)
	: course(course), student(student), enrollment(INTERESTED_IN) {}
Course const CourseStudent::GetCourse() const
{
	return course;
}
Student const CourseStudent::GetStudent() const
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
