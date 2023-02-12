#include "Category_filter.hpp"


Category_filter::Category_filter(string _category) {
	if (_category != "") {
		bool findeed = false;
		for (auto cate : known_categories) {
			if (cate == _category) {
				findeed = true;
				category = _category;
			}
		}
		if (!findeed)
			throw NOT_FOUND;
	}
	else
		throw BAD_REQUEST;
}
void Category_filter::change_value(string _category) {
	if (_category != "") {
		bool findeed = false;
		for (auto cate : known_categories) {
			if (cate == _category) {
				findeed = true;
				category = _category;
			}
		}
		if (!findeed)
			throw NOT_FOUND;
	}
	else
		throw BAD_REQUEST;
	cout<<"s";
}

vector<Item*> Category_filter::filter_item(vector<Item*> items) {
	vector<Item*> filtered_item;
	for (auto item : items) {
		if (item->get_category() == category) {
			filtered_item.push_back(item);
		}
	}
	return filtered_item;
}

string  Category_filter::get_category() { return category; }

