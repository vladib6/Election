#pragma once
#include "ElectorsListArray.h"
#include "PartyID.h"
#define rcastc reinterpret_cast<char*>
#define rcastcc reinterpret_cast<const char*>

class Party
{
	friend class PartyArray;
private:
	STRING prtName;
	PartyID prtID;
	const Citizen* candidate;
	ElectorsListArray electArr;

public:
	//Ctors and Dtors
	Party():
	candidate(nullptr),prtName(STRING()){}
	Party(STRING& _pName,const Citizen* _cand):
		prtName(_pName),candidate(_cand),prtID(prtID.genPartyID()){}
	Party(STRING& _pName,const Citizen* _cand,PartyID& _pID):
		prtName(_pName),candidate(_cand),prtID(_pID){}
	Party(STRING& _pname, const Citizen* _cand, size_t _numDist) :
		prtName(_pname), candidate(_cand) { electArr.setSize(_numDist); }
	Party(STRING& _pname, const Citizen* _cand, PartyID& _pID, size_t _numDist) :
		prtName(_pname), candidate(_cand), prtID(_pID){ electArr.setSize(_numDist); }
	Party(const Party&) = delete;

	Party(std::istream& _in, Voterbook& vb);

	//Getter Functions
	const STRING& getPrtName()const { return prtName; }
	const PartyID& getPartyID()const { return prtID; }
	const Citizen* getCandidate()const { return candidate; }
	const ElectorsList& getElecList(size_t _idx)const { return electArr[_idx]; }
	const Elector& getElector(CitizenID& _id) { return electArr.getElector(_id); }
	const Elector& getElector(CitizenID& _id, size_t _idx) { return electArr.getElector(_id, _idx); }
	size_t getElectArrSize()const { return electArr.getSize(); }
	const ElectorsListArray& getElectArr()const { return electArr; }
	size_t getPartyIDX()const { return (prtID.getPartyID() - 1); }

	//Setter Functions
	void setPrtName(STRING& _pName) { prtName = _pName;}
	void setCandidate(const Citizen* _cand) { candidate = _cand; }
	void setElectArrSize(size_t _size) {  electArr.setSize(_size); }

	//Class Operators
	void printFunc();//made for out stream opeator 
	const Party& operator=(const Party& other);
	friend std::ostream& operator<<(std::ostream& os, const Party& p);

	//Methods 
	//Elector insertion:
	void insertElect(const Citizen& _nelect, size_t _idx) {   electArr.insertElector(&_nelect, _idx);}
	void insertElect(const Citizen* _nelect, size_t _idx) {   electArr.insertElector(_nelect, _idx); }
	void insertElect(Elector* _nelect, size_t _idx) { electArr.insertElector(*_nelect, _idx); }

	void save(std::ostream& _out) const;
	void load(std::istream& _in, Voterbook& vb);

};
