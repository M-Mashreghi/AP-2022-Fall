#include "Offer_category.hpp"
Offer_category::Offer_category(string _seller_set_offer, string _category, int _discount)
	: Offer("category", _seller_set_offer), category(_category), discount(_discount) {};
string Offer_category::get_category() { return category; }
int Offer_category::get_discount() { return discount; }

void Offer_category::Offer_print_detail() {
	cout << get_id() << " " << get_offer_type() << " ";
	cout << category << " ";
	cout << discount << endl;
}
