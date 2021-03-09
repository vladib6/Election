#pragma once
#include "STRING.h"
#include "Voterbook.h"
//FORWARD DECLARATIONS-------------------------------------------------------------------------------------//
class Voterbook;
class VoterbookNode;
//------------------------------------------ CLASS STATEID ------------------------------------------------//
#include "DistrictID.h"

//------------------------------------------- CLASS STATE -------------------------------------------------//
class District
{
public:
	friend class DividedDistrict;
	//CONSTRUCTORS & DESTRUCTORS --------------------------------------------------------------------------//
	District(std::istream& _in) { this->load(_in); districtType = "united"; }
	District(STRING& _name, size_t _numOfElectors);	
	District(const District& other);
	District() : name(STRING()), districtType(STRING()), numOfElectors(0), districtSN(DistrictID()), numOfEligibleCitizens(0), votedCit(0) {}
	virtual ~District() {}
	
	//Getter Functions
	const STRING& getDistrictName()const				{ return name; }
	const DistrictID& getSN()const						{ return districtSN; }
	size_t getVotedCit()const							{ return votedCit; }
	size_t getNumOfEligibleCitizens()const				{ return numOfEligibleCitizens; }
	size_t getNumOfElectors()const						{ return numOfElectors; }
	const STRING& getDistrictType() const		{ return districtType; }

	//Setter Functions
	void setNumOfEligibleCitizens(bool action) { action ? numOfEligibleCitizens++:numOfEligibleCitizens--; }
	void setVotedCit(bool action) { action ? votedCit++ : votedCit--; }


	//Class Operators
	friend std::ostream& operator<<(std::ostream& os, const District& st);//DONE
	friend std::ostream& operator<<(std::ostream& os, const District* st);
	void operator=(const District& other);

	void save(std::ostream& _out)const;
	void load(std::istream& _in);

	//Fields
private:
	STRING districtType;
	STRING name;
	size_t numOfElectors;
	DistrictID districtSN;
	size_t numOfEligibleCitizens;
	size_t votedCit;
	
};



