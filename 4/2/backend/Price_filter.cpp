#include "Price_filter.hpp"

Price_filter::Price_filter(int _min_price, int _max_price) {
	if (_max_price < _min_price)
		throw BAD_REQUEST;
	min_price = _min_price;
	max_price = _max_price;
}
void Price_filter::change_value(int _min_price, int _max_price) {
	if (_max_price < _min_price)
		throw BAD_REQUEST;
	min_price = _min_price;
	max_price = _max_price;
}

vector<Item*> Price_filter::filter_item(vector<Item*> items) {
	vector<Item*> filtered_item;
	for (auto item : items) {
			if ( item->get_price() >= min_price && item->get_price() <= max_price) {
				filtered_item.push_back(item);
			}
	}
	return filtered_item;
}

int Price_filter::get_max_price() { return max_price; }
int Price_filter::get_min_price() { return max_price; }
