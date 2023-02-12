#include "User.hpp"

using namespace std;

User::User(string _username, string _password, string _city): username(_username) ,password(_password) ,city(_city) {}

string User::get_username() const {
	return username;
}

string User::get_password() const {
	return password;
}

string User::get_city() const {
	return city;
}

bool User::is_username_same(string _username) {
	if (username == _username)
		return true;
	return false;
}

bool User::is_password_same(std::string _password) {
	if (password == _password)
		return true;
	return false;
}

bool User::is_city_same(std::string _city) {
	if (city == _city)
		return true;
	return false;
}
