#pragma once
#include <algorithm>
#include <vector>
#include "Buyer.hpp"
#include "Seller.hpp"
#include "Item.hpp"
#include "Read_input.hpp"
using namespace std;


class Purchased
{
public:
	Purchased(string _date, int _item_id, string _item_name, double _item_price, int _purchased_count
			, double _delivery_cost, double _total_cost, string _seller_usename,string _buyer_usename);
	void print_info();
	bool is_id_same(int _id) { return id==_id; };
	int get_purchased_id() {return id;}
	string get_purchased_date() { return date; }
	int get_purchased_item_id() { return item_id; }
	string get_purchased_item_name() { return item_name; }
	double get_purchased_item_price() { return item_price; }
	int get_purchased_count() { return purchased_count; }
	double get_purchased_delivery_cost() { return delivery_cost; }
	double get_purchased_total_cost() { return total_cost; }
	string get_purchased_seller_usename() { return seller_usename; }
	string get_purchased_buyer_usename() { return buyer_usename; }
	static void Increase_Id() {current_registerd_purchased++;};
	void purchase_cart(Buyer* buyer, string city);
private:
	int id;
	string date;
	int item_id;
	string item_name;
	double item_price;
	int purchased_count;
	double delivery_cost;
	double total_cost;
	string seller_usename;
	string buyer_usename;
	static int current_registerd_purchased ;
};

