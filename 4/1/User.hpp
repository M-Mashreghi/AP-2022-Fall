#pragma once

#include <string>

class User {
public:
	User(std::string _username, std::string _password, std::string _city);
	std::string get_username();
	std::string get_password();
	std::string get_city();
	bool is_username_same(std::string _username);
	bool is_password_same(std::string _password);
	bool is_city_same(std::string _city);
protected:
	std::string username;
	std::string password;
	std::string city;
};