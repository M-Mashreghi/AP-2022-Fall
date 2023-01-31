#pragma once

#include <algorithm>
#include <vector>
#include "Buyer.hpp"
#include "Seller.hpp"
#include "Item.hpp"
#include "Read_input.hpp"
#include "Purchased.hpp"

class UTkala {
public:
	void run();
	~UTkala();
private:
	void logincheck(string username, string password);
	void login_seller_run(Seller* seller);
	void login_buyer_run(Buyer* buyer);
	void signup(string username, string password, string role, string city);
	void list_items(string sort_by,string _seller_unsername);
	string find_part_optional(string part, line command);
	string find_part( string part, line command);
	bool compareInterval(Item i1, Item i2);
	bool is_username_unique( string username);
	Seller* check_seller_info(string username, string password);
	Buyer* check_buyer_info(string username, string password);
	Seller* find_seller(string _username);
	Item* find_item(int id);
	Buyer* find_buyer(string _username);
	bool is_seller_username_exists(string _seller_username);
	bool find_list_items(vector<Item*>& item_sorted, string _seller_username);
	void print_items(vector<Item*> itemss ,bool seller);
	double caculate_delivery_cost(Buyer* buyer, Item* item_buy, int count, string _city_op);
	void buy_item(Buyer* buyer, int _id, int count, string _city);
	void list_purchased(Buyer* buyer);
	void refund(Buyer* buyer,string _purchased_id);
	Purchased* find_purchased(int id);
	int find_del_position_purchased(int _id);
	int find_del_position_item(int _id);
	void delete_item(Seller* seller, int _item_id);
	void add_item(Seller* seller, line command);
	void registerd_item_by_seller(Seller* seller, string sort_by);
	void change_item_quantity(Seller* seller, int _id, int quantity);
	void change_item_price(Seller* seller, int _id, double _price);
	bool is_item_name_unique(string _item_name);
	void bought_item_from_seller(Seller* seller);
	void caculate_revenue(Seller* seller);
	 vector<Buyer*> buyers;
	 vector<Seller*> sellers;
	 vector<Item*> items;
	 vector<Purchased*> purchaseds;
};
