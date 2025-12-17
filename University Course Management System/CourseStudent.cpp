// CourseStudent.cpp
#include "CourseStudent.hpp"

extern const Enrolled ENROLLED = Enrolled();
std::ostream& operator<<(std::ostream& os, const Enrolled&) {
	os << "enrolled";
	return os;
}

extern const Dropped DROPPED = Dropped();
std::ostream& operator<<(std::ostream& os, const Dropped&) {
	os << "dropped";
	return os;
}
extern const Waitlisted WAITLISTED = Waitlisted();
std::ostream& operator<<(std::ostream& os, const Waitlisted&) {
	os << "waitlisted";
	return os;
}

extern const InterestedIn INTERESTED_IN = InterestedIn();
std::ostream& operator<<(std::ostream& os, const InterestedIn&) {
	os << "interested in";
	return os;
}

CourseStudent::CourseStudent(Course const &course, Student const &student)
	: course(course), student(student), enrollment(INTERESTED_IN) {}
Course const CourseStudent::GetCourse() const
{
	return course;
}

std::ostream& operator<<(std::ostream& os, const CourseStudent& courseStudent) 
{
	os << "Student: " << courseStudent.student.GetFullName() << std::endl;
	os << "Course: " << courseStudent.course.GetCourseTitle() << std::endl;
	auto e = courseStudent.enrollment;
	os << "Enrollment: " << e << std::endl;
	return os;
}

Student const CourseStudent::GetStudent() const
{
	return student;
}
const EnrollmentState CourseStudent::GetEnrollment() const
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