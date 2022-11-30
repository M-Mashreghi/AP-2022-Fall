#include "Class.hpp"


Class::Class(string c_code, string c_title, int cap) {
	class_code = c_code;
	class_title = c_title;
	capacity = cap;
}
void Class::change_capacity(int new_capacity) { capacity = new_capacity; }
bool Class::has_c_code(string code) { return class_code == code; }
bool Class::has_c_title(string c_title) { return class_title == c_title; }
bool Class::has_c_cap(int cap) { return capacity == cap; }
string Class::get_c_code() { return class_code; }
string Class::get_c_title() { return class_title; }
int Class::get_c_cap() { return capacity; }
