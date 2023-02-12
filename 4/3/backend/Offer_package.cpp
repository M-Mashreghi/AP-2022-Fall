#include "Offer_package.hpp"
Offer_package::Offer_package(string _seller_set_offer, vector<int> _ids, int _discount)
	: Offer("package_offer", _seller_set_offer), discount(_discount), ids(_ids) {

};
vector<int> Offer_package::get_ids() { return ids; }
int Offer_package::get_discount() { return discount; }

void Offer_package::Offer_print_detail() {
	cout << get_id() << " " << get_offer_type() << " ";
	print_vec(ids);
	cout << discount <<endl;
}

void Offer_package::print_vec(vector<int> a) {
	for (int i = 0; i < a.size(); i++)
		cout << a.at(i) << ' ';
}