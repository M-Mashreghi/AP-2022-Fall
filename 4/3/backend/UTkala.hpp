#pragma once
#include <utility>
#include <algorithm>
#include <vector>
#include "Buyer.hpp"
#include "Seller.hpp"
#include "Item.hpp"
#include "Read_input.hpp"
#include "Purchased.hpp"
#include "Purchased_card.hpp"
#include "Offer_package.hpp"
#include "Offer_category.hpp"
#include "total_cost_offer.hpp"

class UTkala {
public:
	void run();
	~UTkala();
	string find_part_optional(string part, line command);
	string find_part( string part, line command);
	void signup(string username, string password, string role, string city);
private:
	void logincheck(string username, string password);
	void login_seller_run(Seller* seller);
	void login_buyer_run(Buyer* buyer);
	
	void list_items(Buyer* buyer,string sort_by,string _seller_unsername);

	bool compareInterval(Item i1, Item i2);
	bool is_username_unique( string username);
	Seller* check_seller_info(string username, string password);
	Buyer* check_buyer_info(string username, string password);
	Seller* find_seller(string _username);
	Item* find_item(int id);
	Buyer* find_buyer(string _username);
	bool is_seller_username_exists(string _seller_username);
	bool find_list_items(vector<Item*> filtered_items, vector<Item*>& item_sorted, string _seller_username);
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
	void add_comment(Buyer* buyer, int _id, string _message);
	void add_rate(Buyer* buyer, int _id, int _rate);
	bool buyer_bought_item(Buyer* buyer, Item* item);
	void list_items_type(Buyer* buyer,line command);
	string find_part_second(string part, line command);
	void add_to_cart(Buyer* buyer, int _id, int _count);
	void purchase_cart(Buyer* buyer, string city);
	void package_offer_check(Seller* seller, string _ids, int _discount);
	void category_offer_check(Seller* seller, string _category, int _discount);
	bool check_item_by_category_sellername(string category, string sellername);
	void total_cost_offer_check(Seller* seller, int _cost, int _discount);
	total_cost_offer* find_total_cost_offer(string sellername);
	void delete_offers(Seller* seller, int id, bool id_given);
	void show_list_offers(string sellername);
	int cate_offer_caculater(Item* item);
	int tco_offer_caculater(Item* item, vector<pair<Item*, int>> cards);
	int pak_offer_caculater(Item* item, vector<Item*> item_buy_list);
	bool isSubset(vector<int> arr1, vector<int> arr2, int m, int n);
	int get_item_discount(Item* item, vector<pair<Item*, int>> cards);
	bool bool_find_part(string part, line command);


	 vector<Buyer*> buyers;
	 vector<Seller*> sellers;
	 vector<Item*> items;
	 vector<Purchased_card*> purchased_cards;
	 vector<Purchased*> purchaseds;
	 vector<Offer_package*> offer_packages;
	 vector<Offer_category*> offer_categories;
	 vector<total_cost_offer*> total_cost_offers;
};