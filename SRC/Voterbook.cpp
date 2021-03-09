#include <iostream>
#include "Voterbook.h"
#include "DistrictsArray.h"
#include "Compare.h"
#include <algorithm>

bool Voterbook::isEmpty()
{
	return voterbook.empty();
}

void Voterbook::insertCitizen(const Citizen* cit)
{
	if (get(cit->getID())) {
		delete cit;
		throw Generalexcep("Already exist user with same id");
	}
	else
	    voterbook.push_back(const_cast<Citizen*>(cit));
	voterbook.sort(Compare());

}



Voterbook::Voterbook(const Voterbook& other)
{
	*this = other;
}

Voterbook::~Voterbook()
{
	for (auto itr : voterbook)
		delete itr;
}


void Voterbook::operator=(const Voterbook& other)
{
	voterbook.assign(other.voterbook.begin(), other.voterbook.end());

}


const Citizen* Voterbook::get(const CitizenID& id)const
{
	const Citizen* cit = nullptr;
	for (auto itr : voterbook) {
		if (id == itr->getID()) 
			cit = itr;
	}
	return cit;
}

void Voterbook::save(std::ostream& out) const
{
	int size = (*this).voterbook.size();
	out.write(rcastcc(&size), sizeof(size));
	for (auto itr : voterbook)
		itr->save(out);
}

void Voterbook::load(std::istream& in, DistrictsArray& districtsarr)
{
	int size;
	in.read(rcastc(&size), sizeof(size));
	size_t districtid;

	for (int i = 0; i < size; i++) {
		in.read(rcastc(&districtid), sizeof(districtid));
		this->voterbook.push_back(new Citizen(in, districtsarr[DistrictID(districtid)]));
	}

}

std::ostream& operator<<(std::ostream& os, const Voterbook& vb)
{
	for (auto itr = vb.voterbook.begin(); itr != vb.voterbook.end(); itr++) {
		std::cout << *(*itr);
   }
	return os;
}

