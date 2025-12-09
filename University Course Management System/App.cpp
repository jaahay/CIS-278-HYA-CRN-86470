#include "App.hpp"
#include "Enrollment.hpp"

const Course App::AddCourse(std::string title, std::string instructor)
{
    auto course = Enrollment::NewCourse(title, instructor);
    courses.insert(std::make_pair(course.GetUid(), course));
    return course;
}
const std::set<Course> App::ListCourses(std::string studentId) const
{
    auto& student = students.find(studentId)->second;
    return ListCourses(student);
}
const Student App::AddStudent(std::string name)
{
    auto student = Enrollment::NewStudent(name);
    students.insert(std::make_pair(student.GetUid(), student));
    return student;
}
const std::set<Student> App::ListStudents(std::string courseId) const
{
    auto& course = courses.find(courseId)->second;
    return ListStudents(course);
}
const CourseStudent App::Enroll(std::string courseId, std::string studentId)
{
    auto& course = courses.find(courseId)->second;
    auto& student = students.find(studentId)->second;
    auto courseStudent = Enrollment::AddStudentToCourse(course, student);
    return courseStudent;
}
const CourseStudent App::Drop(std::string courseId, std::string studentId)
{
    auto& course = courses.find(courseId)->second;
    auto& student = students.find(studentId)->second;
    auto& coursesStudents = courseStudents.find(course)->second;
    for (auto x : coursesStudents)
    {
        if (x->GetStudent() == student)
        {
            x->Drop();
            return *x;
        }
    }
    CourseStudent cs = Enroll(courseId, studentId);
    cs.Drop();
    return cs;
}
const std::set<Course> App::ListCourses(Student const &student) const
{
    auto studentsCourses = studentCourses.find(student);
    std::set<Course> courses;
    for (CourseStudent* studentCourse : studentsCourses->second) {
        courses.insert(studentCourse->GetCourse());
    }
    return courses;
}
const std::set<Student> App::ListStudents(Course const &course) const
{
    auto coursesStudents = courseStudents.find(course);
    std::set<Student> students;
    for (CourseStudent* courseStudent : coursesStudents->second) {
        students.insert(courseStudent->GetStudent());
    }
    return students;
}