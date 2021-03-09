#include "FirstMenu.h"
#include "Exceptions.h"

void FirstMenu::firstMenu() {
	enum FIRSTSELECT {
		NEWELEC = 1, LOADELEC, EXIT
	};

	std::cout << "  Choose an option" << std::endl;
	std::cout << "--- --- --- --- ---" << std::endl;
	std::cout << "1. Create New Election" << std::endl;
	std::cout << "2. Load Election from file" << std::endl;
	std::cout << "3. Exit" << std::endl;
	bool flag = false;//after we return from the functions "CreateNewElection" & "LoadElection" if the flag false we exit the program if true we load new eletion
	bool firstrun = true;
	int userchoice = 0;
	while (userchoice != 3) {
		if (firstrun) {
			std::cin >> userchoice;
			std::cin.ignore();
			firstrun = false;
		}
		if (flag)
			userchoice = 2;

		switch (static_cast<FIRSTSELECT>(userchoice)) {
		case FIRSTSELECT::NEWELEC:
			try
			{
			CreateNewElection(flag);
			}
			catch (const Generalexcep& e)
			{
				std::cout << "Error: " << e.what() << std::endl;
				userchoice = 1;
				break;
			}
			if (!flag)
				userchoice = 3;
			break;

		case FIRSTSELECT::LOADELEC:
			try
			{
			LoadElection(flag);
			}
			catch (const std::ios_base::failure& e)
			{
				std::cout << "Error: " << e.what() << std::endl;
				userchoice = 2;
				break;
			}
			if (!flag)
				userchoice = 3;
			break;

		case FIRSTSELECT::EXIT:
			break;

		default:
			std::cout << "wrong choice ,select number between 1-3" << std::endl;
			break;
		}
	}
	std::cout << "Bye Bye..." << std::endl;

}

void FirstMenu::LoadElection(bool& flag) {
	std::cout << "Please enter a name of a file: " << std::endl;
	STRING fileName;
	fileName.getStrInput();

	std::ifstream infile(fileName.getString(), std::ios::binary);
	if (!infile) {
		throw std::ios_base::failure("Error with file");
	}
	BaseMenu::ELECTYPE type;
	infile.read(rcastc(&type), sizeof(BaseMenu::ELECTYPE));
	Election election(infile);
	infile.close();
	BaseMenu* menu{};
	try
	{
		switch (static_cast<int>(type)) {
		case 1:
			menu = new StandardMenu(election);
			break;
		case 2:
			menu = new SimpleMenu(election);
			break;
		}
		menu->MainMenu(flag);
	}
	catch (const std::bad_alloc& e) {
		delete menu;
		exit(-1);
	}
	catch (const Generalexcep& e) {
		std::cout << "Error: " << e.what() << std::endl;
	}
	
	delete menu;
}

void FirstMenu::CreateNewElection(bool& flag) {
	int day, month, year;
	std::cout << "Enter Election Date in format: day(space)year(space)month" << std::endl;
	std::cin >> day >> month >> year;
	std::cin.ignore();
	if (!isValidDate(day, month, year)) 
		throw Generalexcep("The date are invalid");

	Date elecDate(month, day, year);
	Election E(elecDate);
	std::cout << "Choose Election Method: " << "(1) - Regular Elections" << "(2) - Simple Elections" << std::endl;
	size_t elecType;
	std::cin >> elecType;
	std::cin.ignore();
	if (elecType != 1 && elecType != 2)
		throw Generalexcep("invalid choice of election method");

	BaseMenu* menu{};
		try
		{
			switch (elecType) {
			case 1:
				menu = new StandardMenu(E);
				break;
			case 2:
				menu = new SimpleMenu(E);
				break;
			}
			menu->MainMenu(flag);
		}
		catch (const std::bad_alloc& e) {
			delete menu;
			exit(-1);
		}
		
		delete menu;
	
}

bool FirstMenu::isValidDate(size_t day, size_t month, size_t year)
{
	if (year <= 0)//check year
		return false;
	else if (month < 1 || month>13)//check month
		return false;
	else {
		if (day < 1 || day>31)//check day
			return false;
		if (month == 2 && day > 28)//check februar
			return false;
	}

	return true;
}