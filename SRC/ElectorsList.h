#pragma once
#include <iostream>
#include <list>
#include "Citizen.h"
#include "Compare.h"

class Elector {
private:
	const Citizen* _el;
	DistrictID _id;
public:
	Elector(const Citizen* el = nullptr, const DistrictID& id = 0) :_el(el), _id(id) {}
	Elector(std::istream& _in, Voterbook& vb) :_el(nullptr){ this->load(_in, vb); }
	const Citizen* getCit()const { return _el; }
	const DistrictID& getDistrict()const { return _id; }
	bool operator==(const Elector& other)const { return (_el == other._el) && (_id == other._id); }
	bool operator!=(const Elector& other)const { return !(*this == other); }
	bool operator<(const Elector& other)const { return *_el < *(other._el); }
	bool operator>(const Elector& other)const { return *_el > *(other._el); }
	bool operator<=(const Elector& other)const { return *_el <= *(other._el); }
	bool operator>=(const Elector& other)const { return *_el >=*(other._el); }
	const Elector& operator=(const Elector& other);
	friend std::ostream& operator<<(std::ostream& os, const Elector& el);

	void save(std::ostream& _out)const;
	void load(std::istream& _in, Voterbook& vb);
};
class ElectorsList
{
private:
	std::list<Elector> electorslist;
	size_t numofelectors;
public:
	ElectorsList():numofelectors(0){}
	size_t size() { return electorslist.size(); }
	const Elector* getElector(const CitizenID& id)const;
	void insertElector(Elector _node);
	void insertElector(const Citizen* _nelect, const DistrictID& _id = 0);
	bool operator==(const ElectorsList& other)const { return electorslist == other.electorslist; }
	bool operator!=(const ElectorsList& other)const { return !(*this == other); }
	friend std::ostream& operator<<(std::ostream& os, const ElectorsList& lst);
	const ElectorsList& operator=(const ElectorsList& other);
	const std::list<Elector>& getlist()const{ return electorslist; }

	void save(std::ostream& _out)const;
	void load(std::istream& _in, Voterbook& vb);
};

