// CourseStudent.hpp
#ifndef COURSESTUDENT_HPP
#define COURSESTUDENT_HPP

#include <iostream>
#include "Course.hpp"
#include "Student.hpp"

class EnrollmentState {
public:
	auto operator<=>(const EnrollmentState&) const = default;
};
extern EnrollmentState* ENROLLED;
extern EnrollmentState* DROPPED;
extern EnrollmentState* WAITLISTED;
extern EnrollmentState* INTERESTED_IN;

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

	friend std::ostream& operator<<(std::ostream&, const CourseStudent&);

	Course const GetCourse() const;
	Student const GetStudent() const;
	const EnrollmentState* GetEnrollment() const;
	const CourseStudent& Enroll();
	const CourseStudent& Drop();
	const CourseStudent& Waitlist();
};


#endif // !COURSESTUDENT_HPP