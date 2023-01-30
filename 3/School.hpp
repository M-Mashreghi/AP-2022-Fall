#pragma once
#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include <utility>
#include "Class.hpp"
#include "Student.hpp"
#include "Course_unit_request.hpp"
#include "sign_up_rules.hpp"

using namespace std;
class sign_up_rules;

class School {
public:
	void RUN();
	School(sign_up_rules* _rules);
	~School(){};
	bool is_c_code_exists(string code);
	bool is_s_id_exists(string _id);
	bool is_student_already_in_class(Student* s, Class* c);
private:
	void Load_up_students(int num_of_student);
	void Load_up_classes(int num_of_classes);
	void get_basic_information();
	void call_app_functions(string command);
	void add_new_student(string temp_s_id, string temp_s_name);
	void add_new_class(string code, string title, string cap);
	void pri();
	void change_capacity_order();
	void drop_classes();
	void signup_classes();
	void report_classes();
	void report_student();
	void report_student_unit(Student* student);
	pair<int, int> report_Course_unit_request(Class* c);
	Student* find_id(string _id);
	bool is_s_name_exists(string name);
    Class* find_class(string code);
	void report_student_unit_sorted(vector<string>in_class, vector<string>wating_list);
	bool is_class_empty(Class* c);
	void del_course_unit_request(Student* s, Class* c);
	void find_replace_person(Class* c);
    sign_up_rules* rules ;
	vector<Course_unit_request*>  CURs;
	vector<Student*> students;
	vector<Class*> classes;
};

