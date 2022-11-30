
#include "sign_up_rules.hpp"



	bool sign_up_rules::is_s_id_ok(string _id) {
		if (_id.length() < 6)//check length
			return false;

		if (!is_num_format_ok(_id))
			return false;
		return true;
	}

	bool sign_up_rules::is_s_name_ok(string _name) {
		if (_name == "")
			return false;
		else
			return true;
	}

	bool sign_up_rules::is_num_format_ok(string num) {
		for (int i = 0; i < num.length(); i++) {
			if (!(num[i] == '0' || num[i] == '1' || num[i] == '2' ||
				num[i] == '3' || num[i] == '4' || num[i] == '5' ||
				num[i] == '6' || num[i] == '7' || num[i] == '8' || num[i] == '9')) {
				return false;
			}
		}
		return true;
	}


bool sign_up_rules::sign_up_new_students_rules(School* school, string temp_s_id, string temp_s_name) {

		if (!is_s_name_ok(temp_s_name) || !is_s_id_ok(temp_s_id))//check name and id
			return false;

		if (school->is_s_id_exists(temp_s_id))//the id has been used before?
			return false;

		return true;
}


bool sign_up_rules::sign_up_student_in_class_rules(School* school, Student* student, Class* clas) {
	if (!clas == 0 && !student == 0) {//check class and student both founded

		if (!school->is_student_already_in_class(student, clas)) {// check student isn't in class already
			//cout << "added" << endl;
			return true;
		}
		else {
			//cout << "student is in class" << endl;
			return false;
		}

	}
	else {
		//cout << "class or student not found" << endl;
		return false;
	}

}

bool sign_up_rules::sign_up_new_class_rules(School* school, string code, string title, string cap) {
	if (!is_num_format_ok(cap) || !is_num_format_ok(code))//check format
		return false;

	if (stoi(cap) <= 0 || (code.length() != 2))//check capicity & code lenght
		return false;

	if (title == "")//check title
		return false;

	if (school->is_c_code_exists(code))//check code history doesn't duplicate;
		return false;

	return true;
}





bool sign_up_rules::drop_classes_rules(School* school, Student* student, Class* clas) {
	if (!clas == 0 && !student == 0) {//check class and student both founded
		if (school->is_student_already_in_class(student, clas)) {// check student is in class 
			return true;
		}
		else {
			//cout << "student isn't in class" << endl;
			return false;
		}

	}
	else {
		//cout << "class or student not found" << endl;
		return false;
	}
}










