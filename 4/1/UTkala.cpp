
#pragma warning(disable : 4996)
#include "Consts.hpp"
#include "UTkala.hpp"
#include "Read_input.hpp"
#include <ctime>
#include <chrono>

using namespace std;

void UTkala::run() {
	line command;
	while (true) {
		command = read_command();
		try {
			if (command.size() == 0) { break; }
			else if (command[0] != POST && command[0] != GET && command[0] != DELETE &&  command[0] != PUT) { throw BAD_REQUEST; }
			else if (command[1] == SignUp) { signup(find_part(USERNAME, command) , find_part(PASSWORD, command) , find_part(ROLE, command) , find_part(CITY, command)); }
			else if (command[1] == LOGIN) { logincheck(find_part(USERNAME, command), find_part(PASSWORD, command)); }
			else { throw NOT_FOUND; }
		}
		catch (string error) { cout << error << endl; }
	}
}

bool UTkala::compareInterval(Item i1, Item i2)
{
	return (i1.get_price() < i2.get_price());
}

bool  UTkala::is_seller_username_exists(string _seller_username) {
	for (Seller* seller : sellers)
		if (seller->is_username_same(_seller_username))
			return true;
	return false;
}

bool UTkala::find_list_items(vector<Item*>& item_sorted, string _seller_username) {
	if (_seller_username == STRING_NULL) {
		for (Item* item : items)
			item_sorted.push_back(item);
		return true;
	}
	else if (is_seller_username_exists(_seller_username)) {
		for (Item* item : items)
			if (item->is_seller_username_same(_seller_username)) {
				item_sorted.push_back(item);
			}
		return true;	
	}
	else
		throw NOT_FOUND;
}

void UTkala::list_items(string sort_by, string _seller_username) {
	vector<Item*> item_sorted;
	if (find_list_items(item_sorted, _seller_username)) {
		if (item_sorted.size() != 0 ) {
			if (sort_by == STRING_NULL)
				print_items(item_sorted,false);
			else if (sort_by == HIGHEST_PRICE) {
				sort(item_sorted.begin(), item_sorted.end(), [](const Item* a, const Item* b) { return !(a->operator<(b)); });
				print_items(item_sorted, false);
			}
			else if (sort_by == LOWEST_PRICE) {
				sort(item_sorted.begin(), item_sorted.end(), [](const Item* a, const Item* b) { return (a->operator<(b)); });
				print_items(item_sorted, false);
			}
			else
				throw BAD_REQUEST;
		}
		else
			throw EMPTY;
	}
	else
		throw NOT_FOUND;
}

void UTkala::login_seller_run(Seller* seller) {
	line command;
	cout << OK;
	while (true) {
		command = read_command();
		try {
			if (command.size() == 0) { break; }
			else if (command[0] != POST && command[0] != GET && command[0] != DELETE && command[0] != PUT) { throw BAD_REQUEST; }
			else if (command[1] == ITEM) { delete_item(seller , stoi(IsInteger(find_part("id", command)))); }
			else if (command[1] == LOGOUT) { cout << OK; break; }
			else if (command[1] == ADD_ITEM) { add_item(seller,command); }
			else if (command[1] == ITEM_QUANTITY) { change_item_quantity(seller, stoi(IsInteger(find_part("id", command))) , stoi(IsInteger(find_part("quantity", command)))); }
			else if (command[1] == ITEM_PRICE) { change_item_price(seller,stoi(find_part("id", command)),stod(IsInteger(find_part("price", command)))); }
			else if (command[1] == REVENUE) { caculate_revenue(seller); }
			else if (command[1] == LIST_ITEMS) { registerd_item_by_seller(seller,find_part_optional("sort_by", command)); }
			else if (command[1] == LIST_TRANSACTIONS) { bought_item_from_seller(seller); }
			else { throw NOT_FOUND; }
		}
		catch (string error) { cout << error << endl; }
	}
	
}

void UTkala::login_buyer_run(Buyer* buyer) {
	line command;
	cout << OK;
	while (true) {
		command = read_command();
		try {
			if (command.size() == 0) { break; }
			else if (command[0] != POST && command[0] != GET && command[0] != DELETE && command[0] != PUT) { throw BAD_REQUEST; }
			else if (command[1] == INCREASE_CREDIT) { buyer->increase_credit(IsInteger(find_part(AMOUNT, command))); }
			else if (command[1] == BUY_ITEM) { buy_item( buyer, stoi(IsInteger(find_part("id", command))), stoi(IsInteger(find_part("count", command))), find_part_optional(CITY, command)); }
			else if (command[1] == WALLET_BALANCE) { buyer->print_amount(); }
			else if (command[1] == REFUND) { refund(buyer,find_part("purchased_id", command)); }
			else if (command[1] == LIST_PURCHASED) { list_purchased(buyer); }
			else if (command[1] == LIST_ITEMS) { list_items(find_part_optional("sort_by", command), find_part_optional("seller_username", command)); }
			else if (command[1] == LOGOUT) { cout << OK; break; }
			else { throw NOT_FOUND; }
		}
		catch (string error) { cout << error << endl; }
	}
}

void UTkala::logincheck(string username , string password) {
	Seller* seller = check_seller_info(username, password);
	Buyer* buyer = check_buyer_info(username, password);
	if (seller != NULL) 
		login_seller_run(seller);
	else if (buyer != NULL) 
		login_buyer_run(buyer);
	else
		throw NOT_FOUND;
}

Seller* UTkala::check_seller_info(string username, string password) {
	for(int i=0 ; i< sellers.size();i++){
		if (sellers[i]->is_username_same(username))
			if (sellers[i]->is_password_same(password))
				return sellers[i];
			else
				throw PERMISSION_DENIED;
	}
	return NULL;
}

Buyer* UTkala::check_buyer_info(string username, string password) {
	for (int i = 0; i < buyers.size(); i++) {
		if (buyers[i]->is_username_same(username))
			if (buyers[i]->is_password_same(password))
				return buyers[i];
			else 
				throw PERMISSION_DENIED;
	}
	return NULL;
}

void UTkala::signup(string username, string password , string role, string city) {
	if (!is_username_unique(username))
		throw BAD_REQUEST;
	if (role == BUYER) {
		Buyer* new_buyer = new Buyer(username, password, city);
		buyers.push_back(new_buyer);
		login_buyer_run(check_buyer_info(username, password));
	}
	else if (role == SELLER) {
		Seller* new_seller = new Seller(username, password, city);
		sellers.push_back(new_seller);
		login_seller_run(check_seller_info(username, password));
	}
	else
		throw BAD_REQUEST;
}

string UTkala::find_part(string part, line command) {
	for (int i = 0; i < command.size(); i++) {
		if (command[i] == part)
			return command[i + 1];
	}
	throw BAD_REQUEST;
}

string UTkala::find_part_optional(string part, line command) {
	for (int i = 0; i < command.size(); i++) {
		if (command[i] == part)
			return command[i + 1];
	}
	return STRING_NULL;
}

bool UTkala::is_username_unique(string username) {
	bool is_unique = false;
	try { find_seller(username); }
	catch (string error) {
		try { find_buyer(username); }
		catch (string error) { is_unique = true; }
	}
	return is_unique;
}

Seller* UTkala::find_seller(string _username){
	for (Seller* seller :sellers) {
		if (seller->is_username_same(_username))
			return seller;
	}
	throw NOT_FOUND;
}

Buyer* UTkala::find_buyer(string _username) {
	for (Buyer* buyer : buyers) {
		if (buyer->is_username_same(_username))
			return buyer;
	}
	throw NOT_FOUND;

}

Item* UTkala::find_item(int id) {
	for (Item* item : items) {
		if (item->is_id_same(id))
			return item;
	}
	throw NOT_FOUND;
}

void UTkala::print_items(vector<Item*> itemss, bool seller){
	for (Item* item : itemss) {
		if(seller)
			item->print_info_seller();
		else
			item->print_info();
	}
}

void UTkala::buy_item(Buyer* buyer,int _id, int count, string _city) {
	Item* item_buy = find_item(_id);
	if (count < item_buy->get_quantity()) {
		double delivery_cost = caculate_delivery_cost(buyer, item_buy, count, _city);
		double total_cost = count * item_buy->get_price() + delivery_cost;
		if(buyer->can_buy(total_cost)) {
			buyer->decrease_credit(total_cost);
			item_buy->decrease_quantity(count);
			cout << "total_cost : " << total_cost << endl;
			auto  now = chrono::system_clock::now();
			time_t current_time = chrono::system_clock::to_time_t(now);
			Purchased* new_purchased = new Purchased(ctime(&current_time), item_buy->get_id(),
				item_buy->get_name(), item_buy->get_price(), count, delivery_cost, total_cost,
				item_buy->get_seller()->get_username(), buyer->get_username());
			purchaseds.push_back(new_purchased);
		}	
		else 
			throw BAD_REQUEST;
	}
	else 
		throw BAD_REQUEST;
}

double UTkala::caculate_delivery_cost(Buyer* buyer, Item* item_buy, int count, string _city_op) {
	if (_city_op != STRING_NULL) {
		if(item_buy->get_seller()->is_city_same(_city_op)) 
			return  INSIDE_the_city;
		else 
			return  OUTSIDE_the_city;
	}
	else {
		if (item_buy->get_seller()->is_city_same(buyer->get_city())) 
			return  INSIDE_the_city;
		else 
			return  OUTSIDE_the_city;
	}
}

void UTkala::list_purchased(Buyer* buyer) {
	int count = 0;
	for (Purchased* purchased : purchaseds) {
		if (buyer->is_username_same(purchased->get_purchased_buyer_usename())) {
			purchased->print_info();
			count++;
		}
	}
	if (count == 0) {
		throw EMPTY;
	}
}

void UTkala::refund(Buyer* buyer,string _purchased_id) {
	Purchased* purchased = find_purchased(stoi(_purchased_id));
	Item* item_purchased = find_item(purchased->get_purchased_item_id());
	if (item_purchased->get_refund_percentage() != 0 ) {
		if (buyer->get_username() == purchased->get_purchased_buyer_usename()) {
			buyer->increase_credit((item_purchased->get_refund_percentage())*((purchased->get_purchased_total_cost() - purchased->get_purchased_delivery_cost()))/100);
			item_purchased->get_seller()->increase_unreturnable_revenue(((100 - (item_purchased->get_refund_percentage())) * ((purchased->get_purchased_total_cost() - purchased->get_purchased_delivery_cost()))/100 + ((purchased->get_purchased_delivery_cost()))));
			item_purchased->increase_quantity(purchased->get_purchased_count());
			item_purchased->decrease_purchased_quantity(purchased->get_purchased_count());
			purchaseds.erase(purchaseds.begin() + find_del_position_purchased(purchased->get_purchased_id()));
			cout << OK;
		}
		else
			throw PERMISSION_DENIED;
	}
	else 
		throw BAD_REQUEST;
}

Purchased* UTkala::find_purchased(int id) {
	for (Purchased* purchased : purchaseds) {
		if (purchased->is_id_same(id))
			return purchased;
	}
	throw NOT_FOUND;
}

int UTkala::find_del_position_purchased(int _id) {
	int count = 0;
	for (Purchased* purchased : purchaseds) {
		if (purchased->get_purchased_id() != _id)
			count++;
		else
			return count;
	}
	return count;
}

int UTkala::find_del_position_item(int _id) {
	int count = 0;
	for (Item* item : items) {
		if (item->get_id() != _id)
			count++;
		else
			return count;
	}
	return count;
}

void UTkala::delete_item(Seller* seller, int _item_id) {
	Item* item_del = find_item(_item_id);
	if (item_del->is_seller_username_same(seller->get_username())) {
		items.erase(items.begin() + find_del_position_item(_item_id));
		cout << OK;
	}
	else
		throw PERMISSION_DENIED;
}

void UTkala::add_item(Seller* seller, line command) {
	string item_name = find_part("name", command);
	double item_price = stod(IsInteger(find_part("price", command)));
	string item_category = find_part("category", command);
	int item_quantity = stoi(IsInteger(find_part("quantity", command)));
	int item_refund = stoi(IsInteger(find_part_optional(REFUND, command)));
	if (!is_item_name_unique(item_name)) {
		if (item_price > 0 && item_quantity > 0) {
			cout << "id : " << Item::get_current_Id() << endl;
			auto  now = chrono::system_clock::now();
			time_t current_time = chrono::system_clock::to_time_t(now);
			Item* new_item = new Item(item_name, seller, item_category, ctime(&current_time) , item_price, item_quantity, 0, item_refund);
			items.push_back(new_item);
		}
		else
			throw BAD_REQUEST;
	}
	else
		throw BAD_REQUEST;
}

void UTkala::change_item_quantity(Seller* seller, int _id, int quantity) {
	Item* item = find_item(_id);
	if (item->is_seller_username_same(seller->get_username())) {
		if (quantity > 0) {
			item->change_quantity(quantity);
			cout << OK;
		}
		else
			throw BAD_REQUEST;
	}
	else
		throw PERMISSION_DENIED;
}

void UTkala::change_item_price(Seller* seller, int _id, double _price) {
	Item* item = find_item(_id);
	if (item->is_seller_username_same(seller->get_username())) {
		if (_price > LEAST_prtice) {
			item->change_price(_price);
			cout <<OK;
		}
		else
			throw BAD_REQUEST;
	}
	else
		throw PERMISSION_DENIED;
}

void UTkala::registerd_item_by_seller(Seller* seller, string sort_by) {
	vector<Item*> item_sorted;
	if (find_list_items(item_sorted, seller->get_username())) {
		if (item_sorted.size() != 0) {
			if (sort_by == STRING_NULL)
				print_items(item_sorted , true);
			else if (sort_by == HIGHEST_PRICE) {
				sort(item_sorted.begin(), item_sorted.end(), [](const Item* a, const Item* b) { return !(a->operator<(b)); });
				print_items(item_sorted, true);
			}
			else if (sort_by == LOWEST_PRICE) {
				sort(item_sorted.begin(), item_sorted.end(), [](const Item* a, const Item* b) { return (a->operator<(b)); });
				print_items(item_sorted, true);
			}
			else
				throw BAD_REQUEST;
		}
		else
			throw EMPTY;
	}
	else
		throw BAD_REQUEST;
}

bool UTkala::is_item_name_unique(string _item_name) {
	for (Item* item : items)
		if (item->is_name_same(_item_name))
			return true;
	return false;
}

void UTkala::bought_item_from_seller(Seller* seller) {
	int count = 0 ;
	for(Purchased* purchased : purchaseds)
		if (seller->is_username_same(purchased->get_purchased_seller_usename())) {
			purchased->print_info();
			count++;
		}
	if (count == 0)
		throw EMPTY;
}

void UTkala::caculate_revenue(Seller* seller) {
	double revenue = seller->get_revenue();
	for (Purchased* purchased : purchaseds)
		if (seller->is_username_same(purchased->get_purchased_seller_usename())) {
			revenue += purchased->get_purchased_count() * purchased->get_purchased_item_price() + purchased->get_purchased_delivery_cost();
		}
	cout << "total revenue : " << revenue << endl;
}

UTkala::~UTkala() {
	for (Buyer* buyer : buyers)
		delete buyer;
	buyers.clear();
	for (Seller* seller : sellers)
		delete seller;
	sellers.clear();
	for (Item* item : items)
		delete item;
	items.clear();
	for (Purchased* purchased : purchaseds)
		delete purchased;
	purchaseds.clear();
}