#pragma once

#include <string>

class User {
public:
	User(std::string _username, std::string _password, std::string _city);
	std::string get_username() const;
	std::string get_password() const;
	std::string get_city() const;
	bool is_username_same(std::string _username);
	bool is_password_same(std::string _password);
	bool is_city_same(std::string _city);
protected:
	std::string username;
	std::string password;
	std::string city;
};