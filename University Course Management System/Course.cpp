// Course.cpp
#include "Course.hpp"
#include "Utils.hpp"

Course::Course() : 
	uid(Utils::GenerateNanosecondString()), courseTitle("Untitled Course"), instructorName("John Doe") {}

Course::Course(std::string courseTitle, std::string instructorName) :
	uid(Utils::GenerateNanosecondString()), courseTitle(courseTitle), instructorName(instructorName) {}

std::string& Course::GetUid() const { return uid; }
std::string& Course::GetCourseTitle() const { return courseTitle; }
std::string& Course::GetInstructorName() const { return instructorName; }
const int Course::GetSize() const { return num_seats; }
const Course& Course::AddSeats(int num_seats) {
	this->num_seats += num_seats;
	return *this;
}