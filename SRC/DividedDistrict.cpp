#include "DividedDistrict.h"




DividedDistrict::DividedDistrict(STRING& _name, size_t _numOfElectors) :District(_name,_numOfElectors) {
	districtType = "Divided";
}

DividedDistrict::DividedDistrict(const DividedDistrict& other)
{
	*this = other;
}

std::ostream& operator<<(std::ostream& os, const DividedDistrict* st) {
	os << (*st).District::getSN() << " -- " << (*st).getDistrictType() << " --" << (*st).District::getDistrictName() << " --" << (*st).District::getNumOfElectors() << std::endl;
	return os;
}