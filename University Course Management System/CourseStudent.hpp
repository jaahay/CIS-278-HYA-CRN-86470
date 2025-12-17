// CourseStudent.hpp
#ifndef COURSESTUDENT_HPP
#define COURSESTUDENT_HPP

#include <compare>
#include <iostream>
#include "Course.hpp"
#include "Student.hpp"

class EnrollmentState {
public:
	auto operator<=>(const EnrollmentState&) const = default;
};

class Enrolled : public EnrollmentState { };
const extern Enrolled ENROLLED;
std::ostream& operator<<(std::ostream&, const Enrolled&);

class Dropped : public EnrollmentState { };
const extern Dropped DROPPED;
std::ostream& operator<<(std::ostream&, const Dropped&);

class Waitlisted : public EnrollmentState { };
const extern Waitlisted WAITLISTED;
std::ostream& operator<<(std::ostream&, const Waitlisted&);

class InterestedIn : public EnrollmentState { };
const extern InterestedIn INTERESTED_IN;
std::ostream& operator<<(std::ostream&, const InterestedIn&);
class CourseStudent
{
private:
	const Course course;
	const Student student;
	EnrollmentState enrollment;

public:
	CourseStudent(Course const &, Student const &);
	auto operator<=>(const CourseStudent&) const = default;

	friend std::ostream& operator<<(std::ostream&, const CourseStudent&);

	Course const GetCourse() const;
	Student const GetStudent() const;
	const EnrollmentState GetEnrollment() const;
	const CourseStudent& Enroll();
	const CourseStudent& Drop();
	const CourseStudent& Waitlist();
};


#endif // !COURSESTUDENT_HPP