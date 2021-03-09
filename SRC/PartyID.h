#pragma once
#include <iostream>
#define rcastc reinterpret_cast<char*>
#define rcastcc reinterpret_cast<const char*>

class PartyID {
private:
	size_t partyID;
	static size_t pIDGen;
public:
	//CTORS AND DTORS
	PartyID(std::istream& _in) { this->load(_in); }
	PartyID(bool action = false) { partyID = action ? genPartyID() : 0; }//DONE
	PartyID(size_t id) :partyID(id) { if (id <= 0) throw std::invalid_argument("id number is zero or negative"); }//DONE
	

	size_t genPartyID() { return ++pIDGen; }//DONE
	
	//SETTER FUNC
	const size_t& getPartyID()const { return partyID; }//DONE
	

	//OPERATORS
	void operator=(const size_t id) { partyID = id; }
	void operator=(const PartyID& id) { partyID = id.partyID; }
	bool operator ==(const size_t id) { return (partyID == id); }
	bool operator ==(const PartyID& id) { return (partyID == id.partyID); }

	friend std::ostream& operator<<(std::ostream& os, const PartyID& party);
	
	
	void save(std::ostream& _out)const;
	void load(std::istream& _in);
};

