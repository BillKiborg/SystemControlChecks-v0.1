
#include "SystemControl.h"
#include "Check.h"

using namespace std;

string want_to_save(Check* check) {

	while (true) {

		system("cls");	cout << *check << endl << "Сохранить чек?\n y - да\n n - нет\n < - назад\n:";

		string set;	cin.sync();	getline(cin, set);

		return set;
	}
}

int number_selection(string set, int size) {

	for (int i = 0; i < size; i++) if (atoi(set.c_str()) == (i + 1)) return i;
	return -1;
}


void SystemControl::add_newcheck() {

	Check* newcheck = new Check;

	while (true) {
		newcheck->edit();

		while (true) {

			system("cls");	cout << *newcheck << endl << "Сохранить чек?\n y - да\n n - нет\n < - назад\n:";

			string set;	cin.sync();	getline(cin, set);

			if (set == "y") { checklist.push_back(newcheck); return; }
			else if (set == "n") { delete newcheck; return; }
			else if (set == "<") break;
		}
	}
	
}

void SystemControl::package(ofstream& out) {

	pack = new dataSystemControl;	pack->size_checklist = checklist.size();

	out.write(reinterpret_cast<char*>(pack), sizeof(dataSystemControl));

	delete pack;
}

void SystemControl::unpackage(ifstream& in) {

	pack = new dataSystemControl;

	in.read(reinterpret_cast<char*>(pack), sizeof(dataSystemControl));

	size_checklist = pack->size_checklist;	delete pack;
}


void SystemControl::edit_check() {

	while (true) {

		system("cls"); cout << "Редактировать чек\n";

		for (int i = 0; i < checklist.size(); i++) cout << " " << (i + 1) << " " << *checklist[i];

		cout << " < - Для возврата\n:";		string set; cin.sync(); getline(cin, set);

		if (set == "<") return;
		else {

			int i = number_selection(set, checklist.size());

			if (i > -1) {
				
				Check* newcheck = new Check;
				
				*newcheck = *checklist[i];

				while (true) {

					newcheck->edit();	string set2 = want_to_save(newcheck);

					if (set2 == "y") { delete checklist[i]; checklist[i] = newcheck; return; }
					else if (set2 == "n") { delete newcheck; return; }
					else if (set2 == "<") break;
					
				}
			}
		}

			
	}
	
}


void SystemControl::save_checks() {

	system("cls");

	ofstream save; save.open("DataBase", ios::out | ios::binary);

	if (!save.is_open()) {
		for (int i = 0; i < 3; i++) {
			cout << "Не удалось записать файл\n"; Sleep(450); system("cls"); if (i != 2) Sleep(450);
		}
	}
	else {

		this->package(save);
		for (int i = 0; i < checklist.size(); i++) {

			checklist[i]->package(save);

			for (int j = 0; j < checklist[i]->set_productlist().size(); j++) {

				checklist[i]->set_productlist()[j]->package(save);
			}
		}

		if (!save.rdstate())
			for (int i = 0; i < 3; i++) {
				cout << "Чеки сохранены...\n"; Sleep(450); system("cls"); if (i != 2) Sleep(450);
			}
		else
			for (int i = 0; i < 3; i++) {
				cout << "Ошибка записи...\n"; Sleep(450); system("cls"); if (i != 2) Sleep(450);
			}

		save.close();
	}
}


void SystemControl::view_checks() {

	while (true) {
		system("cls");

		cout << "Просмотреть чеки\n";

		if (!checklist.size()) cout << " Чеков не найдено\n";
		else {
			for (int i = 0; i < checklist.size(); i++) cout << " " << (i + 1) << " - " << *checklist[i];
		}

		cout << " < - для возврата\n:"; string set; cin.sync(); getline(cin, set);

		if (set == "<") return;
		else {

			int i = number_selection(set, checklist.size());

			if (i > -1) checklist[i]->view_product();
		}
	}
}


void SystemControl::delete_check() {

	while (true) {

		system("cls");		cout << "Удалить чек(выберете номер)\n ";

		for (int i = 0; i < checklist.size(); i++) cout << " " << (i + 1) << " - " << *checklist[i];

		cout << " < - для возврата\n:"; string set; cin.sync(); getline(cin, set);

		if (set == "<") return;
		else {

			int i = number_selection(set, checklist.size());			

			if (i > -1) 
				if (are_you_sure()) {

					delete checklist[i];

					auto iterator = checklist.cbegin();

					checklist.erase(iterator + (atoi(set.c_str()) - 1));
					return;
				}
				else break;
				
			
		}
	}
}