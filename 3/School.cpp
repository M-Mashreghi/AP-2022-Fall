#include "School.hpp"


bool School::is_c_code_exists(string code) {
	if (classes.size() == 0)
		return false;
	for (Class* classs : classes) {
		if (classs->has_c_code(code))
			return true;
	}
	return false;
};

bool School::is_s_id_exists(string _id) {
	if (students.size() == 0)
		return false;
	for (Student* student : students) {
		if (student->has_id(_id))
			return true;
	}
	return false;
};

bool School::is_student_already_in_class(Student* s, Class* c) {
	for (Course_unit_request* cur : CURs) {
		if (cur->has_s_id_in_request(s) && cur->has_c_code_in_request(c))
			return true;
	}

	return false;
}

School::School(sign_up_rules* _rules) { rules = _rules;  };

void School::change_capacity_order() {
	int new_capacity;
	string code;
	cin >> code >> new_capacity;
	if ((new_capacity > 0)) {
		if (is_c_code_exists(code)) {
			Class* clas = find_class(code);
			int old_capacity = clas->get_c_cap();
			clas->change_capacity(new_capacity);
			if (clas->get_c_cap() > old_capacity) {
				find_replace_person(clas);
			}
			//cout << new_capacity;
		}
	}
}

//add student in class
void School::signup_classes() {
	string code, _id;
	cin >> _id >> code;
	Student* student = find_id(_id);
	Class* clas = find_class(code);
	if (rules->sign_up_student_in_class_rules(this, student, clas)) {
		Course_unit_request* new_CUR = new Course_unit_request(student, clas, is_class_empty(clas));//add student in class or in waiting
		CURs.push_back(new_CUR);
	}
	else {}//do nothing
}

void School::drop_classes() {
	string code, _id;
	cin >> _id >> code;
	Student* student = find_id(_id);
	Class* clas = find_class(code);
	if (rules->drop_classes_rules(this, student, clas)) {
		del_course_unit_request(student, clas);//del student's course
		//cout << "deleted" << endl;
		find_replace_person(clas);//find replace student if needed
	}
	else{}//do nothing
}

void School::add_new_student(string temp_s_id, string temp_s_name) {
	if (rules->sign_up_new_students_rules(this,temp_s_id, temp_s_name)) {
		Student* new_student = new Student(temp_s_name, temp_s_id);
		students.push_back(new_student);
	}
	else { abort(); }
}

void School::add_new_class(string code, string title, string cap) {
	if (rules->sign_up_new_class_rules(this, code, title, cap)) {//check information
		Class* new_class = new Class(code, title, stoi(cap));
		classes.push_back(new_class);
	}
	else { abort(); }

}


void School::pri() {
		for (Student* student : students) {
			cout << stoi(student->get_id()) << endl << student->get_name() << endl;
		}
		for (Class* classs : classes) {
			cout << classs->get_c_code() << endl << classs->get_c_title() << endl << classs->get_c_cap() << endl;
		}
	}


void School::report_classes() {
		for (Class* clas : classes) {
			pair<int, int> counter = report_Course_unit_request(clas);
			cout << clas->get_c_title() << ": " << counter.first << "(" << counter.second << ")" << endl;
		}
		cout << endl;
}

void School::report_student() {
		string id;
		cin >> id;
		Student* student = find_id(id);
		if (!student == 0) {
			cout << student->get_name() << ":" << endl;
			report_student_unit(student);
		}
}


void School::report_student_unit(Student* student) {
	vector<string> in_class, wating_list;
	for (Course_unit_request* cur : CURs) {
		if (cur->has_s_id_in_request(student)) {
			if (cur->check_status()) {
				in_class.push_back(cur->get_c_title_in_re());
				//cout << cur->get_c_title_in_re() << endl;
			}
			else {
				wating_list.push_back(cur->get_c_title_in_re());
				//cout << cur->get_c_title_in_re() << "(w)" << endl;
			}
		}
	}

	report_student_unit_sorted(in_class, wating_list);
}

void School::report_student_unit_sorted(vector<string>in_class, vector<string>wating_list) {

	for (Class* classs : classes) {
		for (auto in : in_class) {
			if (classs->get_c_title() == in)
				cout << in << endl;
		}
	}
	for (Class* classs : classes) {
		for (auto in_wait : wating_list) {
			if (classs->get_c_title() == in_wait)
				cout << in_wait << "(w)" << endl;
		}
	}
}

pair<int, int> School::report_Course_unit_request(Class* c) {
	int counter_in_class = 0, counter_in_wait = 0;
	for (Course_unit_request* cur : CURs) {
		if (cur->has_c_code_in_request(c)) {
			if (cur->check_status())
				counter_in_class++;
			else
				counter_in_wait++;
		}
	}
	return make_pair(counter_in_class, counter_in_wait);
}

Student* School::find_id(string _id) {
	for (Student* student : students) {
		if (student->has_id(_id))
			return student;
	}
	return NULL;
}

bool School::is_s_name_exists(string name) {
	if (students.size() == 0)
		return false;
	for (Student* student : students) {
		if (student->has_name(name))
			return true;
	}
	return false;
}

Class* School::find_class(string code) {
	for (Class* classs : classes) {
		if (classs->has_c_code(code))
			return classs;
	}
	return NULL;
}

//find out class is empty or not
bool School::is_class_empty(Class* c) {
	int counter = 0;
	for (Course_unit_request* cur : CURs) {
		if (cur->has_c_code_in_request(c))
			counter++;
	}
	if (counter < c->get_c_cap()) {
		//cout << "class isn't full" << endl;
		return true;
	}

	else {
		//cout << "class is full" << endl;
		return false;
	}

}

//del student course
void School::del_course_unit_request(Student* s, Class* c) {
	int counter = 0;
	for (Course_unit_request* cur : CURs) {
		if (cur->has_s_id_in_request(s) && cur->has_c_code_in_request(c)) {
			CURs.erase(CURs.begin() + counter);
		}
		counter++;
	}
}
//find replace student after increase capacity or someone delete its course
void School::find_replace_person(Class* c) {
	int counter = 0;
	for (Course_unit_request* cur : CURs) {
		if (cur->has_c_code_in_request(c) && counter < c->get_c_cap()) {
			cur->bring_in_class();
			counter++;
		}
	}
}





void Load_up_students(class School& school, int num_of_student) {
	string  temp_s_name, temp_s_id;
	for (int i = 0; i < num_of_student; i++) {// get & add one by one student information: 
		cin >> temp_s_id >> temp_s_name;
		school.add_new_student(temp_s_id, temp_s_name);
	}
}

void Load_up_classes(class School& school, int num_of_classes) {
	string  title, code, cap;
	for (int i = 0; i < num_of_classes; i++) {
		cin >> code >> title >> cap;
		school.add_new_class(code, title, cap);
	}
}

void get_basic_information(class School& school) {
	int num_of_student, num_of_classes;

	cin >> num_of_student;
	Load_up_students(school, num_of_student);

	cin >> num_of_classes;
	Load_up_classes(school, num_of_classes);

	//school.pri();
}


//call the command order
void call_app_functions(class School& school, string command) {
	if (command == "setcap") { school.change_capacity_order(); }
	else if (command == "add") { school.signup_classes(); }
	else if (command == "drop") { school.drop_classes(); }
	else if (command == "report") { school.report_classes(); }
	else if (command == "student") { school.report_student(); }
}

string get_command(string command) {
	cin >> command;
	return command;
}

void get_order(class School& school) {
	string command;
	while (true) {
		call_app_functions(school, get_command(command));
	}
}
