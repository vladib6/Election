#include "Party.h"

void Party::printFunc(){
	std::cout << "Party ID: " << prtID << std::endl;
	std::cout << "Party name: " << prtName << std::endl;
	std::cout << "Party Candidate name: " << *candidate<<std::endl;
}

const Party & Party::operator=(const Party & other)
{
	prtName = other.prtName;
	prtID = other.prtID;
	candidate=other.candidate;
	electArr=other.electArr;
	return *this;
}



std::ostream& operator<<(std::ostream& os, const Party& p) {
	std::cout << "Party ID: " << p.prtID << std::endl;
	std::cout << "Party name: " << p.prtName << std::endl;
	std::cout << "Party Candidate name: " << *(p.candidate) << std::endl;
	std::cout << "Electors: " << p.electArr << std::endl;

	return os;
}

void Party::save(std::ostream& _out)const {
	prtName.save(_out);
	prtID.save(_out);
	const_cast<CitizenID&>(candidate->getID()).save(_out);
	electArr.save(_out);
}

void Party::load(std::istream& _in, Voterbook& vb) {
	prtName.load(_in);
	prtID.load(_in);
	CitizenID candID(_in);
	candidate = vb.get(candID);
	electArr.load(_in, vb);
}


Party::Party(std::istream& _in, Voterbook& vb) {
	this->load(_in, vb);
}


