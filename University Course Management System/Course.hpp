// Course.hpp
#ifndef COURSE_HPP
#define COURSE_HPP
#include <string>

class Course
{
private:
	const std::string uid;
	const std::string courseTitle;
	const std::string instructorName;
	int num_seats{};
public:
	Course();
	Course(const std::string, const std::string);
	~Course() = default;
	Course(const Course&) = default;
	Course& operator=(const Course&) = default;
	Course(Course&&) = default;
	Course& operator=(Course&&) = default;
	const std::string& GetUid() const;
	const std::string& GetCourseTitle() const;
	const std::string& GetInstructorName() const;
	const int GetSize() const;
	const Course& AddSeats(int);
}; // class Course

#endif // !COURSE_HPP

