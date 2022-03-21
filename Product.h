#pragma once

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct dataProduct {
	char name[90];
	float quantity;
	float price;
};

class Product {
	string name;
	float quantity;
	float price;

	dataProduct* pack;

public:
	Product()
		: name("неизвестно"), quantity(0.0), price(0.0), pack(nullptr) {
	}

	string get_name() {
		return name;
	}	

	float get_price() {
		return price;
	}	

	float get_quantity() {
		return quantity;
	}

	void set_name();
	void set_price();
	void set_quantity();		

	void package(ofstream& out);
	void unpackage(ifstream& in);

	Product* operator = (const Product& product);

	friend ostream& operator << (ostream& out, Product& product);
};

void str_translate(string& str, char* c_str);