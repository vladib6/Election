#pragma once
#include <iostream>
#define rcastc reinterpret_cast<char*>
#define rcastcc reinterpret_cast<const char*>
class DistrictID {
	//CLASS VARIABLES
private:
	size_t districtID;
	static size_t sIDGen;
public:
	//CONSTRUCTORS & DESTRUCTORS
	DistrictID() = default;//DONE
	DistrictID(size_t id) :districtID(id) {}//DONE

	//GET FUNCTIONS
	const size_t& getDistrictID()const { return districtID; }//DONE

	//SET FUNCTIONS 
	void setDistrictID(size_t ID);//**PROBLEMATIC**//

	//CLASS OPERATORS
	bool operator==(const DistrictID& other)const { return (districtID == other.districtID); }//DONE
	friend std::ostream& operator <<(std::ostream& os, const DistrictID& id);//DONE

	//MEMBER FUNCTIONS
	size_t genDistrictID() { return ++sIDGen; }//DONE

	void save(std::ostream& _out)const { _out.write(rcastcc(&districtID), sizeof(districtID)); }
	void load(std::istream& _in) { _in.read(rcastc(&districtID), sizeof(districtID)); }
};
