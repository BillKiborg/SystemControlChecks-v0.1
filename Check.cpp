
#include "Check.h"
#include "Product.h"
#include "SystemControl.h"

#include <iomanip>
#include <regex>


Check::Check()
	: shopname("Новый чек"), totalprice(0.0), pack(nullptr), size_productlist(0) {
}

string Check::get_shopname() const {	
		return shopname;	
}

string& Check::set_shopname() {
	return shopname;
}

Date Check::get_date() const {
	return date;
}

Date& Check::set_date() {
	return date;
}

float Check::get_totalprice() const {
	return totalprice;
}

float& Check::set_totalprice() {
	return totalprice;
}

vector <Product*>& Check::set_productlist() {
	return productlist;
}

vector <Product*> Check::get_productlist() const {
	return productlist;
}

int Check::get_size_productlist() const {
	return size_productlist;
}

Check::~Check() {
	for (auto i : productlist) delete i;
}


Date input_date(string input) {

	Date date;

	regex format_date("(\\d{2}).(\\d{2}).(\\d{4}|\\d{2})");

	cmatch result;	

		if (regex_search(input.c_str(), result, format_date)) {

			auto it = result.begin();	it++;

			string str;
			str = *it;	date.day = atoi(str.c_str());	it++;
			str = *it;	date.mounth = atoi(str.c_str()); it++;
			str = *it;	date.year = atoi(str.c_str());			

		}	
	
	return date;

}


void Check::edit() {

	while (true) {

		system("cls");

		cout << *this;

		cout << " 1 - Задать дату и место покупки\n 2 - Добавить товар"
			<< "\n 3 - Удалить товар\n 4 - Просмотреть товары\n < - Назад\n:";

		string set; cin.sync();	getline(cin, set);

		if (set == "1") set_date_shopname();
		else if (set == "2") add_product();
		else if (set == "3") del_product();
		else if (set == "4") view_product();
		else if (set == "<") return;
		
	}

}


void Check::set_date_shopname() {

	while (true) {

		system("cls");

		cout << "Дата и место покупки (для возврата нажмите <)\n Введите место покупки\n:";
		string buffname;	cin.sync();  getline(cin, buffname);

		if (buffname[0] == '<') return;
		else this->shopname = buffname;

		system("cls");

		cout << "Дата и место покупки (для возврата нажмите <)\n Введите дату покупки\n:";
		string buffdate; cin.sync(); getline(cin, buffdate);

		if (buffdate[0] == '<') continue;
		else { this->date = input_date(buffdate); break; }

	}
}

void Check::add_product() {

	Product* newproduct = new Product;

	while (true) {

		system("cls");

		cout << "Добавить товар\n 1 - Ввести наименование\t" << newproduct->get_name()
			<< "\n 2 - Ввести цену\t\t" << newproduct->get_price()
			<< "\n 3 - Ввести кол-во(г/л)\t\t" << newproduct->get_quantity()
			<< "\n s - Сохранить\n < - Выйти\n:";

		string set; cin.sync(); getline(cin, set);

		if (set == "1") newproduct->set_name();
		else if (set == "2") newproduct->set_price();
		else if (set == "3") newproduct->set_quantity();
		else if (set == "s") { productlist.push_back(newproduct); totalprice += (newproduct->get_price()); return; }
		else if (set == "<") { delete newproduct; return; }
		else continue;
	}
}

void Check::view_product() {

	while (true) {

		system("cls");

		cout << *this;

		if (!productlist.size()) cout << " Товаров не найдено\n";
		else {

			for (int i = 0; i < productlist.size(); i++) 
				cout << "\n " << i + 1 << " " << *productlist[i];			
		}

		for (int i = 0; i < 70; i++) cout << "-";

		cout << "\n < - Для возврата\n:";
		string set; cin.sync(); getline(cin, set);

		if (set == "<") return;

	}
}

bool are_you_sure() {

	while (true) {

		system("cls");	cout << "Вы уверены?\n Y - Да\n N - Нет\n";

		string set; cin.sync();	getline(cin, set);

		if (set == "Y") return 1;
		else if (set == "N") return 0;
	}
}


void Check::del_product() {

	while (true) {

		system("cls"); cout << "Удалить товар\n";

		for (int i = 0; i < productlist.size(); i++) 
			cout << " " << (i + 1) << *productlist[i];

		for (int i = 0; i < 70; i++) 
			cout << "-";	
		
		cout << "\n < - Для возврата\n:";		
		
		string set; cin.sync();	getline(cin, set);

		if (set == "<") return;
		else {

			int i = number_selection(set, productlist.size());

			if (i > -1)
				if (are_you_sure()) {

					totalprice -= productlist[i]->get_price();

					delete productlist[i];		auto itr = productlist.cbegin();

					productlist.erase(itr + (atoi(set.c_str()) - 1));
				}
				
			
		}
	}
}


void Check::package(ofstream& out) {

	pack = new dataCheck;
	strcpy_s(pack->shopname, 90, shopname.c_str());

	pack->date = date;	pack->totalprice = totalprice;
	pack->size_productlist = productlist.size();

	out.write(reinterpret_cast<char*>(pack), sizeof(dataCheck));
	delete pack;
}


void Check::unpackage(ifstream& in) {

	pack = new dataCheck;
	in.read(reinterpret_cast<char*>(pack), sizeof(dataCheck));

	str_translate(shopname, pack->shopname);
	date = pack->date;	totalprice = pack->totalprice;

	size_productlist = pack->size_productlist;
	delete pack;
}


ostream& operator << (ostream& out, Check& check) {

	out << check.get_shopname() << "   "
		<< check.get_date().day << "." << check.get_date().mounth
		<< "." << check.get_date().year << "   "
		<< check.get_totalprice() << ".руб" << "   " << check.set_productlist().size()
		<< " товар(ов)\n";

	return out;
}


Check* Check::operator = (const Check& check) {	

	shopname = check.shopname;
	date = check.date;
	totalprice = check.totalprice;	

	for (auto i : check.productlist) {

		Product* copy = new Product;	 *copy = *i;	productlist.push_back(copy);
	}

	return this;
}