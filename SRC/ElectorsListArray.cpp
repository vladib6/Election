#include "ElectorsListArray.h"

const Elector& ElectorsListArray::getElector(const CitizenID& _id)const {
	const Elector* temp;
	for (const ElectorsList& list :const_cast<DynamicArray<ElectorsList>&>(earr)){
		if ((temp = list.getElector(_id)))
			return *temp;
	}
}

const ElectorsListArray& ElectorsListArray::operator=(const ElectorsListArray& other) {
	numoflists = other.numoflists;
	earr = other.earr;
	return *this;
}


void ElectorsListArray::insertElector(Elector& _nelect, size_t _idx) {

	 const_cast<ElectorsList&>(earr[_idx]).insertElector(_nelect);
}

void ElectorsListArray::insertElector(const Citizen* _nelect, size_t _idx) {

	  const_cast<ElectorsList&>(earr[_idx]).insertElector(_nelect);
}

std::ostream& operator<<(std::ostream& os, const ElectorsListArray& earr) {
	for (const ElectorsList& lst : const_cast<ElectorsListArray&>(earr).earr)
		os << lst << std::endl;
	return os;
}

void ElectorsListArray::save(std::ostream& _out)const {
	_out.write(rcastcc(&numoflists), sizeof(size_t));
	for (const ElectorsList& lst : const_cast<DynamicArray<ElectorsList>&>(earr))
		lst.save(_out);
	
}

void ElectorsListArray::load(std::istream& _in, Voterbook& vb) {
	_in.read(rcastc(&numoflists), sizeof(size_t));
	setSize(numoflists);
	for (ElectorsList& lst : const_cast<DynamicArray<ElectorsList>&>(earr))
		lst.load(_in, vb);
	
}