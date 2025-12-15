// CourseStudent.cpp
#include "CourseStudent.hpp"


class Enrolled : public EnrollmentState {
};
extern std::ostream& operator<<(std::ostream& os, const Enrolled&) {
	os << "enrolled";
	return os;
}
EnrollmentState* ENROLLED = new Enrolled();

class Dropped : public EnrollmentState {
};
extern std::ostream& operator<<(std::ostream& os, const Dropped&) {
	os << "dropped";
	return os;
}
EnrollmentState* DROPPED = new Dropped();

class Waitlisted : public EnrollmentState {
};
extern std::ostream& operator<<(std::ostream& os, const Waitlisted&) {
	os << "waitlisted";
	return os;
}
EnrollmentState* WAITLISTED = new Waitlisted();

class InterestedIn : public EnrollmentState {
};
extern std::ostream& operator<<(std::ostream& os, const InterestedIn&) {
	os << "interested in";
	return os;
}
EnrollmentState* INTERESTED_IN = new InterestedIn();

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
	os << "Enrollment: " << courseStudent.enrollment << std::endl;
	return os;
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