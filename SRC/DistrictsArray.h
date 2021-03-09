#pragma once
#include "DynamicArray.h"
#include "District.h"
#include "DividedDistrict.h"
class DistrictsArray
{
private:
	DynamicArray<District*> darr;
	size_t numofdistricts;
	bool iscopy;
public:
	DistrictsArray():darr(DynamicArray<District*>(0)),numofdistricts(0),iscopy(false){}
	DistrictsArray(const DistrictsArray& other) :darr(other.darr), numofdistricts(other.numofdistricts), iscopy(true) {}
	~DistrictsArray();

	const DynamicArray<District*>& getArr()const        { return darr; }//new added
	size_t getDistrictIDX(const DistrictID& _id)const	{ return (_id.getDistrictID() - 1); }
	size_t getDistrictIDX(const District& _st)const		{ return (_st.getSN().getDistrictID() - 1); }
	size_t getSize()const								{ return darr.size(); }
	size_t getCapacity()const							{ return darr.capcity(); }
	size_t getNumofDistricts()const						{ return numofdistricts; }
	void setSize(size_t size)							{ darr.resize(size); }
	District* operator[](size_t _idx)const				{ return darr[_idx]; }
	District* operator[](size_t _idx)					{ return darr[_idx]; }
	District* operator[](const DistrictID& _id)			{ return darr[getDistrictIDX(_id)]; }
	void operator+=(District* _ndistrict)				{ darr.push_back(_ndistrict); numofdistricts++; }
	const DistrictsArray& operator=(const DistrictsArray& other) = delete;
	void insertDistrict(District* _ndistrict) { darr.push_back(_ndistrict); numofdistricts++; }

	friend std::ostream& operator<<(std::ostream& os, const DistrictsArray& starr);
	
	void save(std::ostream& _out) const;
	void load(std::istream& _in);

};

enum class DistrictType {
	UNITED = 1, DIVIDED = 2
};



