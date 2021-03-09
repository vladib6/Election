#pragma once
#include "STRING.h"
#include "Voterbook.h"
#define rcastc reinterpret_cast<char*>
#define rcastcc reinterpret_cast<const char*>
//FORWARD DECLARATIONS-------------------------------------------------------------------------------------//
class Voterbook;
class VoterbookNode;


class DividedDistrict:public District {
public:
	//CONSTRUCTORS & DESTRUCTORS --------------------------------------------------------------------------//
	DividedDistrict(STRING& _name, size_t _numOfElectors);
	DividedDistrict(const DividedDistrict& other);
	DividedDistrict(std::istream& _in) { this->load(_in); districtType = "Devided"; };
	DividedDistrict() = default;
	friend std::ostream& operator<<(std::ostream& os, const DividedDistrict* st);



};