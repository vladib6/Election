#pragma once
#include "STRING.h" 
#include "Election.h"
#include <fstream>

class Save {

private:
	STRING FileName;
	Election* E;
	size_t elecType;
public:
	Save(STRING Fname, Election& _E, size_t _elecType) :FileName(Fname), E(&_E),elecType(_elecType) { runSave(); }
	void runSave()const ;//save the election to file


};
