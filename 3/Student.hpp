#pragma once
#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include <utility>


using namespace std;


class Student {
public:
	Student(string _name, string _member_id);
	bool has_id(string _id);
	bool has_name(string name);
	string get_id();
	string get_name();
private:
	string _student_name;
	string _student_id;
};