#include <iostream>
#include <Windows.h>
#include <vector>
#include <string>
#include <fstream>
#include <regex>

#include "SystemControl.h"
#include "Check.h"
#include "Product.h"

using namespace std;


SystemControl* read_base() {

	ifstream base; base.open("DataBase", ios::in | ios::binary);

	if (!base.is_open()) {
		for (int i = 0; i < 3; i++) {
			cout << "Не удалось открыть файл\n"; Sleep(450); system("cls"); if (i != 2) Sleep(450);
		}
		return new SystemControl;
	}
	else {

		SystemControl* buffBase = new SystemControl;	buffBase->unpackage(base);

		Check* buffCheck;	Product* buffProduct;

		for (int i = 0; i < buffBase->get_size_checklist(); i++) {

			buffCheck = new Check;
			buffCheck->unpackage(base);	buffBase->get_checklist().push_back(buffCheck);

			for (int j = 0; j < buffCheck->get_size_productlist(); j++) {

				buffProduct = new Product;
				buffProduct->unpackage(base);
				buffBase->get_checklist()[i]->set_productlist().push_back(buffProduct);
			}
		}

		if (!base.rdstate()) { base.close(); return buffBase; }
		else {
			for (int i = 0; i < 3; i++) {
				cout << "Ошибка чтения...\n"; Sleep(450); system("cls"); if (i != 2) Sleep(450);

			}
			base.close();
			return new SystemControl;
		}

	}
}


void menu() {

	SystemControl* DataBase = read_base();

	while (true) {

		cout << "Меню:\n 1 - Добавить новый чек\n 2 - Просмотреть все чеки\n"
			<< " e - Редактировать чек\n"
			<< " s - Сохранить чеки\n d - Удалить чек\n 0 - Выйти\n:";
		string set;	cin.sync();	getline(cin, set);

		if (set == "1") { DataBase->add_newcheck(); system("cls"); }
		else if (set == "2") { DataBase->view_checks(); system("cls"); }
		else if (set == "e") { DataBase->edit_check(); system("cls"); }
		else if (set == "s") { DataBase->save_checks(); system("cls"); }
		else if (set == "d") { DataBase->delete_check(); system("cls"); }
		else if (set == "0") return;
		else { system("cls"); continue; }
	}
}


int main() {

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	menu();

	return 0;
}