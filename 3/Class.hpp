#pragma once
#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include <utility>



using namespace std;

class Class {
public:

	Class(string c_code, string c_title, int cap);
	void change_capacity(int new_capacity);
	bool has_c_code(string code);
	bool has_c_title(string c_title);
	bool has_c_cap(int cap);
	string get_c_code();
	string get_c_title();
	int get_c_cap();

private:
	string class_code;
	string class_title;
	int capacity;
};

