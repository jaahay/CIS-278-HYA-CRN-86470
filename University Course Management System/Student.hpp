// Student.hpp
#ifndef STUDENT_HPP
#define STUDENT_HPP
#include <string>

class Student
{
private:
	std::string uid;
	std::string fullName;
public:
	Student();
	Student(std::string);
	~Student() = default;
	Student(const Student&) = default;
	// Student& operator=(const Student&) = default;
	Student(Student&&) = default;
	// Student& operator=(Student&&) = default;
	// auto operator<=>(const Student&) const = default;
	bool operator==(const Student&) const = default;

	std::string& GetUid() const;
	std::string& GetFullName() const;
}; // class Student

#endif // !STUDENT_HPP
