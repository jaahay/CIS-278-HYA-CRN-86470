#include "App.hpp"
#include "Enrollment.hpp"

const Course App::AddCourse(std::string title, std::string instructor)
{
    const auto& course = Enrollment::NewCourse(title, instructor);
    courses.insert(std::make_pair(course.GetUid(), course));
    courseStudentMap.insert({course, std::set<CourseStudent>()});
    courseWaitlistMap.insert({course, std::list<CourseStudent>()});
    return course;
}
const std::optional<std::set<Course>> App::ListCourses(std::string studentId) const
{
    const auto& student = students.find(studentId);
    if(student == students.end()) { return std::nullopt; }
    return ListCourses(student->second);
}
const Student App::AddStudent(std::string name)
{
    const auto& student = Enrollment::NewStudent(name);
    students.insert(std::make_pair(student.GetUid(), student));
    studentCourseMap.insert({student, std::set<CourseStudent>()});
    studentWaitlistMap.insert({student, std::set<CourseStudent>()});
    return student;
}
const std::optional<std::set<Student>> App::ListStudents(std::string courseId) const
{
    const auto& course = courses.find(courseId);
    if(course == courses.end()) { return std::nullopt; }
    return ListStudents(course->second);
}
const std::optional<CourseStudent> App::Enroll(std::string courseId, std::string studentId)
{
    auto course = courses.find(courseId);
    if(course == courses.end()) { return std::nullopt; }
    auto student = students.find(studentId);
    if(student == students.end()) { return std::nullopt; }
    
    return Enroll(course->second, student->second);
}
const std::optional<CourseStudent> App::Drop(std::string courseId, std::string studentId)
{
    auto optional = Enroll(courseId, studentId);
    if(optional == std::nullopt) { return std::nullopt; }
    auto courseStudent = optional.value();
    courseStudent.Drop();
    return courseStudent;
}
const std::optional<CourseStudent> App::Waitlist(std::string courseId, std::string studentId)
{
    auto optional = Enroll(courseId, studentId);
    if(optional == std::nullopt) { return std::nullopt; }
    auto courseStudent = optional.value();
    courseStudent.Waitlist();
    return courseStudent;
}
const std::optional<std::list<Student>> ClassWaitlist(std::string studentId) {
    return std::nullopt;
}
const std::set<Course> App::ListCourses(Student const &student) const
{
    auto studentCourses = studentCourseMap.at(student);
    std::set<Course> courses;
    for (auto studentCourse : studentCourses) {
        courses.insert(studentCourse.GetCourse());
    }
    return courses;
}
const std::set<Student> App::ListStudents(Course const &course) const
{
    auto courseStudents = courseStudentMap.at(course);
    std::set<Student> students;
    for (auto courseStudent : courseStudents) {
        students.insert(courseStudent.GetStudent());
    }
    return students;
}
const CourseStudent App::Enroll(Course const &course, Student const &student)
{
    auto courseStudents = courseStudentMap.find(course);
    for(auto courseStudent : courseStudents->second)
    {
        if(courseStudent.GetStudent() == student) {
            return courseStudent;
        }
    }
    CourseStudent courseStudent(course, student);
    courseStudentMap.at(course).insert(courseStudent);
    studentCourseMap.at(student).insert(courseStudent);
    return courseStudent;
   
}
const CourseStudent App::Drop(Course const &course, Student const &student) 
{
    CourseStudent courseStudent = Enroll(course, student);
    courseStudent.Drop();
    return courseStudent;
}
const CourseStudent App::Waitlist(Course const &course, Student const &student)
{
    CourseStudent courseStudent = Enroll(course, student);
    courseStudent.Waitlist();
    return courseStudent;
}
const std::list<Student> App::CourseWaitlist(Course const &course) const
{
    auto waitlistedStudents = courseWaitlistMap.at(course);
    auto students = new std::list<Student>();
    for(auto courseStudent : waitlistedStudents)
    {
        Student student = courseStudent.GetStudent();
        students->push_back(student);
    }
    return *students;
}

const std::set<Course> App::StudentWaitlist(Student const &student) const
{
    auto studentWaitlists = studentWaitlistMap.at(student);
    auto courses = new std::set<Course>();
    for(auto courseStudent : studentWaitlists)
    {
        Course course = courseStudent.GetCourse();
        courses->insert(course);
    }
    return *courses;
}