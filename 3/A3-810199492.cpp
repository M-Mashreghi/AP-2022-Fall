#include <iostream>
#include "sign_up_rules.hpp"
#include "School.hpp"

using namespace std;

int main() {
	sign_up_rules rule;
	School school(&rule);
	school.RUN();
}