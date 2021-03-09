#include "Citizen.h"

std::ostream& operator<< (std::ostream& os, const Citizen& cit)
{
	os << "ID: " << cit.getID() << " -- " << "Name: " << cit.getName() << " -- " << "Birthdate: " << cit.getDate() << " -- " << "District: " << cit.getDistrict().getDistrictName() << std::endl;
	return os;
}

std::ostream& operator<< (std::ostream& os, Citizen* cit)
{
	os << "ID: " << cit->getID() << " -- " << "Name: " << cit->getName() << " -- " << "Birthdate: " << cit->getDate() << " -- " << "District: " << cit->getDistrict().getDistrictName() << std::endl;
	return os;
}

std::ostream& operator<<(std::ostream& os, const CitizenID& ID) {
	os << ID.getCitizenID();
	return os;
}


CitizenID::CitizenID(std::istream& in)
{
	in.read(rcastc(&citID), sizeof(citID));
}

bool CitizenID::operator==(const CitizenID& rhs)const {
	return(citID == rhs.citID);
}

bool CitizenID::operator==(const size_t& rhs)const {
	return (citID == rhs);
}

void CitizenID::operator=(const CitizenID& rhs)
{
	this->citID = rhs.citID;
}

void CitizenID::load(std::istream& in)
{
	in.read(rcastc(&citID), sizeof(citID));
}

void CitizenID::save(std::ostream& out) const
{
	out.write(rcastcc(&citID), sizeof(citID));

}

Citizen::Citizen(std::istream& in, District* _district){
	this->load(in, _district);
}

void Citizen::load(std::istream& in, District* _district)
{
	district = _district;
	name.load(in);
	ID.load(in);
	birthDate.load(in);
	in.read(rcastc(&citVoted), sizeof(citVoted));
}

void Citizen::save(std::ostream& out) const
{
	size_t districtid = district->getSN().getDistrictID();
	out.write(rcastcc(&districtid), sizeof(districtid));
	const_cast<STRING&>(name).save(out);
	ID.save(out);
	birthDate.save(out);
	out.write(rcastcc(&citVoted), sizeof(citVoted));

}
