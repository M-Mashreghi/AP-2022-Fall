
#include "Buyer.hpp"
#include "Consts.hpp"
#include <iostream>
#include "Read_input.hpp"
using namespace std;
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


