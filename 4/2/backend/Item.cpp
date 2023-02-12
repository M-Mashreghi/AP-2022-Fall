#include "Item.hpp"
#include <iostream>

int Item::current_registerd_item = 1;

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
	cout << "purchased_count : " << purchased_count << endl;
	cout << "average_rate: " << ratesAvg << endl << endl;
}

void Item::print_info_solo() {
	cout << "id : " << id << endl;
	cout << "name : " << name << endl;
	cout << "seller : " << get_seller()->get_username() << endl;
	cout << "category : " << category << endl;
	cout << "date : " << date;
	cout << "price : " << price << endl;
	cout << "quantity : " << quantity << endl;
	cout << "purchased_count : " << purchased_count << endl;
	cout << "average_rate: " << ratesAvg << endl;
	if (comments.size() != 0) {
		cout << "comments :" << endl;
		for (auto comment : comments)
			cout << "\"" << comment.second << "\""<< " by " << comment.first->get_username() << endl;
		cout << endl;
	}
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

void Item::add_comment_item(Buyer* buyer, string _message) {
	comments.push_back(make_pair(buyer, _message));
}

bool Item::check_rate_value(int _rate) {
	if (_rate <= 10 && _rate >= 0)
		return true;
	else
		return false;
}

void Item::add_rate_item(Buyer* buyer, int _rate) {
	rates_.push_back(make_pair(buyer, _rate));
	caculate_avg_rate();
}

void Item::caculate_avg_rate() {
	float ratesAvg_ = 0.0f;
	for (auto rate : rates_) {
		ratesAvg_ += rate.second;
	}
	ratesAvg = ratesAvg_ / (rates_.size());
}


float Item::get_avg_rate() {
	return ratesAvg;
}





bool Item::buyer_rated_item(Buyer* buyer) {
	for (auto rate : rates_) {
		if (buyer->is_username_same(rate.first->get_username()))
			return true;
	}
	return false;
}