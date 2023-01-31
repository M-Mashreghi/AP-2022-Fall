

#include "Item.hpp"
#include <iostream>


int Item::current_registerd_item = 0;

bool Item::is_seller_username_same(string _seller_unsername) {
	if (seller_username->get_username() == _seller_unsername)
		return true;
	return false;
}

void Item::change_price(double _price) {
	price = _price;
}

bool Item::is_name_same(string _name) {
	if (_name == name)
		return true;
	return false;
}

bool  Item::is_id_same(int _id) {
	if (id == _id)
		return true;
	return false;
}

bool Item::operator <(const Item* s2) const {
	return this->get_price() < s2->get_price();
}

void Item::decrease_quantity(int count) {
	quantity = quantity - count;
	purchased_count += count;
}

void Item::change_quantity(int count) {
	quantity = count;
}

void Item::increase_quantity(int count) {
	quantity += count;
}

void Item::decrease_purchased_quantity(int count) {
	purchased_count = purchased_count - count;
}

void Item::print_info() {
	cout << "id : " << id << endl;
	cout << "name : " << name << endl;
	cout << "seller : " << get_seller()->get_username() << endl;
	cout << "category : " << category << endl;
	cout << "date : " << date;
	cout << "price : " << price << endl;
	cout << "quantity : " << quantity << endl;
	cout << "purchased_count : " << purchased_count << endl << endl;
}

void Item::print_info_seller() {
	cout << "id : " << id << endl;
	cout << "name : " << name << endl;
	cout << "category : " << category << endl;
	cout << "date : " << date;
	cout << "price : " << price << endl;
	cout << "quantity : " << quantity << endl; 
	cout << "purchased_count : " << purchased_count << endl;
	cout << "refund_percentage : " << refund_percentage << endl << endl;
}


