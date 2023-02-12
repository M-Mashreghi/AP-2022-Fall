#pragma once

#include "User.hpp"

class Seller : public User {
	public:
		Seller(std::string _username, std::string _password, std::string _city);
		void increase_unreturnable_revenue(double _unreturnable_revenue) { unreturnable_revenue += _unreturnable_revenue;}
		double get_revenue() { return unreturnable_revenue; }
	private:
		double unreturnable_revenue = 0;
};

