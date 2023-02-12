#pragma once
#include "User.hpp"
#include <string>


class Buyer : public User {
	public:
		Buyer(std::string _username, std::string _password, std::string _city);
		void increase_credit(std:: string  _amount);
		void increase_credit(double  _amount);
		void decrease_credit(double  cost);
		double get_amount() const;
		void print_amount()const;
		double can_buy(double total_cost)const;
	private:
		double amount;
};

