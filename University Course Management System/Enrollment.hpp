// Enrollment.hpp
#ifndef ENROLLMENT_HPP
#define ENROLLMENT_HPP

#include "CourseStudent.hpp"

namespace Enrollment
{
	const Course NewCourse(std::string, std::string);
	const Student NewStudent(std::string);
	const CourseStudent Enroll(const Course &, const Student &);
	const CourseStudent Drop(CourseStudent &);
	const CourseStudent Waitlist(CourseStudent &);
	const CourseStudent Accept(CourseStudent &);
} // namespace Enrollment

#endif // !ENROLLMENT_HPP

