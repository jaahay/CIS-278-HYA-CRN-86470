// UniversityCourseManagementSystem.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <algorithm>
#include <cctype>
#include <iostream>
#include "App.hpp"
#include <sstream>

int main()
{
    std::cout << "Welcome." << std::endl;
    auto running = true;
    auto prompt = true;
    //while (running) {
    //    auto app = new App();
    //    if (prompt) {
    //        std::cout << "Please enter one of the following, and, replace arguments appropriately:" << std::endl;
    //        std::cout << "\tAdd" << std::endl;
    //        std::cout << "\tList" << std::endl;
    //        std::cout << "\tEnroll" << std::endl;
    //        std::cout << "\tGet" << std::endl;
    //        prompt = false;
    //    }
    //    /*std::cout << "\tAdd course _title_ _instructor_" << std::endl;
    //    std::cout << "\tList courses" << std::endl;
    //    std::cout << "\tAdd student _name_" << std::endl;
    //    std::cout << "\tList Students" << std::endl;
    //    std::cout << "\tEnroll _courseid_ _studentid_" << std::endl;
    //    std::cout << "\tList student courses" << std::endl;
    //    std::cout << "\tList course students" << std::endl;
    //    std::cout << "\tDrop _courseid_ _studentid_" << std::endl;
    //    std::cout << "\tWaitlist _courseid_ _studentid_" << std::endl;
    //    std::cout << "\tAccept _courseid_ _studentid_" << std::endl;
    //    std::cout << "\tGet course waitlist _courseid_" << std::endl;
    //    std::cout << "\tGet student waitlist _studentid_" << std::endl;*/
    //    std::string command;
    //    std::cin >> command;
    //    std::transform(command.begin(), command.end(), command.begin(), std::tolower);
    //    
    //    if (command == "get") {

    //    }
    //    getline(ss, token, ' ');
    //    if (token == "add") {
    //        getline(ss, token, ' ');
    //        if (token == "course") {
    //            std::string title;
    //            getline(ss, title, ' ');
    //            std::string instructor;
    //            getline(ss, instructor, ' ');
    //            auto course = app->AddCourse(title, instructor);
    //            std::cout << &course << std::endl;
    //        }
    //        else if (token == "student") {
    //            std::string name;
    //            getline(ss, name, ' ');
    //            auto student = app->AddStudent(name);
    //            std::cout << &student << std::endl;
    //        }
    //        else { prompt = true;  }
    //    }
    //    else if (token == "list") {
    //        getline(ss, token, ' ');
    //        if (token == "courses") {
    //            auto courses = app->ListCourses();
    //            std::cout << &courses << std::endl;
    //        }
    //        else if (token == "student") {
    //            auto students = app->ListStudents();
    //            std::cout << &students << std::endl;
    //        } 
    //        else if (token == "course") {
    //            getline(ss, token, ' ');
    //            if (token == "students") {
    //                getline(ss, token, ' ');
    //                auto courses = app->ListCourses(token);
    //                std::cout << &courses << std::endl;
    //            }
    //            else { prompt = true;  }
    //        }
    //        else if (token == "student") {
    //            getline(ss, token, ' ');
    //            if (token == "courses") {
    //                getline(ss, token, ' ');
    //                auto students = app->ListStudents(token);
    //                std::cout << &students << std::endl;
    //            }
    //        }
    //        else { prompt = true;  }
    //    }
    //    else if (token == "enroll") {
    //        std::string courseid;
    //        getline(ss, courseid, ' ');
    //        std::string studentid;
    //        getline(ss, studentid, ' ');
    //        auto enrollment = app->Enroll(courseid, studentid);
    //        std::cout << &enrollment << std::endl;
    //    }
    //    else if (token == "drop") {
    //        std::string courseid;
    //        getline(ss, courseid, ' ');
    //        std::string studentid;
    //        getline(ss, studentid, ' ');
    //        auto enrollment = app->Drop(courseid, studentid);
    //        std::cout << &enrollment << std::endl;
    //    }
    //    else if (token == "waitlist") {
    //        std::string courseid;
    //        getline(ss, courseid, ' ');
    //        std::string studentid;
    //        getline(ss, studentid, ' ');
    //        auto enrollment = app->Waitlist(courseid, studentid);
    //        std::cout << &enrollment << std::endl;

    //    }
    //    else if (token == "accept") {
    //        std::string courseid;
    //        getline(ss, courseid, ' ');
    //        std::string studentid;
    //        getline(ss, studentid, ' ');
    //        auto enrollment = app->Accept(courseid, studentid);
    //        std::cout << &enrollment << std::endl;

    //    }
    //    else if (token == "get") {
    //        getline(ss, token, ' ');
    //        if (token == "course") {
    //            getline(ss, token, ' ');
    //            if (token == "waitlist") {
    //                getline(ss, token, ' ');
    //                auto courseWaitlist = app->CourseWaitlist(token);
    //                std::cout << &courseWaitlist << std::endl;
    //            }
    //            else { prompt = true; }
    //        }
    //        else if (token == "student") {
    //            getline(ss, token, ' ');
    //            if (token == "waitlist") {
    //                getline(ss, token, ' ');
    //                auto studentWaitlist = app->StudentWaitlist(token);
    //                std::cout << &studentWaitlist << std::endl;
    //            }
    //            else { prompt = true; }
    //        }
    //    }
    //    else { prompt = true; }
    //    if(prompt == true) {
    //        std::cout << "I didn't understand that.";
    //        continue;
    //    }

    //    std::cout << "Continue? Y/N" << std::endl;
    //    std::string s;
    //    std::cin >> s;
    //    if (s != "Y" || s != "y") {
    //        running = false;
    //        std::cout << "Goodbye." << std::endl;
    //    }
    //}
}