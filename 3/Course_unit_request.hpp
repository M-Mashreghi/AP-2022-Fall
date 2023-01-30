#pragma once
#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include <utility>
#include <memory>

#include "Student.hpp"
#include "Class.hpp"



using namespace std;

class Course_unit_request {
public:
	Course_unit_request(Student* s, Class* c, bool statuse);
	void bring_in_class();
	bool has_s_id_in_request(Student* s);
	bool has_c_code_in_request(Class* c);
	string get_s_name_in_re();
	string get_c_code_in_re();
	string get_c_title_in_re();
	int get_c_cap_in_re();
	bool check_status();
private:
	Student* _student;
	Class* _clas;
	bool _statuse;
};

