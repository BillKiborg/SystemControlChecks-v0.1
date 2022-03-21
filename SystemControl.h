#pragma once

#include <vector>
#include <Windows.h>
#include <string>

#include "Check.h"

struct dataSystemControl {
	int size_checklist;
};

class SystemControl {
	int size_checklist;
	vector <Check*> checklist;

	dataSystemControl* pack;

public:
	int get_size_checklist() {
		return size_checklist;
	}

	vector <Check*>& get_checklist() {
		return checklist;
	}

	void add_newcheck();
	void view_checks();

	void edit_check();
	void save_checks();
	void delete_check();

	void package(ofstream& out);
	void unpackage(ifstream& in);			
};

int number_selection(string set, int size);