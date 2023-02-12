#pragma once
#include "Consts.hpp"
#include "Item.hpp"
#include <iostream>
class Item;

class Filter {
public:
    Filter() { id = 0; };
    void print_nothing() { cout << "sad"; };
    virtual vector<Item*> filter_item(vector<Item*> items) = 0;
private:
    int id;
};