#include "total_cost_offer.hpp"
total_cost_offer::total_cost_offer(string _seller_set_offer, int _price, int _discount)
	: Offer("total_cost_offer", _seller_set_offer), price(_price), discount(_discount) {};
int total_cost_offer::total_cost_offer_price() { return price; };
int total_cost_offer::total_cost_offer_discount() { return discount; };

void total_cost_offer::Offer_print_detail() {
	cout << get_id() << " " << get_offer_type() << " ";
	cout << price << " ";
	cout << discount << endl;
}