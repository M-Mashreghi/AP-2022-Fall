#include "Buyer.hpp"
#include <iostream>
#include "Read_input.hpp"
#include <utility>
using namespace std;
void Buyer::add_to_cart_buyer(Item* item, int _count) {
    int total = 0;
    for (auto card : cards) {
        if(item == card.first)
            total += card.second;
    }
    if (item->get_quantity() >= (total + _count)) {
        cards.push_back(make_pair(item, _count));
    }
    else
        throw BAD_REQUEST;
}

Buyer::Buyer(string _username, string _password, string _city): User( _username,  _password, _city) , amount(0) {}

void Buyer::decrease_credit(double  cost) {
       amount = amount - cost;

}

void Buyer::increase_credit(string  _amount) {
    double temp = stod(_amount);
    if (temp > 0) {
        amount += temp;
        cout << OK;
    }
    else
        throw BAD_REQUEST;
}

void Buyer::increase_credit(double  _amount) {
        if (_amount > 0) {
            amount += _amount;
        }
        else
            throw BAD_REQUEST;
}

double Buyer::get_amount()const { return amount; }

double Buyer::can_buy(double total_cost)const { return (total_cost < amount); }

void Buyer::print_amount()const { cout << "wallet balance : " << amount << endl; }

void Buyer::rate_filter_new(int _min_rating, int _max_rating) {
    if (rate_filter == nullptr) {
        Rate_filter* rate_filter_new = new Rate_filter(_min_rating, _max_rating);
        rate_filter = rate_filter_new;
    }
    else {
        rate_filter->change_value(_min_rating, _max_rating);
    }
    cout << OK;
}

void Buyer::price_filter_new(int _min_price, int _max_price) {
    if (price_filter == NULL) {
        Price_filter* price_filter_new = new Price_filter(_min_price, _max_price);
        price_filter = price_filter_new;
    }
    else {
        price_filter->change_value(_min_price, _max_price);
    }
    cout << OK;
}

void Buyer::category_filter_new(string _category) {
    if (category_filter == NULL) {
        Category_filter* category_filter_new = new Category_filter(_category);
        category_filter = category_filter_new;
    }
    else {
        category_filter->change_value(_category);
    }
    cout << OK;
}

void Buyer::delete_filters() {
    if (rate_filter != NULL) 
        rate_filter = NULL;
    if (price_filter != NULL)
        price_filter = NULL;
    if (category_filter != NULL)
        category_filter = NULL;
}

vector<Item*> Buyer::filter_list_items(vector<Item*> item) {
    vector<Item*> item_filtered = item;
    //cout << (rate_filter != NULL );
    if (rate_filter != NULL)
        item_filtered = rate_filter->filter_item(item_filtered);
    if (price_filter != NULL)
        item_filtered = price_filter->filter_item(item_filtered);
    if (category_filter != NULL)
        item_filtered = category_filter->filter_item(item_filtered);
    return item_filtered;
}