#include "Polls.h"

DynamicArray<size_t> Polls::electorsDistribute(DynamicArray<size_t>& arr, float votesFor1Elector, size_t numOfElectors, size_t numofparties)const {

	DynamicArray<float> floatarr(numofparties);
	for (size_t& itr: arr ) {
		floatarr.push_back(static_cast<float>(itr));
	}

	DynamicArray<size_t> res(numofparties);
	for (int i = 0; i < numofparties;i++) {
		res.push_back(0);
	}

	for (int i = 0; i < numOfElectors; i++) {
		size_t index = findMax(floatarr, floatarr.size());
		res[index]++;
		floatarr[index] -= votesFor1Elector;
	}
	return res;
}


size_t Polls::totalVotesByParty(size_t partyIdx)const {
	size_t count=0;

	for (size_t i = 0; i < polls.size(); ++i) {
		count += polls[i][partyIdx];
	}
	return count;
}

DynamicArray<size_t> Polls::selectionSort(DynamicArray<size_t> votesArr,PartyArray& partyarray, int n)const
{
	if (n == 1) {//if there is only 1 party we return the first place
		DynamicArray<size_t> res(1);
		res.push_back((size_t)0);
		return res;
	}
	int i, j, max_idx;

	DynamicArray<size_t> res(n);
	for (i = 0; i < n; i++)
	{
		max_idx = 0;
		for (j = 1; j < n; j++) {
			if (votesArr[j] == votesArr[max_idx]) {
				if (partyarray[j].getPartyID().getPartyID() > partyarray[max_idx].getPartyID().getPartyID()) {
					max_idx = j;
				}
			}
			else if (votesArr[j] > votesArr[max_idx]) {
				max_idx = j;
			}
		}
		votesArr[max_idx] = 0;
		res.push_back(max_idx);
	}

	return res;
}

bool Polls::updatePolls(size_t _nrows, size_t _ncols) {
	return setArrSize(_nrows, _ncols);
}

bool Polls::setArrSize(size_t _nrows, size_t _ncols) {
	return(setRowSize(_nrows) && setColSize(_ncols));
}


bool Polls::updateNumOfParties(size_t _nrows) {
	return setColSize(_nrows);
}

bool Polls::updateNumOfDistricts(size_t _ncols) {
	return setRowSize(_ncols);
	
}

bool Polls::setRowSize(size_t _nrows) {
	return polls.resize(_nrows);
}


bool Polls::setColSize(size_t _ncols) {
	for (DynamicArray<size_t>& arr : polls) {
		if (!(arr.resize(_ncols)))
			return false;
	}
	return true;
}



void Polls::load(std::istream & in)
{
	size_t logRows;
	size_t logCols;
	in.read(rcastc(&logRows), sizeof(logRows));
	in.read(rcastc(&logCols), sizeof(logCols));
	polls.resize(logRows);
	for (DynamicArray<size_t>& arrRows : const_cast<DynamicArray<DynamicArray<size_t>>&>(polls)) {
		for (int i = 0; i < logCols; i++) {
			size_t num;
			in.read(rcastc(&num), sizeof(size_t));
			arrRows.push_back(num);
			}
	}
}

void Polls::save(std::ostream & out) const
{
	size_t logRows = polls.size();
	size_t logCols = polls[0].size();
	out.write(rcastcc(&logRows), sizeof(logRows));
	out.write(rcastcc(&logCols), sizeof(logCols));
	for (DynamicArray<size_t>& arrRows: const_cast<DynamicArray<DynamicArray<size_t>>&>(polls)) {
		for (size_t& nums : arrRows)
			out.write(rcastcc(&nums), sizeof(size_t));
	}
}


