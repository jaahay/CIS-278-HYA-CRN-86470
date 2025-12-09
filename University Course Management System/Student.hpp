// Student.hpp
#ifndef STUDENT_HPP
#define STUDENT_HPP
#include <string>

class Student
{
private:
	const std::string uid;
	const std::string fullName;
public:
	Student();
	Student(const std::string);
	~Student() = default;
	Student(const Student&) = default;
	Student& operator=(const Student&) = default;
	Student(Student&&) = default;
	Student& operator=(Student&&) = default;
	auto operator<=>(const Student&) const = default;
	bool operator==(const Student&) const = default;

	const std::string& GetUid() const;
	const std::string& GetFullName() const;
}; // class Student

#endif // !STUDENT_HPP
