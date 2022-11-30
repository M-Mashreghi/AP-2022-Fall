#pragma once
#include <iostream>
#include <cstdlib>
#include <vector>
#include <utility>
#include <string>
#include "School.hpp"

using namespace std;
class School;

class sign_up_rules
{
	public:
		bool sign_up_new_class_rules(School* school, string code, string title, string cap);
		bool drop_classes_rules(School* school, Student* student, Class* clas);
		bool sign_up_new_students_rules(School* school, string temp_s_id, string temp_s_name);
		bool sign_up_student_in_class_rules(School* school, Student* student, Class* clas);

	private:

		bool is_s_id_ok(string _id);

		bool is_s_name_ok(string _name);

		bool is_num_format_ok(string num);

	};

