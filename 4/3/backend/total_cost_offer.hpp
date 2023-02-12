#pragma once
#include "Offer.hpp"
class total_cost_offer : public Offer {
public:
	total_cost_offer(string _seller_set_offer, int _price, int _discount);
	int total_cost_offer_price();
	int total_cost_offer_discount();
	void Offer_print_detail();
private:
	int price;
	int discount;
};
