#include "DistrictsArray.h"

DistrictsArray::~DistrictsArray() {
	if (!iscopy) {
		for (District* d : darr)
			delete[](d);
	}
}

void DistrictsArray::save(std::ostream& _out) const {
	DistrictType type;
	_out.write(rcastcc(&numofdistricts), sizeof(size_t));
	for (const District* d : const_cast<DynamicArray<District*>&>(darr)) {
		if (typeid(*d) == typeid(DividedDistrict))
			type = DistrictType::DIVIDED;
		else
			type = DistrictType::UNITED;
		_out.write(rcastc(&type), sizeof(DistrictType));
		d->save(_out);
	}


}

void DistrictsArray::load(std::istream& _in) {
	DistrictType type;
	_in.read(rcastc(&numofdistricts), sizeof(size_t));
	setSize(numofdistricts);
	for (District*& d : darr) {
		_in.read(rcastc(&type), sizeof(DistrictType));
		switch (type) {
		case DistrictType::DIVIDED:
			d = new DividedDistrict(_in);
			break;
		case DistrictType::UNITED:
			d = new District(_in);
			break;
		}
	}
}


std::ostream& operator<<(std::ostream& os, const DistrictsArray& starr)
{
	for (const District* d : const_cast<DynamicArray<District*>&>(starr.darr))
		os << *d;

	return os;
}
