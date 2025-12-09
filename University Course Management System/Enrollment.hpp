// Enrollment.hpp
#ifndef ENROLLMENT_HPP
#define ENROLLMENT_HPP

#include "CourseStudent.hpp"

namespace Enrollment
{
	Course NewCourse(const std::string, const std::string);
	Student NewStudent(const std::string);
	CourseStudent AddStudentToCourse(const Course &, const Student &);

	/*Course& AddCourse(Course&);
	Student& AddStudent(const Student&);*/
} // namespace Enrollment

#endif // !ENROLLMENT_HPP

