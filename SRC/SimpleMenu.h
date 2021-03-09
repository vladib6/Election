#pragma once
#include "BaseMenu.h"
class Save;
class SimpleMenu :public BaseMenu {
public:
	SimpleMenu(Election& _E):BaseMenu(_E) {}
	void MainMenu(bool& flag) override;//the main menu of simple election
	virtual void AddDistrict();//create new district and resize the districts
	virtual void AddCitizen() noexcept(false);//create new citizen and adding him to voterbook
	virtual void AddElector();//add citizen to representatives list of party
	virtual void ShowResults();//show the results of election
	void printWinner();//print the results in simple election
	void printDDistrictDetails(DividedDistrict* district, PartyArray& partyarray,DynamicArray<size_t>& array, DynamicArray<size_t>& electorsDistributeArr);//print details of uniform district like: votingpercent ,the party that win in this state and etc

};





