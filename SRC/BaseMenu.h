#pragma once
#include <iostream>
#include  "Election.h"
#include "DividedDistrict.h"
#include "Save.h"
#include <fstream>
#include "Exceptions.h"
class BaseMenu
{
public:

	enum class ELECTYPE {
		REGULAR = 1, SIMPLE
	};
	BaseMenu(Election& _E) :E(&_E) {}

	virtual void printMenu();//print the election menu
	void AddVote();//adding vote to Polls array
	virtual void AddCitizen() noexcept(false);//create new citizen and adding him to voterbook
	void AddParty();//create new party and resize partyarray

	//Unimplemented Base Class Interface:
	virtual void MainMenu(bool& flag);//run the menu
	virtual void AddDistrict() = 0;//create new district and resize the districts
	virtual void AddElector();//add citizen to representatives list of party
	virtual void ShowResults() = 0;//show the results of election
	
	
	virtual void printDDistrictDetails(DividedDistrict* district, PartyArray& partyarray, DynamicArray<size_t>& array, DynamicArray<size_t>& electorsDistributeArr)=0;
	virtual void printCandidateResults(DynamicArray<int> finalElectorsRes, Polls& _polls);//print the final results of candidates, each candidate and num of electors he won
	virtual void addElectorsToFinalResults(DynamicArray<int>& finalElectorsRes, DynamicArray<size_t>& electorsDistributeArr, size_t NumofParties);//Manage the electros final results array,sum from each district the electors 
	virtual void printElectors(Party& p, size_t districtindex, size_t& numofelectors);//print the representatives of the party in specific district
	virtual void printPartyResults(District* district, PartyArray& partyarray, Polls& _polls, DynamicArray<size_t>& electorsDistributeArr);//print the results of each party in specific district

	bool isValidDate(size_t year) { return ( year<=(E->getDate().getYear())-18); }//check if the year in range
	bool IDCheck(size_t id);

protected:
	Election* E;
};

enum class Select {
	ASTATE = 1, ACITIZEN, APARTY, AELECTOR, SSTATES, SCITIZENS, SPARTIES, AVOTE, RESULTS, EXIT,SAVE,LOAD
};