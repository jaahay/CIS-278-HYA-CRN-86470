// Student.cpp
#include <chrono>
#include "Student.hpp"
#include "Utils.hpp"

Student::Student()
	: uid(Utils::GenerateNanosecondString()), fullName("John Doe") {}

Student::Student(const std::string fullName = std::string{ "John Doe" })
	: uid(Utils::GenerateNanosecondString()), fullName(fullName) {}

const std::string& Student::GetUid() const { return uid; }
const std::string& Student::GetFullName() const { return fullName; }