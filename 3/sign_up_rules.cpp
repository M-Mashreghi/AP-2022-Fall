
#include "sign_up_rules.hpp"
const int id_size = 6;
const int Code_Length = 2;

	bool sign_up_rules::is_s_id_ok(string _id) {
		if (_id.length() < id_size)
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
				num[i] == '6' || num[i] == '7' || num[i] == '8' || num[i] == '9')) 
				return false;
		}
		return true;
	}


bool sign_up_rules::sign_up_new_students_rules(School* school, string temp_s_id, string temp_s_name) {
		if (!is_s_name_ok(temp_s_name) || !is_s_id_ok(temp_s_id))
			return false;
		if (school->is_s_id_exists(temp_s_id))
			return false;
		return true;
}


bool sign_up_rules::sign_up_student_in_class_rules(School* school, Student* student, Class* clas) {
	if (clas != NULL && student != NULL) {
		if (!school->is_student_already_in_class(student, clas))
			return true;
		else 
			return false;
	}
	else 
		return false;
}

bool sign_up_rules::sign_up_new_class_rules(School* school, string code, string title, string cap) {
	if (!is_num_format_ok(cap) || !is_num_format_ok(code))
		return false;
	if (stoi(cap) <= 0 || (code.length() != Code_Length))
		return false;
	if (title == "")
		return false;
	if (school->is_c_code_exists(code))
		return false;
	return true;
}





bool sign_up_rules::drop_classes_rules(School* school, Student* student, Class* clas) {
	if (clas != NULL && student != NULL) {
		if (school->is_student_already_in_class(student, clas)) 
			return true;
		else 
			return false;
	}
	else 
		return false;
}
