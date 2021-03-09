#include "PartyArray.h"

bool PartyArray::setSize(size_t _nsize) {
	partyArray.resize(_nsize);
	return(partyArray.size() == _nsize);
}



bool PartyArray::addParty(STRING& _name, const Citizen* _cand){
	partyArray.push_back(Party(_name, _cand));
	
	return (_name == partyArray[this->getSize() - 1].prtName && _cand == partyArray[this->getSize() - 1].candidate);
}

std::ostream& operator<<(std::ostream& os, const PartyArray& parr) {
	for (auto itr= const_cast<PartyArray&>(parr).partyArray.begin(); itr != const_cast<PartyArray&>(parr).partyArray.end(); ++itr)
		os << *itr << std::endl;

	return os; }

void PartyArray::load(std::istream& _in, Voterbook& vb) {
	size_t numOfParties = 0;
	_in.read(rcastc(&numOfParties), sizeof(size_t));
	partyArray.resize(numOfParties);
	for (size_t i = 0; i < numOfParties; ++i)
		const_cast<Party&>(partyArray[i]).load(_in, vb);
}


void PartyArray::save(std::ostream& _out)const {
	size_t numOfParties = partyArray.size();
	_out.write(rcastcc(&numOfParties), sizeof(size_t));
	for (const Party& party: const_cast<DynamicArray<Party>&>(partyArray)) {
		party.save(_out);
	}
}









