#pragma once
#include "Purchased.hpp"


using namespace std;
class Purchased_card
{
public:
	Purchased_card(vector<Purchased*> _purchased_cards, string _date, string _buyer_name,int _total_cost, int _paid):
	date(_date) , buyer_name(_buyer_name), total_cost(_total_cost), paid(_paid), purchaseds(_purchased_cards) {
		id = current_registerd_purchased_card;
		Increase_Id();
	}
	string get_purchased_card_buyer_usename() { return buyer_name; }
	static void Increase_Id() { current_registerd_purchased_card++; };
	static int current_registerd_purchased_card;
	void print_info() {
		cout << "id : " << id << endl;
		cout << "date : " << date;
		cout << "items :" << endl;
		int count = 1;
		for (auto purchased : purchaseds) {
			cout << count << ")" << endl;
			cout << "seller : " << purchased ->get_purchased_seller_usename() << endl;
			cout << "item_id : " << purchased->get_purchased_item_id() << endl;
			cout << "item_name : " << purchased->get_purchased_item_name() << endl;
			cout << "item_price : " << purchased->get_purchased_item_price() << endl;
			cout << "purchased_count : " << purchased->get_purchased_count() << endl;
			cout << "delivery_cost : " << purchased->get_purchased_delivery_cost() << endl;
			cout << "total_cost : " << purchased->get_purchased_total_cost() << endl;
			count++;
		}
		cout << "total_cost : " << total_cost << endl;
		cout << "paid : " << paid << endl;
	};

	void print_info_seller(string seller_name) {
		bool find_seller=false;
		for (auto purchased : purchaseds) {
			if (purchased->get_purchased_seller_usename() == seller_name) {
				find_seller = true;
				break;
			}
		}
		if (find_seller) {
			cout << "id : " << id << endl;
			cout << "date : " << date;
			cout << "buyer :" << buyer_name << endl;
			cout << "items :" << endl;
			int count = 1;
			for (auto purchased : purchaseds) {
					if (purchased->get_purchased_seller_usename() == seller_name) {
						cout << count << ")" << endl;
						cout << "seller : " << purchased->get_purchased_seller_usename() << endl;
						cout << "item_id : " << purchased->get_purchased_item_id() << endl;
						cout << "item_name : " << purchased->get_purchased_item_name() << endl;
						cout << "item_price : " << purchased->get_purchased_item_price() << endl;
						cout << "purchased_count : " << purchased->get_purchased_count() << endl;
						cout << "delivery_cost : " << purchased->get_purchased_delivery_cost() << endl;
						cout << "total_cost : " << purchased->get_purchased_total_cost() << endl;
						count++;
					}
			}
			cout << "total_cost : " << total_cost << endl;
			cout << "paid : " << paid << endl;
		}
	};
	vector<Purchased*> get_purchased_card_purchaseds() { return purchaseds; }
private:
	int id;
	int total_cost;
	int paid;
	string buyer_name;
	string date;
	vector<Purchased*> purchaseds;
};

