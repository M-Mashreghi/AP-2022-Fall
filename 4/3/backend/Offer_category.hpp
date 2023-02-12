#pragma once
#include "Offer.hpp"

class Offer_category : public Offer {
public:
	Offer_category(string _seller_set_offer, string _category, int _discount);
	string get_category();
	int get_discount();
	void Offer_print_detail();
private:
	string category;
	int discount;
};