#pragma warning(disable : 4996)

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
			else if (command[0] != "POST" && command[0] != "GET" && command[0] != DELETE &&  command[0] != PUT) { throw BAD_REQUEST; }
			else if (command[1] == SignUp) { signup(find_part(USERNAME, command) , find_part(PASSWORD, command) , find_part(ROLE, command) , find_part(CITY, command)); }
			else if (command[1] == LOGIN) { logincheck(find_part(USERNAME, command), find_part(PASSWORD, command)); }
			else { throw BAD_REQUEST; }
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

bool UTkala::find_list_items(vector<Item*> filtered_items,vector<Item*>& item_sorted, string _seller_username) {
	
	if (_seller_username == STRING_NULL) {
		for (Item* item : filtered_items)
			item_sorted.push_back(item);
		return true;
	}
	else if (is_seller_username_exists(_seller_username)) {
		for (Item* item : filtered_items)
			if (item->is_seller_username_same(_seller_username)) {
				item_sorted.push_back(item);
			}
		return true;	
	}
	else
		throw NOT_FOUND;
}

void UTkala::list_items(Buyer* buyer,string sort_by, string _seller_username) {
	vector<Item*> item_sorted;
	vector<Item*> filtered_items = buyer->filter_list_items(items);
	if (find_list_items(filtered_items,item_sorted, _seller_username)) {
		if (item_sorted.size() != NULL) {
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
			else if (command[0] != "POST" && command[0] != "GET" && command[0] != DELETE && command[0] != PUT) { throw BAD_REQUEST; }
			else if (command[1] == ITEM) { delete_item(seller , stoi(IsInteger(find_part("id", command)))); }
			else if (command[1] == LOGOUT) { cout << OK; break; }
			else if (command[1] == ADD_ITEM) { add_item(seller,command); }
			else if (command[1] == ITEM_QUANTITY) { change_item_quantity(seller, stoi(IsInteger(find_part("id", command))) , stoi(IsInteger(find_part("quantity", command)))); }
			else if (command[1] == ITEM_PRICE) { change_item_price(seller,stoi(find_part("id", command)),stod(IsInteger(find_part("price", command)))); }
			else if (command[1] == REVENUE) { caculate_revenue(seller); }
			else if (command[1] == LIST_ITEMS) { registerd_item_by_seller(seller,find_part_optional("sort_by", command)); }
			else if (command[1] == LIST_TRANSACTIONS) { bought_item_from_seller(seller); }

			else if (command[1] == "package_offer") { package_offer_check(seller, find_part("id", command), stoi(IsInteger(find_part("discount", command)))); }
			else if (command[1] == "category_offer") { category_offer_check(seller, find_part("category", command), stoi(IsInteger(find_part("discount", command)))); }
			else if (command[1] == "total_cost_offer") { total_cost_offer_check(seller, stoi(IsInteger(find_part("cost", command))), stoi(IsInteger(find_part("discount", command)))); }
			else if (command[1] == "offers") { delete_offers(seller, stoi(IsInteger(find_part_optional("id", command))), bool_find_part("id", command)); }


			else { throw BAD_REQUEST; }
		}
		catch (string error) { cout << error << endl; }
	}
	
}

bool UTkala::bool_find_part(string part, line command) {
	for (int i = 0; i < command.size(); i++) {
		if (command[i] == part)
			return true;
	}
	return false;
}


void UTkala::delete_offers(Seller* seller,int id,bool id_given) {
	bool deleted = false;
	bool id_finded = false;
	if (!id_given) {
		for (Offer_package* offer_package : offer_packages) {
			if (offer_package->get_seller_set_offer() == seller->get_username()) {
				delete offer_package;
				deleted = true;
			}
		}
		for (Offer_category* offer_category : offer_categories) {
			if (offer_category->get_seller_set_offer() == seller->get_username()) {
				delete offer_category;
				deleted = true;
			}
		}
		for (total_cost_offer* total_cost_offerr : total_cost_offers) {
			if (total_cost_offerr->get_seller_set_offer() == seller->get_username()) {
				delete total_cost_offerr;
				deleted = true;
			}
		}
	}
	else {
		for (Offer_package* offer_package : offer_packages) {
			if (offer_package->get_id() == id) {
				id_finded = true;
				if (offer_package->get_seller_set_offer() == seller->get_username()) {
					delete offer_package;
					deleted = true;
				}
				else
					throw PERMISSION_DENIED;
			}
		}
		for (Offer_category* offer_category : offer_categories) {
			if (offer_category->get_id() == id) {
				id_finded = true;
				if (offer_category->get_seller_set_offer() == seller->get_username()) {
					delete offer_category;
					deleted = true;
				}
				else
					throw PERMISSION_DENIED;
			}
		}
		for (total_cost_offer* total_cost_offerr : total_cost_offers) {
			if (total_cost_offerr->get_id() == id) {
				id_finded = true;
				if (total_cost_offerr->get_seller_set_offer() == seller->get_username()) {
					delete total_cost_offerr;
					deleted = true;
				}
				else
					throw PERMISSION_DENIED;
			}
		}
	}
	if (deleted) {
		cout << OK;
	}
	else if (!id_finded) {
		throw NOT_FOUND;
	}
	else
		throw BAD_REQUEST;
}

void UTkala::total_cost_offer_check(Seller* seller, int _cost, int _discount) {
	total_cost_offer* total_cost_offerr = find_total_cost_offer(seller->get_username());
	if (total_cost_offerr == NULL) {
		total_cost_offer* new_total_cost_offer = new total_cost_offer(seller->get_username(), _cost, _discount);
		total_cost_offers.push_back(new_total_cost_offer);
		cout << OK;
	}
	else
		throw BAD_REQUEST;
}
total_cost_offer* UTkala::find_total_cost_offer(string sellername) {
	for (auto tco : total_cost_offers) {
		if (tco->get_seller_set_offer() == sellername)
			return tco;
	}
	return NULL;
}

void UTkala::category_offer_check(Seller* seller, string _category, int _discount) {
	if (check_item_by_category_sellername(_category, seller->get_username())) {
		Offer_category* new_Offer_category = new Offer_category(seller->get_username(), _category, _discount);
		offer_categories.push_back(new_Offer_category);
		cout << OK;
	}
	else
		throw BAD_REQUEST;
}

void UTkala::package_offer_check(Seller* seller, string _ids, int _discount) {
	line _idss = Offer_package::split_string(_ids);
	vector<int> ids;
	for (auto _ids : _idss) {
		Item* item = find_item(stoi(IsInteger(_ids)));
		if (item != NULL)
			if (item->is_seller_username_same(seller->get_username())) {
				ids.push_back(stoi(IsInteger(_ids)));
			}
			else
				throw BAD_REQUEST;
		else
			throw NOT_FOUND;
	}
	Offer_package* new_Offer_package = new Offer_package(seller->get_username(), ids, _discount);
	offer_packages.push_back(new_Offer_package);
	cout << OK;
}


bool UTkala::check_item_by_category_sellername(string category, string sellername) {
	for (Item* item : items) {
		if (item->get_category() == category)
			if (item->get_seller_username() == sellername)
				return true;
	}
	throw NOT_FOUND;
}

void UTkala::login_buyer_run(Buyer* buyer) {
	line command;
	cout << OK;
	while (true) {
		command = read_command();
		try {
			if (command.size() == 0) { break; }
			else if (command[0] != "POST" && command[0] != "GET" && command[0] != DELETE && command[0] != PUT) { throw BAD_REQUEST; }
			else if (command[1] == INCREASE_CREDIT) { buyer->increase_credit(IsInteger(find_part(AMOUNT, command))); }
			else if (command[1] == BUY_ITEM) { buy_item( buyer, stoi(IsInteger(find_part("id", command))), stoi(IsInteger(find_part("count", command))), find_part_optional(CITY, command)); }
			else if (command[1] == WALLET_BALANCE) { buyer->print_amount(); }
			else if (command[1] == REFUND) { refund(buyer,find_part("purchased_id", command)); }
			else if (command[1] == LIST_PURCHASED) { list_purchased(buyer); }
			else if (command[1] == LIST_ITEMS) { list_items_type(buyer,command); }
			else if (command[1] == "comment") { add_comment(buyer, stoi(IsInteger(find_part("id", command))), find_part("message", command)); }
			else if (command[1] == "rate") { add_rate(buyer, stoi(IsInteger(find_part("id", command))), stoi(IsInteger(find_part_second("rate", command)))); }
			else if (command[1] == "rate_filter") { buyer->rate_filter_new(stoi(IsInteger(find_part("min_rating", command))), stoi(IsInteger(find_part("max_rating", command)))); }
			else if (command[1] == "price_filter") { buyer->price_filter_new(stoi(IsInteger(find_part("min_price", command))), stoi(IsInteger(find_part("max_price", command)))); }
			else if (command[1] == "category_filter") { buyer->category_filter_new(find_part("category", command)); }
			else if (command[1] == "filters") { buyer->delete_filters();    cout << OK;}
			else if (command[1] == "add_to_cart") { add_to_cart(buyer, stoi(IsInteger(find_part("id", command))), stoi(IsInteger(find_part("count", command)))); }
			else if (command[1] == "purchase_cart") {purchase_cart(buyer, find_part_optional("city", command)); }
			else if (command[1] == "cart") { buyer->DELETE_cart(); }
			else if (command[1] == "list_offers") { show_list_offers(find_part("username", command)); }
			else if (command[1] == LOGOUT) { buyer->delete_filters(); buyer->DELETE_cart();  cout << OK; break; }
			else { throw BAD_REQUEST; }
		}
		catch (string error) { cout << error << endl; }
	}
}

void UTkala::show_list_offers(string sellername) {
	bool finded = false;
	for (Offer_package* offer_package : offer_packages) {
		if (offer_package->get_seller_set_offer() == sellername) {
			offer_package->Offer_print_detail();
			finded = true;
		}
	}
	for (Offer_category* offer_category : offer_categories) {
		if (offer_category->get_seller_set_offer() == sellername) {
			offer_category->Offer_print_detail();
			finded = true;
		}
	}
	for (total_cost_offer* total_cost_offerr : total_cost_offers) {
		if (total_cost_offerr->get_seller_set_offer() == sellername) {
			total_cost_offerr->Offer_print_detail();
			finded = true;
		}
	}
	if( offer_packages.size() == 0 && offer_categories.size() ==0 && total_cost_offers.size() == 0)
		throw EMPTY;
	else if (!finded)
		throw NOT_FOUND;
}



void UTkala::add_to_cart(Buyer* buyer, int _id, int _count) {
	if (_id >= 0, _count > 0) {
		Item* item = find_item(_id);
		buyer->add_to_cart_buyer(item, _count);
		cout << OK;
	}
	else
		throw BAD_REQUEST;
}
int UTkala::cate_offer_caculater(Item* item) {
	for (auto cate_offer : offer_categories) {
		if (item->is_seller_username_same(cate_offer->get_seller_set_offer()))
			if (item->get_category() == cate_offer->get_category())
				return cate_offer->get_discount();
	}
	return 0;
}

int UTkala::tco_offer_caculater(Item* item, vector<pair<Item*, int>> cards) {
	int total_price_of_one_seller = 0;
	for (auto card : cards) {
		if (item->is_seller_username_same(card.first->get_seller_username()))
			total_price_of_one_seller += card.second * card.first->get_price();
	}
	for (auto tco_offer : total_cost_offers) {
		if (item->is_seller_username_same(tco_offer->get_seller_set_offer()))
			if (total_price_of_one_seller >= tco_offer->total_cost_offer_price())
				return tco_offer->total_cost_offer_discount();
	}
	return 0;
}

bool UTkala::isSubset(vector<int> arr1, vector<int> arr2, int m, int n){
	int i = 0;
	int j = 0;
	for (i = 0; i < n; i++) {
		for (j = 0; j < m; j++) {
			if (arr2[i] == arr1[j])
				break;
		}
		if (j == m)
			return false;
	}
	return true;
}



int UTkala::pak_offer_caculater(Item* item, vector<Item*> item_buy_list) {
	int discount = 0;
	vector<int> _ids;
	for (auto item : item_buy_list)
		_ids.push_back(item->get_id());

	for (auto pak_offer : offer_packages) {
		if (item->is_seller_username_same(pak_offer->get_offer_type()))
			if (isSubset(_ids, pak_offer->get_ids(), _ids.size(), pak_offer->get_ids().size()))
				discount += pak_offer->get_discount();
	}
	return discount;

}

int UTkala::get_item_discount(Item* item, vector<pair<Item*, int>> cards) {
	vector<Item*> item_buy_list;
	for (auto card : cards)
		item_buy_list.push_back(card.first);
	int cate_offer = cate_offer_caculater(item);
	int tco_offer = tco_offer_caculater(item, cards);
	int pak_offer = pak_offer_caculater(item, item_buy_list);
	int total_discount = cate_offer + tco_offer + pak_offer;
	if (total_discount <= 100)
		return total_discount;
	else
		return 0;
}


void UTkala::purchase_cart(Buyer* buyer, string city) {
	vector<pair<Item*, int>> cards = buyer->get_cards();
	
	int total_price = 0;
	int total_price_with_discount = 0;
	vector<Purchased*> purchasedss;
	if (cards.size() != 0) {
		for (auto card : cards) {
			int delivery_cost = caculate_delivery_cost(buyer, card.first, 0, city);
			total_price_with_discount += (card.first->get_price() * card.second * (100 - get_item_discount(card.first, cards))) / 100 + delivery_cost;
			total_price += card.first->get_price() * card.second + delivery_cost;
			card.first->decrease_quantity(card.second);
			auto  now = chrono::system_clock::now();
			time_t current_time = chrono::system_clock::to_time_t(now);
			Purchased* new_purchased = new Purchased(ctime(&current_time), card.first->get_id(),
				card.first->get_name(), card.first->get_price(), card.second, delivery_cost, total_price,
				card.first->get_seller()->get_username(), buyer->get_username());
			purchaseds.push_back(new_purchased);
			purchasedss.push_back(new_purchased);
		}
		if (buyer->can_buy(total_price)) {
			buyer->DELETE_cart();
			auto  now = chrono::system_clock::now();
			time_t current_time = chrono::system_clock::to_time_t(now);
			Purchased_card* new_Purchased_card = new Purchased_card(purchasedss, ctime(&current_time), buyer->get_username(), total_price, total_price_with_discount);
			purchased_cards.push_back(new_Purchased_card);
			buyer->decrease_credit(total_price_with_discount);
			cout << "total_cost : " << total_price << endl;
			cout << "total_discount : " << total_price - total_price_with_discount << endl;
			cout << "paid : " << total_price_with_discount << endl;
		}
		else
			throw BAD_REQUEST;
	}
	else
		throw BAD_REQUEST;
}






void UTkala::list_items_type(Buyer* buyer,line command) {
	if (find_part_optional("id", command) == STRING_NULL)
		list_items(buyer,find_part_optional("sort_by", command), find_part_optional("seller_username", command));
	else {
		Item* item = find_item(stoi(IsInteger(find_part("id", command))));
		item->print_info_solo();
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

string UTkala::find_part_second(string part, line command) {
	int count = 0;
	for (int i = 0; i < command.size(); i++) {
		if (command[i] == part && count == 1)
			return command[i + 1];
		if (command[i] == part)
			count++;
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
	for (Purchased_card* purchased_card : purchased_cards) {
		if (buyer->is_username_same(purchased_card->get_purchased_card_buyer_usename())) {
			purchased_card->print_info();
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
			Item* new_item = new Item(item_name, seller, item_category,ctime(&current_time), item_price, item_quantity, 0, item_refund);
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
	if (find_list_items(items,item_sorted, seller->get_username())) {
		if (item_sorted.size() != NULL) {
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
	int count = 0;
	for (Purchased_card* Purchased_card : purchased_cards) {
		Purchased_card->print_info_seller(seller->get_username());
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

void UTkala::add_comment(Buyer* buyer,int _id, string _message) {
	Item* item = find_item(_id);
	if (_message != STRING_NULL) {
		item->add_comment_item(buyer,_message);
		cout << OK;
	}
	else
		throw BAD_REQUEST;
}

void UTkala::add_rate(Buyer* buyer, int _id, int _rate) {
	Item* item = find_item(_id);
	if (item->check_rate_value(_rate))
		if (buyer_bought_item(buyer, item) && !item->buyer_rated_item(buyer)) {
			item->add_rate_item(buyer, _rate);
			cout << OK;
		}
		else
			throw PERMISSION_DENIED;
	else
		throw BAD_REQUEST;
}


bool UTkala::buyer_bought_item(Buyer* buyer,Item* item) {
	for (Purchased* purchased : purchaseds) {
		if (item->is_id_same(purchased->get_purchased_item_id()))
			if (buyer->is_username_same(purchased->get_purchased_buyer_usename()))
				return true;
	}
	return false;
}

