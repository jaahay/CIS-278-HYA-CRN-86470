// app.hpp
#ifndef APP_HPP
#define APP_HPP

#include <list>
#include <map>
#include <string>
#include "CourseStudent.hpp"
class App
{
private:
	std::map <std::string, Course*> courses;
	std::map <std::string, Student*> students;
	std::map <Course*, CourseStudent*> courseStudents;
	std::map <Student*, CourseStudent*> studentCourses;
public:
	App() = default;
	~App() = default;
	App(const App& other) = default;
	App& operator=(const App& other) = default;
	App(App&& other) noexcept = default;
	App& operator=(App&& other) noexcept = default;
	App& AddCourse(Course&);
	App& AddStudent(const Student&);
	const std::list<Student> ListStudents(Course&) const;
	const std::list<Course> ListCourses(Student&) const;

}; // class App

#endif // !APP_HPP

