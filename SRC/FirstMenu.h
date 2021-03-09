#pragma once
#include "SimpleMenu.h"
#include "StandardMenu.h"
class FirstMenu {
private:


public:
	FirstMenu() { firstMenu(); }
	void CreateNewElection(bool& flag);
	void firstMenu();
	void LoadElection(bool& flag);
	bool isValidDate(size_t day, size_t month, size_t year);//check if the date is valid

};




