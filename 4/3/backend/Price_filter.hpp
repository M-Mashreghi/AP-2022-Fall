#pragma once

#include "Item.hpp"

class Item;
#include "Filter.hpp"
class Filter;
class Price_filter {
public:
	Price_filter(int min_price, int max_price);
	vector<Item*> filter_item(vector<Item*> items);
	int get_max_price();
	int get_min_price();
	void change_value(int _min_price, int _max_price);
private:

	int max_price;
	int min_price;
};