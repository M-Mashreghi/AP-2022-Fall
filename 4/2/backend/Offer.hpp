#pragma once

#include <iostream>
#include "Consts.hpp"


class Offer {
public:
	Offer(string _offer_type, string _seller_set_offer):offer_type(_offer_type) , seller_set_offer(_seller_set_offer) {
		id = offer_id;
		Increase_Id();
	}
	string get_offer_type() { return offer_type; }
	string get_seller_set_offer(){ return seller_set_offer; };
	int get_id() { return id; };
	static void Increase_Id() { offer_id++; };
	static int offer_id;
	virtual void Offer_print_detail() const { cout << "wrong message"; };
private:
	int id;
	string offer_type;
	string seller_set_offer;
};