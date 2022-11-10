#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include <algorithm>   

using namespace std;

typedef vector<vector<string>> CONTACTS;

//typedef Contact[phone_locaton] PHONES;


const int Initial_ID = 0;
const int id_locaton = 0;
const int fname_locaton = 1;
const int lname_locaton = 2;
const int phone_locaton = 3;
const int email_locaton = 4;
const string ATSIGN = "@";
const char DOT = '.';


//declaration:
void delete_user(CONTACTS& Contact);
void app();
void command_ok();
void command_failed();
vector<int> findLocationofdot(string domain);
bool domain_check(vector<int> findLocationofdot, string domain);
bool check_email(vector<string>& temp, int num);
bool check_phone(string num);
int find_phone(vector<string>& temp);
int find_fname(vector<string>& temp);
int find_lname(vector<string>& temp);
int find_email(vector<string>& temp);
bool get_contact_information(string& f_name, string& l_name, string& phone, string& email);
void save_contact_information(CONTACTS& Contact, string& f_name, string& l_name, string& phone, string& email, int& id);
void add_contact(CONTACTS& Contact, int& id);
void call_app_functions(CONTACTS& Contact, string command, int& id);
string get_command(string command);
bool check_duplicate_email(vector<string >& EMAILS, string& email_new);
bool check_duplicate_details(CONTACTS& Contact, string& f_name, string& l_name, string& phone, string& email);
bool check_duplicate_name(vector<string >& F_Names, vector<string >& L_Names, string& fname_new, string& lname_new);
bool check_duplicate_phone(vector<string >& PHONES, string& phone_new);
void print_search(const CONTACTS& Contact, const vector<int>& founded);
void delete_duplicate_search_found(vector<int>& founded);

int main()
{
	//the app
	app();
}

//print ok
void command_ok() {
	cout << "Command OK" << endl;
}
//print fail
void command_failed() {
	cout << "Command Failed" << endl;
}

//find all the DOTs in the domain of Email in sign up and return it
vector<int> findLocationofdot(string domain)
{
	vector<int> character_Locations_of_dot;
	for (int i = 0; i < domain.size(); i++)
		if (domain[i] == DOT)
			character_Locations_of_dot.push_back(i);
	return character_Locations_of_dot;
}

//check domain part of email
bool domain_check(vector<int> findLocationofdot, string domain) {
	//check dot positions
	int temp = NULL;

	//check atleast be one letter between two dots 
	for (int i = 0; i < findLocationofdot.size(); i++) {
		if ((findLocationofdot[i] - temp) == 1) {
			return false;
		}
		temp = findLocationofdot[i];
	}

	//check frist and last letter of domain ,the domain shoudn't start or end with dot
	if (domain[0] == DOT || domain[domain.length() - 1] == DOT) {
		return false;
	}
	return true;
}

bool check_email(vector<string>& temp, int num) {
	size_t atsign_location = temp[num].find(ATSIGN);

	// find name part of email
	string name = temp[num].substr(0, temp[num].find(ATSIGN));
	// find name part of email
	string domain = temp[num].substr(temp[num].find(ATSIGN) + 1, temp[num].length() - 1);
	//check name part(it's length =! 0 )
	if (name.length() == 0) { return false; }
	//check domain part
	if (!domain_check(findLocationofdot(domain), domain)) { return false; }
	return true;
}

bool check_phone(string num) {

	//check format
	for (int i = 0; i < num.length()  ; i++) {
		if (!(num[i] == '0' || num[i] == '1' || num[i] == '2' ||
			num[i] == '3' || num[i] == '4' || num[i] == '5' ||
			num[i] == '6' || num[i] == '7' || num[i] == '8' || num[i] == '9')) {
			return false;
		}
	}

	//check length and the first and second letter
	if (num.length() == 11 && num[0] == '0' && num[1] == '9') {  return true; }

	//phone num is ok
	else
		return false;
}

//find phone position
int find_phone(vector<string>& temp) {
	string check_phone = "-p";
	int i = 0;
	for (i = 0; i < 7; i = i + 2) {
		if (temp[i] == check_phone)
			break;
	}
	return i + 1;
}

//find fname position
int find_fname(vector<string>& temp) {
	string check_fname = "-f";
	int i = 0;
	for (i = 0; i < 7; i = i + 2) {
		if (temp[i] == check_fname)
			break;
	}
	return i + 1;
}

//find lname position
int find_lname(vector<string>& temp) {
	string check_lname = "-l";
	int i = 0;
	for (i = 0; i < 7; i = i + 2) {
		if (temp[i] == check_lname)
			break;
	}
	return i + 1;
}

//find email position
int find_email(vector<string>& temp) {
	string check_email = "-e";
	int i = 0;
	for (i = 0; i < 7; i++) {
		if (temp[i] == check_email)
			break;
	}
	return i + 1;
}

bool get_contact_information(string& f_name, string& l_name, string& phone, string& email) {
	vector<string> temp(8);

	//get all information
	for (int i = 0; i < temp.size(); i++)
	{
		cin >> temp[i];
	}
	//check we got all data!
	if (find_phone(temp) == 8 || find_fname(temp) == 8 ||
		find_lname(temp) == 8 || find_email(temp) == 8)
	{
		 return false;
	}

	//check Email and Phone number
	if (!check_phone(temp[find_phone(temp)]) || !check_email(temp, find_email(temp)))
	{
		return false;
	}

	//save data for next process
	phone = temp[find_phone(temp)];
	f_name = temp[find_fname(temp)];
	l_name = temp[find_lname(temp)];
	email = temp[find_email(temp)];

	return true;
}

//save information in database
void save_contact_information(CONTACTS& Contact, string& f_name, string& l_name, string& phone, string& email,int& id) {
	Contact[id_locaton].push_back(to_string(id));
	Contact[fname_locaton].push_back(f_name);
	Contact[lname_locaton].push_back(l_name);
	Contact[phone_locaton].push_back(phone);
	Contact[email_locaton].push_back(email);
}

//check email duplicate
bool check_duplicate_email(vector<string >& EMAILS, string& email_new) {

	for (int i = 0; i < EMAILS.size(); i++) {
		if (EMAILS[i] == email_new) {//check email deplicate
			return false;// email is duplicated
		}
	}
	return true;//email is new
}

//check phone duplicate
bool check_duplicate_phone(vector<string >& PHONES, string& phone_new) {

	for (int i = 0; i < PHONES.size(); i++) {
		if (PHONES[i] == phone_new) {//check phone deplicate
			return false;//phone num is duplicated
		}
	}
	return true;//phone num is new
}


//check name duplicate
bool check_duplicate_name(vector<string >& F_Names, vector<string >& L_Names, string& fname_new, string& lname_new) {
	for (int i = 0; i < F_Names.size(); i++) {
		if (F_Names[i] == fname_new)//check fname
			if (L_Names[i] == lname_new) //check lname
				return false;// the name was duplicated
	}
	return true;//the name is new
}


//check all names , phones , emails didn't duplicate with new contact's details
bool check_duplicate_details(CONTACTS& Contact, string& f_name, string& l_name, string& phone, string& email) {

	//founded sth
	if(!check_duplicate_name(Contact[fname_locaton], Contact[lname_locaton], f_name, l_name) ||
	!check_duplicate_phone(Contact[phone_locaton], phone) ||
		!check_duplicate_email(Contact[email_locaton], email)) 
		return false;
	
	//nothing founded
	else  return true; 
}

void add_contact(CONTACTS& Contact,int& id) {
	//get new contact information
	string f_name, l_name, phone, email;

	//get information and check phone and email
	if (!get_contact_information(f_name, l_name, phone, email) )
		command_failed();
	//check the information does'nt repeated
	else if (!check_duplicate_details(Contact, f_name, l_name, phone, email)) 
		command_failed();
	//every things ok,save the new information
	else {
		save_contact_information(Contact, f_name, l_name, phone, email,id);//save information in 2d vector
		id++;//setting new id for the next sign up
		command_ok();//everythings is allright
	}
}


void search_email(CONTACTS& Contact, vector<int>& founded, string search_word) {
	for (int i = 0; i < Contact[email_locaton].size(); i++) {
		size_t found = Contact[email_locaton][i].find(search_word);
		if (found != string::npos)
			founded.push_back(i);
	}
}

void search_phone(CONTACTS& Contact, vector<int>& founded, string search_word) {
	for (int i = 0; i < Contact[phone_locaton].size(); i++) {
		size_t found = Contact[phone_locaton][i].find(search_word);
		if (found != string::npos)
			founded.push_back(i);
	}
}

void search_fname(CONTACTS& Contact, vector<int>& founded, string search_word) {
	for (int i = 0; i < Contact[fname_locaton].size(); i++) {
		size_t found = Contact[fname_locaton][i].find(search_word);
		if (found != string::npos)
			founded.push_back(i);
	}
}

void search_lname(CONTACTS& Contact, vector<int>& founded, string search_word) {
	for (int i = 0; i < Contact[lname_locaton].size(); i++) {
		size_t found = Contact[lname_locaton][i].find(search_word);
		if (found != string::npos)
			founded.push_back(i);
	}
}

//delete the id if users that founded more than once
void delete_duplicate_search_found(vector<int>& founded) {

	auto end = founded.end();
	for (auto it = founded.begin(); it != end; ++it) {
		end = remove(it + 1, end, *it);
	}

	founded.erase(end, founded.end());
}


//print search result
void print_search(const CONTACTS& Contact, const vector<int>& founded) {
	for (auto i : founded) {
		cout << Contact[id_locaton][i] << " ";
		cout << Contact[fname_locaton][i] << " ";
		cout << Contact[lname_locaton][i] << " ";
		cout << Contact[phone_locaton][i] << " ";
		cout << Contact[email_locaton][i] << endl;
	}
}

//search user
void search_user(CONTACTS& Contact) {
	string search_word;
	cin >> search_word;
	vector<int> founded;//id of user that have been found
	search_fname(Contact, founded, search_word);//search key word in fnames
	search_lname(Contact, founded, search_word);//search key word in lnames
	search_email(Contact, founded, search_word);//search key word in emails
	search_phone(Contact, founded, search_word);//search key word in phones
	delete_duplicate_search_found(founded);//delete the id if users that founded more than once
	sort(founded.begin(), founded.end());//sort list to get ready for print
	print_search(Contact, founded);//print founded user
}

//check del_id exists in contacts
bool is_id_exist(CONTACTS& Contact, int& delete_id) {
	for (int i = 0; i < Contact[id_locaton].size(); i++) {
		if (to_string(delete_id) == Contact[id_locaton][i]) {
			return true;
		}
	}
	return false;
}

//del use with id  of user
void delete_user(CONTACTS& Contact) {
	int delete_id;
	cin >> delete_id;//get id

	//del id must be positive and less than the size of all id
	if (delete_id < 0 && delete_id >= Contact[id_locaton].size()) { command_failed(); }

	//check del_id exists in contacts
	else if (!is_id_exist(Contact, delete_id)) { command_failed(); }

	//user founded ,starts deleting 
	else {
		Contact[id_locaton].erase(Contact[id_locaton].begin() + delete_id);
		Contact[fname_locaton].erase(Contact[fname_locaton].begin() + delete_id);
		Contact[lname_locaton].erase(Contact[lname_locaton].begin() + delete_id);
		Contact[phone_locaton].erase(Contact[phone_locaton].begin() + delete_id);
		Contact[email_locaton].erase(Contact[email_locaton].begin() + delete_id);
		command_ok();
	}
}


//call the command order
void call_app_functions(CONTACTS& Contact, string command, int& id) {
	if (command == "add") { add_contact(Contact, id); }//add - f firstName - l lastName - p phone - e email
	else if (command == "search") { search_user(Contact); }
	else if (command == "delete") { delete_user(Contact); }
	else command_failed();
}


//get command , check  and return it
string get_command(string command) {
	cin >> command;
	return command;
}


void app() {
	string command;
	int id = Initial_ID;
	CONTACTS  Contact = { {} , {} , {}, {}, {} };//{ {id} , {f_names} , {l_names}, {phones}, {emails} }
	//running app
	while (true) {
		call_app_functions(Contact, get_command(command), id);
	}
}
