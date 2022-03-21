#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "Product.h"

using namespace std;

bool are_you_sure();

struct Date {
	int day = 0;
	int mounth = 0;
	int year = 0;
};

struct dataCheck {
	char shopname[90];
	Date date;
	float totalprice;

	int size_productlist;
};

class Check {
	string shopname;
	Date date;
	float totalprice;

	vector <Product*> productlist;
	int size_productlist;

	dataCheck* pack;

public:
	Check();

	string get_shopname() const;
	string& set_shopname();

	Date get_date() const;
	Date& set_date();

	float get_totalprice() const;
	float& set_totalprice();

	vector <Product*>& set_productlist();
	vector <Product*> get_productlist() const;

	int get_size_productlist() const;

	~Check();

	void set_date_shopname();
	void add_product();
	void del_product();
	void view_product();

	void edit();

	void package(ofstream& out);
	void unpackage(ifstream& in);

	Check* operator = (const Check& check);

	friend ostream& operator << (ostream& out, Check& check);
};