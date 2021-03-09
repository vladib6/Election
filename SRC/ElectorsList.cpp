#include "ElectorsList.h"
#include <algorithm>

const Elector* ElectorsList::getElector(const CitizenID& id)const
{
	for (const Elector& elec : electorslist)
		if (*elec.getCit() == id)
			return &elec;
}

void ElectorsList::insertElector(Elector _node)
{
	electorslist.push_back(_node); numofelectors++;
	
}

const Elector& Elector::operator=(const Elector& other)
{
	if (this == &other)
		return *this;
	_el = other._el;
	_id = other._id;
	return *this;
}

void ElectorsList::insertElector(const Citizen* _nelect, const DistrictID& _id) {
	electorslist.push_back(Elector(_nelect, _id));
	numofelectors++;
}


const ElectorsList& ElectorsList::operator=(const ElectorsList& other) {
	numofelectors = other.numofelectors;
	electorslist = other.electorslist;
	return *this;
}

std::ostream& operator<<(std::ostream& os, const Elector& el) {
	os << *(el.getCit());

	return os;
}

std::ostream& operator<<(std::ostream& os, const ElectorsList& lst) {
	for (const Elector& el : lst.electorslist)
		os << el << std::endl;

	return os;
}

void Elector::save(std::ostream& _out)const {
	const_cast<CitizenID&>(_el->getID()).save(_out);
}

void ElectorsList::save(std::ostream& _out)const {
	_out.write(rcastcc(&numofelectors), sizeof(size_t));
	for (const Elector& el : electorslist)
		el.save(_out);
}


void Elector::load(std::istream& _in, Voterbook& vb) {
	CitizenID ID(_in);
	_el = vb.get(ID);
}
void ElectorsList::load(std::istream& _in, Voterbook& vb) {
	size_t count;
	_in.read(rcastc(&count), sizeof(size_t));
	for (size_t i = 0; i < count; ++i) {
		this->insertElector(Elector(_in, vb));
	}
}
