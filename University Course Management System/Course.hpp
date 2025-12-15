// Course.hpp
#ifndef COURSE_HPP
#define COURSE_HPP
#include <string>
#include <iostream>

class Course
{
private:
	std::string uid;
	std::string courseTitle;
	std::string instructorName;
	int num_seats{};
public:
	Course();
	Course(std::string, std::string);
	~Course() = default;
	Course(const Course&) = default;
	// Course& operator=(const Course&) = default;
	Course(Course&&) = default;
	// Course& operator=(Course&&) = default;
	auto operator<=>(const Course&) const = default;
	bool operator==(const Course&) const = default;

	friend std::ostream& operator<<(std::ostream&, const Course&);

	std::string GetUid() const;
	std::string GetCourseTitle() const;
	std::string GetInstructorName() const;
	const int GetSize() const;
	const Course& AddSeats(int);

}; // class Course

#endif // !COURSE_HPP

