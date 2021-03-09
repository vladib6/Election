#pragma once
#include <iostream>
#include "Citizen.h"
#include "District.h"
#include <list>
#include "Exceptions.h"
class Citizen;
class District;
class CitizenID;
class DistrictsArray;

class Voterbook {
private:

	std::list<Citizen*> voterbook;
public:
	Voterbook()=default;
	Voterbook(const Voterbook& other);
	~Voterbook();
	bool isEmpty();//return 1 if list empty else return 0
	void insertCitizen(const Citizen* cit) noexcept(false);//add citizen to voterbook
	std::list<Citizen*>::iterator getHead() { return voterbook.begin(); }//return pointer to first node in list
	const Citizen* get(const CitizenID& id)const;//return pointer to citizen from voterbook according to citizenID that sent as argument
	friend class District;

	//OPERATORS----------
	void operator=(const Voterbook& other);
	friend std::ostream& operator<<(std::ostream& os, const Voterbook& vb);

	//FILE FUNCTIOS------
	void save(std::ostream& out)const;//save election to file
	void load(std::istream& in, DistrictsArray& districtsarr);//load election from file

};
