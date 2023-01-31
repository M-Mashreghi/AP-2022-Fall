
#include "Purchased.hpp"
Purchased::Purchased(string _date, int _item_id, string _item_name, double _item_price, int _purchased_count,
	double _delivery_cost, double _total_cost, string _seller_usename, string _buyer_usename)
	:date(_date), item_id(_item_id), item_name(_item_name), item_price(_item_price), purchased_count(_purchased_count) ,
	delivery_cost(_delivery_cost) , total_cost(_total_cost) , seller_usename(_seller_usename) , buyer_usename(_buyer_usename) {
	id = current_registerd_purchased;
	Increase_Id();
}

int Purchased::current_registerd_purchased = 0;

void Purchased::print_info() {
	cout << "id : " << id << endl;
	cout << "date : " << date;
	cout << "seller : " << seller_usename << endl;
	cout << "item_id : " << item_id << endl;
	cout << "item_name : " << item_name << endl;
	cout << "item_price : " << item_price << endl;
	cout << "purchased_count : " << purchased_count << endl;
	cout << "delivery_cost : " << delivery_cost << endl;
	cout << "total_cost : " << total_cost << endl<< endl;
}
