// app.hpp
#ifndef APP_HPP
#define APP_HPP

#include <list>
#include <set>
#include <map>
#include <string>
#include "CourseStudent.hpp"
class App
{
private:
	std::map <std::string, Course const> courses;
	std::map <std::string, Student const> students;
	std::map <Course const, std::set<CourseStudent*>> courseStudents;
	std::map <Student const, std::set<CourseStudent*>> studentCourses;
public:
	App() = default;
	~App() = default;
	App(const App& other) = default;
	App& operator=(const App& other) = default;
	App(App&& other) noexcept = default;
	App& operator=(App&& other) noexcept = default;
	const Course AddCourse(const std::string, const std::string);
	const std::set<Course> ListCourses(std::string const) const;
	const Student AddStudent(const std::string);
	const std::set<Student> ListStudents(std::string const) const;
	const CourseStudent Enroll(const std::string, const std::string);
	const CourseStudent Drop(const std::string, const std::string);

protected:
	const std::set<Course> ListCourses(Student const &) const;
	const std::set<Student> ListStudents(Course const &) const;
}; // class App

#endif // !APP_HPP

