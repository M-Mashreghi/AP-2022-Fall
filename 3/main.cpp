#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include <utility>
#include "sign_up_rules.hpp"
#include "School.hpp"
#include "Class.hpp"
#include "Student.hpp"
#include "Course_unit_request.hpp"


using namespace std;



int main() {
	sign_up_rules rule;
	School school(&rule);
	get_basic_information(school);//get classes and students
	get_order(school);//get orders
}



