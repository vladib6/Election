#pragma once
#include "DynamicArray.h"
#include "ElectorsList.h"

class ElectorsListArray
{
private:
	DynamicArray<ElectorsList> earr;
	size_t numoflists;
public:
	ElectorsListArray():earr(DynamicArray<ElectorsList>()),numoflists(0){}
	size_t getsize() { return earr.size(); }
	const ElectorsList& getlist(size_t _idx) { return earr[_idx]; }
	const Elector& getElector(const CitizenID& _id, size_t _idx)const{ return *(earr[_idx].getElector(_id)); }
	const Elector& getElector(const CitizenID& _id)const;
	const ElectorsListArray& operator=(const ElectorsListArray& other);
	const ElectorsList& operator[](size_t _idx)const { return earr[_idx]; }
	void insertElector(Elector& _nelect, size_t _idx);//DONT
	void insertElector(const Citizen* _nelect, size_t _idx);//DONE
	bool addList(ElectorsList& _nlist) { earr.push_back(_nlist); return(_nlist == earr[numoflists] ? true : false); }//DONE
	size_t getSize()const { return earr.size(); }
	size_t setSize(size_t size) { numoflists = size; return earr.resize(size); }

	friend std::ostream& operator<<(std::ostream& os, const ElectorsListArray& earr);

	void save(std::ostream& _out)const;
	void load(std::istream& _in, Voterbook& vb);

};

