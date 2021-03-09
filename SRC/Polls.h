#pragma once
#include "PartyArray.h"
#define rcastc reinterpret_cast<char*>
#define rcastcc reinterpret_cast<const char*>

class Polls
{
private:
	DynamicArray<DynamicArray<size_t>> polls;

public:
	Polls(const Polls&) = delete;
	Polls() = default;
	

//Methods
	bool updateNumOfDistricts(size_t _nrows);
	bool updateNumOfParties(size_t _ncols);
	bool updatePolls(size_t _nrows, size_t _ncols);

	DynamicArray<size_t> electorsDistribute(DynamicArray<size_t>& arr, float votesFor1Elector, size_t numOfElectors, size_t numofparties)const;//return array that store how much electors get each party in this state
	bool voteToParty(size_t _partyIdx, size_t _districtIdx) { (polls[_districtIdx][_partyIdx])++; return true; }//add vote to party
	size_t totalVotesByParty(size_t partyIdx)const;//calculate the all votes that party get in all districts
	DynamicArray<size_t> selectionSort(DynamicArray<size_t> votesArr,PartyArray& partyarray, int n) const;//sort the votes in district Descending return array with id of party
	DynamicArray<DynamicArray<size_t>> getPollsArr()const { return polls; };
	void load(std::istream & in);
	void save(std::ostream & out) const;

	DynamicArray<size_t>& operator[](size_t _idx)const { return const_cast<DynamicArray<size_t>&>(polls[_idx]); }
	template <typename T>
	size_t findMax(T& arr, size_t size) const {//return the index of max element in array
		size_t maxindex = 0;
		for (int i = 1; i < size; i++) {
			if (arr[i] > arr[maxindex])
				maxindex = i;
		}
		return maxindex;
	}
private:
	bool setArrSize(size_t _nrows, size_t _ncols);
	bool setColSize(size_t _ncols);
	bool setRowSize(size_t _nrows);
	


};

