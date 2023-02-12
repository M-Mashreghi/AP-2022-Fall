#pragma once
#include "Filter.hpp"
#include "Item.hpp"
class Item;
class Category_filter : public Filter {
public:
	Category_filter(string _category);
	vector<Item*> filter_item(vector<Item*> items);
	string  get_category();
	void change_value(string _category);
private:
	string category;
};

