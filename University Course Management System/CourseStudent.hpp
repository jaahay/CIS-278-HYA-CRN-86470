// CourseStudent.hpp
#ifndef COURSESTUDENT_HPP
#define COURSESTUDENT_HPP

#include <iostream>
#include "Course.hpp"
#include "Student.hpp"

class EnrollmentState {
public:
	bool operator==(const EnrollmentState& other) const { return this == &other; };
	virtual std::ostream& print(std::ostream&) const = 0;
};

class Enrolled : public EnrollmentState {
public:
	std::ostream& print(std::ostream& os) const override {
		os << "enrolled";
		return os;
	}
};
static const EnrollmentState* ENROLLED = new Enrolled();

class Dropped : public EnrollmentState {
public:
	std::ostream& print(std::ostream& os) const override {
		os << "dropped";
		return os;
	}
};
static const EnrollmentState* DROPPED = new Dropped();

class Waitlisted : public EnrollmentState {
public:
	std::ostream& print(std::ostream& os) const override {
		os << "waitlisted";
		return os;
	}
};
static const EnrollmentState* WAITLISTED = new Waitlisted();

class InterestedIn : public EnrollmentState {
public:
	std::ostream& print(std::ostream& os) const override {
		os << "interested in";
		return os;
	}
};
static const EnrollmentState* INTERESTED_IN = new InterestedIn();

class CourseStudent
{
private:
	const Course& course;
	const Student& student;
	const EnrollmentState* enrollment;

public:
	CourseStudent() = default;
	CourseStudent(const Course&, const Student&);
	~CourseStudent() = default;
	CourseStudent(const CourseStudent& other) = default;
	CourseStudent& operator=(const CourseStudent& other) = default;
	CourseStudent(CourseStudent&& other) noexcept = default;
	CourseStudent& operator=(CourseStudent&& other) noexcept = default;
	const Course& GetCourse() const;
	const Student& GetStudent() const;
	const EnrollmentState* GetEnrollment() const;
	const CourseStudent& Enroll();
	const CourseStudent& Drop();
	const CourseStudent& Waitlist();
};

#endif // !COURSESTUDENT_HPP