#include "PartyID.h"

//===========================Class PartyID ==================================/
std::ostream& operator<<(std::ostream& os, const PartyID& party){
	os << party.partyID;
	return os;
}

void PartyID::save(std::ostream& _out)const {
	_out.write(rcastcc(&partyID), sizeof(size_t));
}


void PartyID::load(std::istream& _in) {
	_in.read(rcastc(&partyID), sizeof(size_t));
}

size_t PartyID::pIDGen = 0;
