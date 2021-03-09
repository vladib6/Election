#include "District.h"
void DistrictID::setDistrictID(size_t ID) {
	districtID = ID;
}


//STATE CLASS FUNCTIONS
//STATIC VARIABLES

//CTORS AND DTORS
District::District(STRING& _name, size_t _numOfElectors) :name(_name), numOfElectors(_numOfElectors), numOfEligibleCitizens(0), votedCit(0) {
	districtSN.setDistrictID(districtSN.genDistrictID());
	districtType = "Uniform";
}

District::District(const District & other)
{
	*this = other;
}


//MEMBER FUNCTIONS


void District::operator=(const District & other)
{
	this->name = other.name;
	this->numOfElectors = other.numOfElectors;
	this->districtSN = other.districtSN;
	this->numOfEligibleCitizens = other.numOfEligibleCitizens;
	this->votedCit = other.votedCit;

}




//STATEARRAY CLASS FUNCTIONS
//
//CTORS AND DTORS

//OPERATORS OVERLOADS


std::ostream& operator<<(std::ostream& os, const District& st) {
	os << st.getSN() << " -- " <<st.getDistrictType()<<" --"<< st.getDistrictName() << " --" << st.numOfElectors << std::endl;
	return os;
}
std::ostream& operator<<(std::ostream& os, const District* st) {
	os << st->getSN() << " -- " << st->getDistrictType() << " --" << st->getDistrictName() << " --" << st->getNumOfElectors() << std::endl;
	return os;
}

std::ostream& operator <<(std::ostream& os, const DistrictID& id) {
	os << id.getDistrictID();
	return os;
}


void District::save(std::ostream& _out)const {
	districtType.save(_out);
	name.save(_out);
	districtSN.save(_out);
	_out.write(rcastcc(&numOfElectors), sizeof(size_t));
	_out.write(rcastcc(&numOfEligibleCitizens), sizeof(size_t));
	_out.write(rcastcc(&votedCit), sizeof(size_t));
}

void District::load(std::istream& _in) {
	districtType.load(_in);
	name.load(_in);
	districtSN.load(_in);
	_in.read(rcastc(&numOfElectors), sizeof(size_t));
	_in.read(rcastc(&numOfEligibleCitizens), sizeof(size_t));
	_in.read(rcastc(&votedCit), sizeof(size_t));
}

size_t DistrictID::sIDGen = 0;

