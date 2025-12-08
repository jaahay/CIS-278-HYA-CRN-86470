// Course.cpp
#include "Course.hpp"
#include "Utils.hpp"

Course::Course() : 
	uid(Utils::GenerateNanosecondString()), courseTitle("Untitled Course"), instructorName("John Doe") {}

Course::Course(const std::string courseTitle, const std::string instructorName) :
	uid(Utils::GenerateNanosecondString()), courseTitle(courseTitle), instructorName(instructorName) {}

const std::string& Course::GetUid() const { return uid; }
const std::string& Course::GetCourseTitle() const { return courseTitle; }
const std::string& Course::GetInstructorName() const { return instructorName; }
const int Course::GetSize() const { return num_seats; }
const Course& Course::AddSeats(int num_seats) {
	this->num_seats += num_seats;
	return *this;
}