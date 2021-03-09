#pragma once

#include <iostream>
#include "STRING.h"
#include "Date.h"
#include "District.h"


class District;
class STRING;
class Date;

class CitizenID {
private:
	size_t citID;
public:
	CitizenID(size_t id) :citID(id) {}
	CitizenID(std::istream& in);
	CitizenID() = default;
	const size_t& getCitizenID()const { return citID; }//return citizen ID
	bool operator==(const CitizenID& rhs)const;
	bool operator==(const size_t& rhs)const;
	void operator=(const CitizenID& rhs);
	bool operator>(const CitizenID& other)const { return(citID > other.citID); }
	bool operator>=(const CitizenID& other)const { return (citID >= other.citID); }
	bool operator<(const CitizenID& other)const { return !(*this >= other); }
	bool operator<=(const CitizenID& other)const { return !((*this) > other); }

	friend std::ostream& operator<<(std::ostream& os, const CitizenID& ID);
	void load(std::istream& in);//load citizenID from file
	void save(std::ostream& out)const;//save citizenID to file
};


class Citizen
{
public:
	Citizen() :name(STRING()),ID(CitizenID()),birthDate(Date()),district(nullptr),citVoted(false){};
	Citizen(std::istream& in, District* _district);
	Citizen(const Citizen& rhs):name(rhs.name), ID(rhs.ID), birthDate(rhs.birthDate), district(rhs.district), citVoted(rhs.citVoted) {}
	Citizen(const STRING& name, const CitizenID& id, const Date& bDate, const District*& st) :name(name), ID(id), birthDate(bDate), district(st), citVoted(false) {}
	Citizen(STRING& name, CitizenID& id, Date& bDate, District*& st) :name(name), ID(id), birthDate(bDate), district(st), citVoted(false) {}
	const CitizenID& getID()const					{ return ID; };
	const STRING& getName()const					{ return name; };
	const Date& getDate()const						{ return birthDate; };
	const District& getDistrict()const				{ return *district; }
	bool getCitVoted()const							{ return citVoted; };
	void setCitVoted(bool flag)						{ citVoted = flag; }

	friend std::ostream& operator<<(std::ostream& os, const Citizen& cit);
	friend std::ostream& operator<<(std::ostream& os, Citizen* cit);
	bool operator==(const CitizenID& id)const		{ return(ID == id); }
	bool operator==(const Citizen& other)const		{ return(ID == other.ID); }
	bool operator>(const Citizen& other)const		{ return ID>other.ID;}
	bool operator>=(const Citizen& other)const		{ return !(ID<other.ID); }
	bool operator<(const Citizen& other)const		{ return ID<other.ID; }
	bool operator<=(const Citizen& other)const		{ return !(ID > other.ID); }

	void load(std::istream& in, District* _district);
	void save(std::ostream& out) const;
private:
	STRING name;
	CitizenID ID;
	Date birthDate;
	const District* district;
	bool citVoted;
};

