// Enrollment.hpp
#ifndef ENROLLMENT_HPP
#define ENROLLMENT_HPP

#include "CourseStudent.hpp"

namespace Enrollment
{
	Course NewCourse(std::string, std::string);
	Student NewStudent(std::string);
	CourseStudent AddStudentToCourse(const Course &, const Student &);
	
} // namespace Enrollment

#endif // !ENROLLMENT_HPP

