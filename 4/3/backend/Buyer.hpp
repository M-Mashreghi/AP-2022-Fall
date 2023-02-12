#pragma once
#include "User.hpp"
#include <array>
#include "Filter.hpp"
#include "Rate_filter.hpp"
#include "Price_filter.hpp"
#include "Category_filter.hpp"
 
 
class Item;
class Rate_filter;
class Price_filter;
class Category_filter;
class Buyer : public User {
	public:
		Buyer(std::string _username, std::string _password, std::string _city);
		void increase_credit(std:: string  _amount);
		void increase_credit(double  _amount);
		void decrease_credit(double  cost);
		double get_amount() const;
		void print_amount()const;
		vector<pair< Item*, int>> get_cards() { return cards; };
		double can_buy(double total_cost)const;
		void add_to_cart_buyer(Item* item, int _count);
		void DELETE_cart() { cards.clear(); }
		void rate_filter_new(int _min_rating, int _max_rating);
		void price_filter_new(int _min_price, int _max_price);
		void category_filter_new(string _category);
		void delete_filters();
		vector<Item*> filter_list_items(vector<Item*> item);
	private:
		double amount;
		vector<pair<Item*, int>> cards;
		Rate_filter* rate_filter;
		Price_filter* price_filter;
		Category_filter* category_filter;
};

