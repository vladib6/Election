#pragma once
#include "BaseMenu.h"


class StandardMenu :public BaseMenu {
public:
	StandardMenu(Election& _E) :BaseMenu(_E) {}

	void printDDistrictDetails(DividedDistrict* district, PartyArray& partyarray, DynamicArray<size_t>& array, DynamicArray<size_t>& electorsDistributeArr);//print details of divided district like:voting percent and all the party that get at least 1 elector
	void printUDistrictDetails(District* district, PartyArray& partyarray, DynamicArray<size_t>& array);//print details of uniform district like: votingpercent ,the party that win in this state and etc
	void printWinnerInDistricts();//print the results in each district,the candidate that won etc.
	void ShowResults();//show the results of election
	void AddDistrict();//create new district and resize the districts

};