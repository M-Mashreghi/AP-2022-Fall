#include "Course_unit_request.hpp"





Course_unit_request::Course_unit_request(Student* s, Class* c, bool statuse) {
	_student = s;
	_clas = c;
	_statuse = statuse;
	if (statuse == false) {
		//cout << "full";
	}
}
void Course_unit_request::bring_in_class() { _statuse = true; }

bool Course_unit_request::has_s_id_in_request(Student* s) { return(_student->get_id() == s->get_id()); }
bool Course_unit_request::has_c_code_in_request(Class* c) { return(_clas->get_c_code() == c->get_c_code()); }
string Course_unit_request::get_s_name_in_re() { return _student->get_id(); }
string Course_unit_request::get_c_code_in_re() { return _clas->get_c_code(); }
string Course_unit_request::get_c_title_in_re() { return _clas->get_c_title(); }
int Course_unit_request::get_c_cap_in_re() { return _clas->get_c_cap(); }
bool Course_unit_request::check_status() { return _statuse; }