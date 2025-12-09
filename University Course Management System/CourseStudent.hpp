// CourseStudent.hpp
#ifndef COURSESTUDENT_HPP
#define COURSESTUDENT_HPP

#include <iostream>
#include "Course.hpp"
#include "Student.hpp"

class EnrollmentState {
public:
	bool operator==(const EnrollmentState& other) const = default;
	virtual std::ostream& print(std::ostream&) const = 0;
};

class Enrolled : public EnrollmentState {
public:
	std::ostream& print(std::ostream& os) const override {
		os << "enrolled";
		return os;
	}
};

class Dropped : public EnrollmentState {
public:
	std::ostream& print(std::ostream& os) const override {
		os << "dropped";
		return os;
	}
};

class Waitlisted : public EnrollmentState {
public:
	std::ostream& print(std::ostream& os) const override {
		os << "waitlisted";
		return os;
	}
};

class InterestedIn : public EnrollmentState {
public:
	std::ostream& print(std::ostream& os) const override {
		os << "interested in";
		return os;
	}
};

class CourseStudent
{
private:
	Course const course;
	Student const student;
	const EnrollmentState* enrollment;

public:
	// CourseStudent() = default;
	CourseStudent(Course const &, Student const &);
	~CourseStudent() = default;
	CourseStudent(const CourseStudent& other) = default;
	// CourseStudent& operator=(const CourseStudent& other) = default;
	CourseStudent(CourseStudent&& other) noexcept = default;
	// CourseStudent& operator=(CourseStudent&& other) noexcept = default;
	auto operator<=>(const CourseStudent&) const = default;
	bool operator==(const CourseStudent&) const = default;

	Course const GetCourse() const;
	Student const GetStudent() const;
	const EnrollmentState* GetEnrollment() const;
	const CourseStudent& Enroll();
	const CourseStudent& Drop();
	const CourseStudent& Waitlist();
};

#endif // !COURSESTUDENT_HPP