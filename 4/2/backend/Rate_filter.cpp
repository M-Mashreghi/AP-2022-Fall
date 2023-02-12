#include "Rate_filter.hpp"
Rate_filter::Rate_filter(int _min_rating, int _max_rating) {
	if (_max_rating < _min_rating)
		throw BAD_REQUEST;
		min_rating = _min_rating;
		max_rating = _max_rating;
}
void Rate_filter::change_value(int _min_rating, int _max_rating) {
	if (_max_rating < _min_rating)
		throw BAD_REQUEST;
	min_rating = _min_rating;
	max_rating = _max_rating;
}

vector<Item*> Rate_filter::filter_item(vector<Item*> items) {
	vector<Item*> filtered_item;
	for (auto item : items) {
		if (item->get_avg_rate() == NULL) {
			if (0 >= min_rating && 0 <= max_rating) {
				filtered_item.push_back(item);
			}
		}
		else {
			if ((item->get_avg_rate()) >= min_rating && (item->get_avg_rate()) <= max_rating) {
				filtered_item.push_back(item);
			}
		}
	}
	return filtered_item;
}

int Rate_filter::get_max_rating() { return max_rating; }
int Rate_filter::get_min_rating() { return min_rating; }