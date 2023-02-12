#pragma once

#include "Item.hpp"
class Item;
#include "Filter.hpp"
class Rate_filter{
public:
	Rate_filter(int min_rating, int max_rating);
	~Rate_filter(){};
	vector<Item*> filter_item(vector<Item*> items);
	int get_max_rating();
	int get_min_rating();
	void change_value(int _min_rating, int _max_rating);
private:
	int max_rating;
	int min_rating;
};
