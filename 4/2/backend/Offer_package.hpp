#pragma once

#include "Offer.hpp"
#include "Read_input.hpp"


class Offer_package : public Offer {
public:
	Offer_package(string _seller_set_offer, vector<int> _ids, int _discount);
	vector<int> get_ids();
	int get_discount();
	void Offer_print_detail();
	void print_vec(vector<int> a);

	static line split_string(string str) {
		line data_line;
		string data;
		while (str.size() > 0) {
			data = str.substr(0, str.find(","));
			str.erase(0, data.length() + 1);
			data_line.push_back(data);
		}
		return data_line;
	}
private:
	vector<int> ids;
	int discount;
};