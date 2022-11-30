#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include <utility>

using namespace std;

//stoi()

class School;
class Class;
class Course_unit_request;
class Student;
class sign_up_rules;

class sign_up_rules {
public:

	bool sign_up_new_class_rules(string code, string title, string cap);

	bool sign_up_new_students_rules(string temp_s_id, string temp_s_name);


private:

	bool is_s_id_ok(string _id) {
		if (_id.length() < 6)//check length
			return false;

		if (!is_num_format_ok(_id))
				return false;
		return true;
	}

	bool is_s_name_ok(string _name) {
		if (_name == "")
			return false;
		else
			return true;
	}

	bool is_num_format_ok(string num) {
		for (int i = 0; i < num.length(); i++) {
			if (!(num[i] == '0' || num[i] == '1' || num[i] == '2' ||
				num[i] == '3' || num[i] == '4' || num[i] == '5' ||
				num[i] == '6' || num[i] == '7' || num[i] == '8' || num[i] == '9')) {
				return false;
			}
		}
		return true;
	}

};

bool sign_up_rules::sign_up_new_students_rules(string temp_s_id, string temp_s_name) {

	if (!is_s_name_ok(temp_s_name) || !is_s_id_ok(temp_s_id))//check name and id
		return false;
	return true;
}



bool sign_up_rules::sign_up_new_class_rules(string code, string title, string cap) {
	if (!is_num_format_ok(cap) || !is_num_format_ok(code))//check format
		return false;

	if (stoi(cap) <= 0 || (code.length() != 2))//check capicity & code lenght
		return false;

	if (title == "")//check title
		return false;
	return true;
}













class Class {
public:

	Class(string c_code, string c_title, int cap) {
		class_code = c_code;
		class_title = c_title;
		capacity = cap;
	}
	void change_capacity(int new_capacity) { capacity = new_capacity; }
	bool has_c_code(string code) { return class_code == code; }
	bool has_c_title(string c_title) { return class_title == c_title; }
	bool has_c_cap(int cap) { return capacity == cap; }

	string get_c_code() { return class_code; }
	string get_c_title() { return class_title; }
	int get_c_cap() { return capacity; }

private:
	friend class Course_unit_request;
	string class_code;
	string class_title;
	int capacity;
};

class Student {
public:
	Student(string _name, string _member_id) {
		_student_name = _name;
		_student_id = _member_id;
	}
	bool has_id(string _id) { return _student_id == _id; }
	bool has_name(string name) { return _student_name == name; }

	string get_id() { return _student_id; }
	string get_name() { return _student_name; }

private:
	friend class Course_unit_request;
	string _student_name;
	string _student_id;
};

class Course_unit_request {
public:
	Course_unit_request(Student* s, Class* c, bool statuse) {
		_student = s;
		_clas = c;
		_statuse = statuse;
		if (statuse == false)
			cout << "full";

	}
	void bring_in_class() { _statuse = true; }

	bool has_s_id_in_request(Student* s) { return(_student->get_id() == s->get_id()); }
	bool has_c_code_in_request(Class* c) { return(_clas->get_c_code() == c->get_c_code()); }
	string get_s_name_in_re() { return _student->get_id(); }
	string get_c_code_in_re() { return _clas->get_c_code(); }
	string get_c_title_in_re() { return _clas->get_c_title(); }
	int get_c_cap_in_re() { return _clas->get_c_cap(); }
	bool check_status() { return _statuse; }

private:
	Student* _student;
	Class* _clas;
	bool _statuse;
};



class School {
public:
	void add_new_student(string temp_s_id, string temp_s_name);
	void add_new_class(string code, string title, string cap);

	bool is_c_code_exists(string code);
	bool is_s_id_exists(string _id);
	bool is_student_already_in_class(Student* s, Class* c);

	void pri() {
		for (Student* student : students) {
			cout << stoi(student->get_id()) << endl << student->get_name() << endl;
		}
		for (Class* classs : classes) {
			cout << classs->get_c_code() << endl << classs->get_c_title() << endl << classs->get_c_cap() << endl;
		}
	}
	void change_capacity_order();
	void drop_classes();
	void signup_classes();
	void report_classes() {
		for (Class* clas : classes) {
			pair<int, int> counter = report_Course_unit_request(clas);
			cout << clas->get_c_title() << ": " << counter.first << "(" << counter.second << ")" << endl;
		}
		cout << endl;
	}
	void report_student() {
		string id;
		cin >> id;
		Student* student = find_id(id);
		if (!student == 0) {
			cout << student->get_name() << ":" << endl;
			report_student_unit(student);
		}
	}



private:

	void report_student_unit(Student* student) {
		for (Course_unit_request* cur : CURs) {
			if (cur->has_s_id_in_request(student)) {
				if (cur->check_status())
					cout << cur->get_c_title_in_re() << endl;
				else
					cout << cur->get_c_title_in_re() << "(w)" << endl;

			}
		}
	}

	vector<Course_unit_request*>  CURs;//course unit request
	vector<Student*> students;
	vector<Class*> classes;
	sign_up_rules rules;

	pair<int, int> report_Course_unit_request(Class* c) {
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

	Student* find_id(string _id) {
		for (Student* student : students) {
			if (student->has_id(_id))
				return student;
		}
		return NULL;
	}

	bool is_s_name_exists(string name) {
		if (students.size() == 0)
			return false;
		for (Student* student : students) {
			if (student->has_name(name))
				return true;
		}
		return false;
	}


	Class* find_class(string code) {
		for (Class* classs : classes) {
			if (classs->has_c_code(code))
				return classs;
		}
		return NULL;
	}


	//find out class is empty or not
	bool is_class_empty(Class* c) {
		int counter = 0;
		for (Course_unit_request* cur : CURs) {
			if (cur->has_c_code_in_request(c))
				counter++;
		}
		if (counter < c->get_c_cap()) {
			return true;
			cout << "class isn't full" << endl;
		}

		else {
			return false;
			cout << "class is full" << endl;

		}

	}

	//del student course
	void del_course_unit_request(Student* s, Class* c) {
		int counter = 0;
		for (Course_unit_request* cur : CURs) {
			if (cur->has_s_id_in_request(s) && cur->has_c_code_in_request(c)) {
				CURs.erase(CURs.begin() + counter);
			}
			counter++;
		}
	}

	//find replace student after increase capacity or someone delete its course
	void find_replace_person(Class* c) {
		int counter = 0;
		for (Course_unit_request* cur : CURs) {
			if (cur->has_c_code_in_request(c) && counter < c->get_c_cap()) {
				cur->bring_in_class();
				counter++;
			}
		}
	}
};

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
			cout << new_capacity;
		}
	}
}

//add student in class
void School::signup_classes() {
	string code, _id;
	cin >> _id >> code;
	Student* student = find_id(_id);
	Class* clas = find_class(code);
	if (!clas == 0 && !student == 0) {//check class and student both founded

		if (!is_student_already_in_class(student, clas)) {// check student isn't in class already
			Course_unit_request* new_CUR = new Course_unit_request(student, clas, is_class_empty(clas));//add student in class or in waiting
			CURs.push_back(new_CUR);

			cout << "added" << endl;
		}
		else {//do nothing
			cout << "student is in class" << endl;
		}

	}
	else {//do nothing
		cout << "class or student not found" << endl;
	}









}

void School::drop_classes() {
	string code, _id;
	cin >> _id >> code;
	Student* student = find_id(_id);
	Class* clas = find_class(code);
	if (!clas == 0 && !student == 0) {//check class and student both founded
		if (is_student_already_in_class(student, clas)) {// check student is in class 
			del_course_unit_request(student, clas);//del student's course
			cout << "deleted" << endl;
			find_replace_person(clas);//find replace student if needed
		}
		else {
			cout << "student isn't in class" << endl;
			//Do nothing
		}

	}
	else {
		cout << "class or student not found" << endl;
		//Do nothing
	}

}

void School::add_new_student(string temp_s_id, string temp_s_name) {
	if (rules.sign_up_new_students_rules(temp_s_id, temp_s_name)) {
		if (!is_s_id_exists(temp_s_id)) {//the id has been used before?
			Student* new_student = new Student(temp_s_name, temp_s_id);
			students.push_back(new_student);
		}
	}
    else{abort();}
}

void School::add_new_class(string code, string title, string cap) {
	if (rules.sign_up_new_class_rules(code, title, cap)) {//check information
		if (!is_c_code_exists(code)) {//check code history doesn't duplicate;
			Class* new_class = new Class(code, title, stoi(cap));
			classes.push_back(new_class);
		}
		else { abort(); }
	}
	else { abort(); }

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

	school.pri();
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


int main() {
    cout<<"j";
	School school;
	get_basic_information(school);//get classes and students
	get_order(school);//get orders

}
