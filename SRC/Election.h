#pragma once
#include <iostream>
#include "Voterbook.h"
#include "DistrictsArray.h"
#include "Polls.h"
#include "DividedDistrict.h"
#define rcastc reinterpret_cast<char*>
#define rcastcc reinterpret_cast<const char*>

#define CCprt const_cast<Party&>
#define CCprtarr const_cast<PartyArray&>

class Election {

private:
	Date* date;
	Voterbook* voterbook;
	DistrictsArray* districts;
	PartyArray* partyarray;
	Polls* polls;
	
public:
	Election(Date& elecDate);
	Election(std::istream& _in) :date(new Date()), districts(new DistrictsArray()), voterbook(new Voterbook()),partyarray(new PartyArray()),
		polls(new Polls()) { this->load(_in); }
	~Election();
	

	//GETTER
	const DistrictsArray& getDistrictArray()const { return *districts; }
	const PartyArray& getPartyArray()const { return *partyarray; }
	const Date& getDate()const { return *date; }
	const Voterbook& getVoterbook()const { return *voterbook; }
	const Polls& getPolls()const { return *polls; }
    
    //SAVE&LOAD
	void save(std::ostream& out)const;
	void load(std::istream& _in,bool _existelection=false);

	void resetElections();




};