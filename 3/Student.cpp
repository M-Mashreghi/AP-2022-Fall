#include "Student.hpp"






Student::Student(string _name, string _member_id) {
	_student_name = _name;
	_student_id = _member_id;
}

bool Student::has_id(string _id) { return _student_id == _id; }
bool Student::has_name(string name) { return _student_name == name; }

string Student::get_id() { return _student_id; }
string Student::get_name() { return _student_name; }
