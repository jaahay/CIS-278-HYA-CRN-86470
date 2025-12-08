// App.cpp
#include "App.hpp"

App& App::AddCourse(Course& course) {
    // auto x = &course;
    // courses.insert(course.GetUid(), x);
    auto k = new Course();
    // courses.insert({std::string {"hi"}, course});
    return *this;
}