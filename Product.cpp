
#include <iomanip>

#include "Product.h"

void str_translate(string& str, char* c_str) {
	string tmp(c_str);	str = tmp;
}

void Product::set_name() {

	system("cls");
	cout << "¬ведите наименование (дл€ возврата нажмите <)\n:";
	string buffname; cin.sync(); getline(cin, buffname);

	if (buffname == "<") return;
	else name = buffname;
}

void Product::set_quantity() {

	system("cls");
	cout << "¬ведите кол-во товара в граммах/литрах (дл€ возврата нажмите <)\n:";
	string buffquantity; cin.sync(); getline(cin, buffquantity);

	if (buffquantity == "<") return;
	else {
		char tmp[10]; int i;
		for (i = 0; buffquantity[i]; i++) tmp[i] = buffquantity[i];
		tmp[i] = '\0';

		quantity = atof(tmp);

	}
}

void Product::set_price() {

	system("cls");
	cout << "¬ведите цену за единицу товара (дл€ возврата нажмите <)\n:";
	string buffprice; cin.sync(); getline(cin, buffprice);

	if (buffprice == "<") return;
	else {
		char tmp[90]; int i;
		for (i = 0; buffprice[i]; i++) tmp[i] = buffprice[i];
		tmp[i] = '\0';

		price = static_cast<float>(atof(tmp));

	}
}

void Product::package(ofstream& out) {

	pack = new dataProduct;

	strcpy_s(pack->name, 90, name.c_str());
	pack->price = price;	pack->quantity = quantity;

	out.write(reinterpret_cast<char*>(pack), sizeof(dataProduct));
	delete pack;
}

void Product::unpackage(ifstream& in) {

	pack = new dataProduct;
	in.read(reinterpret_cast<char*>(pack), sizeof(dataProduct));

	str_translate(name, pack->name);
	price = pack->price;	quantity = pack->quantity;

	delete pack;
}


ostream& operator << (ostream& out, Product& product) {

	out << left << setw(7) << product.get_name()
		<< "\tкол-во в (г/л) - " << product.get_quantity()
		<< "\t\tцена в руб. - " << product.get_price() << endl;

	return out;
}


Product* Product::operator = (const Product& product) {	

	name = product.name;
	quantity = product.quantity;
	price = product.price;

	return this;
}