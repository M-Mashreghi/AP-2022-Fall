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
	School(sign_up_rules* _rules);
	void add_new_student(string temp_s_id, string temp_s_name);
	void add_new_class(string code, string title, string cap);
	bool is_c_code_exists(string code);
	bool is_s_id_exists(string _id);
	bool is_student_already_in_class(Student* s, Class* c);
	void pri();
	void change_capacity_order();
	void drop_classes();
	void signup_classes();
	void report_classes();
	void report_student();



private:
	

	void report_student_unit(Student* student);

	vector<Course_unit_request*>  CURs;//course unit request
	vector<Student*> students;
	vector<Class*> classes;

	pair<int, int> report_Course_unit_request(Class* c);

		Student* find_id(string _id);

		bool is_s_name_exists(string name);


		Class* find_class(string code);
		void report_student_unit_sorted(vector<string>in_class, vector<string>wating_list);

	//find out class is empty or not
		bool is_class_empty(Class* c);

	//del student course
		void del_course_unit_request(Student* s, Class* c);

	//find replace student after increase capacity or someone delete its course
		void find_replace_person(Class* c);


		sign_up_rules* rules ;
};





void Load_up_students(class School& school, int num_of_student);

void Load_up_classes(class School& school, int num_of_classes);

void get_basic_information(class School& school);


//call the command order
void call_app_functions(class School& school, string command);

string get_command(string command);

void get_order(class School& school);
