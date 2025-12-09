// app.hpp
#ifndef APP_HPP
#define APP_HPP

#include <list>
#include <set>
#include <map>
#include <optional>
#include <string>
#include "CourseStudent.hpp"
class App
{
private:
	std::map <std::string, Course const> courses;
	std::map <std::string, Student const> students;
	std::map <Course const, std::set<CourseStudent>> courseStudentMap;
	std::map <Student const, std::set<CourseStudent>> studentCourseMap;
	std::map <Course const, std::list<CourseStudent>> courseWaitlistMap;
	std::map <Student const, std::set<CourseStudent>> studentWaitlistMap;
public:
	App() = default;
	~App() = default;
	App(const App& other) = default;
	App& operator=(const App& other) = default;
	App(App&& other) noexcept = default;
	App& operator=(App&& other) noexcept = default;
	const Course AddCourse(std::string, std::string);
	const std::optional<std::set<Course>> ListCourses(std::string) const;
	const Student AddStudent(std::string);
	const std::optional<std::set<Student>> ListStudents(std::string) const;
	const std::optional<CourseStudent> Enroll(std::string, std::string);
	const std::optional<CourseStudent> Drop(std::string, std::string);
	const std::optional<CourseStudent> Waitlist(std::string, std::string);
	const std::optional<CourseStudent> Accept(std::string, std::string);
	const std::optional<std::list<Student>> CourseWaitlist(std::string) const;
	const std::optional<std::set<Course>> StudentWaitlist(std::string) const;
protected:
	const std::set<Course> ListCourses(Student const &) const;
	const std::set<Student> ListStudents(Course const &) const;
	const CourseStudent Enroll(Course const &, Student const &);
	const CourseStudent Drop(Course const &, Student const &);
	const CourseStudent Waitlist(Course const &, Student const &);
	const std::list<Student> CourseWaitlist(Course const &) const;
	const std::set<Course> StudentWaitlist(Student const &) const;
}; // class App

#endif // !APP_HPP
