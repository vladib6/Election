#pragma once
#include "Party.h"
#include "DynamicArray.h"
#define rcastc reinterpret_cast<char*>
#define rcastcc reinterpret_cast<const char*>

class PartyArray
{
private:
	//Class Fields
	DynamicArray<Party> partyArray;

	//Class Member Funcitons
public:
	PartyArray() = default;
	PartyArray(const PartyArray& RHS) = delete;
	

	//Getter Functions
	size_t getPrtIDX(PartyID& _id)const { return (_id.getPartyID()-1); }
	size_t getSize()const { return partyArray.size(); }
	size_t getCapacity()const { return partyArray.capcity(); }
	size_t getNumofParties()const { return partyArray.size();}
	const ElectorsListArray& getElecArr(size_t _idx)const { return partyArray[_idx].getElectArr(); }
	const DynamicArray<Party>& getPartyArray()const { return partyArray; }

	//Setter Functions
private:
	bool setSize(size_t _nsize);


public:
	//Class Operators
	void operator=(const PartyArray& RHS) = delete;
	const Party& operator[](size_t _idx)const { return partyArray[_idx]; }
	const Party& operator[](PartyID _id)const { return partyArray[getPrtIDX(_id)]; }
	friend std::ostream& operator<<(std::ostream& os, const PartyArray& parr);
	
	//Other Methods
	bool addParty(STRING& name, const Citizen* _cand);
	void save(std::ostream& _out) const;
	void load(std::istream& _in, Voterbook& vb);
};


