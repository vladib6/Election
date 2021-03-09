#include "StandardMenu.h"

void StandardMenu::AddDistrict() {
	std::cout << "Enter the name of district :" << std::endl;
	std::cin.ignore();
	STRING name;
	name.getStrInput();

	size_t numOfElectors;
	std::cout << "Enter the num of electors in this district :" << std::endl;
	std::cin >> numOfElectors;
	if (numOfElectors <= 0)
		throw Generalexcep("number of electors are zero or negative");
	size_t districtType;
	std::cout << "Select type of district:    1-Uniform      0-Divided" << std::endl;
	std::cin >> districtType;
	if (districtType != 0 && districtType != 1) 
		throw Generalexcep("invalid select type of district");

	District* newDistrict;
	if (districtType)
		newDistrict = new District(name, numOfElectors);
	else
		newDistrict = new DividedDistrict(name, numOfElectors);
	size_t numOfDistricts{};
	try
	{
		const_cast<DistrictsArray&>(E->getDistrictArray()).insertDistrict(newDistrict);//district addition
	}
	catch (const std::bad_alloc& e)
	{
		delete newDistrict;
		std::cout << "Allocation failed: " << e.what() << std::endl;
		throw;
	}
	catch (const std::out_of_range& e)
	{
		delete newDistrict;
		std::cout << "Out of range error: " << e.what() << std::endl;
		throw;
	}
	numOfDistricts = E->getDistrictArray().getNumofDistricts();
	const_cast<Polls&>(E->getPolls()).updateNumOfDistricts(numOfDistricts);
	for (Party& party : const_cast<DynamicArray<Party>&>(E->getPartyArray().getPartyArray())) {
		party.setElectArrSize(numOfDistricts);
	}

	std::cout << "District Added" << std::endl;
}


void StandardMenu::ShowResults() {
	printWinnerInDistricts();
}

void StandardMenu::printWinnerInDistricts() {
	Polls& polls = const_cast<Polls&>(E->getPolls());

	DynamicArray<int> finalElectorsRes (E->getPartyArray().getNumofParties());//save how much electors get each candidate,index 0 =electors of candidate of party 1 and etc...
	for (int i = 0; i < E->getPartyArray().getNumofParties(); i++) {
		finalElectorsRes.push_back(0);
	}
	std::cout << "---####---------  The Winners in each District  ----------####---" << std::endl;
	std::cout << "------------------------------------------------------------- " << std::endl;
	std::cout << "Election " << E->getDate() << std::endl;
	std::cout << "------------------------------------------------------------- " << std::endl;

	for (size_t i = 0; i < E->getDistrictArray().getNumofDistricts(); i++) {
		DynamicArray<size_t> array = polls.selectionSort(polls[i], CCprtarr(E->getPartyArray()),E->getPartyArray().getNumofParties());//return sorted array with index of party in this district that get the most votes Descending
		District* district = const_cast<District*>(E->getDistrictArray()[i]);
		DynamicArray<size_t> electorsDistributeArr = polls.electorsDistribute(polls[i], (static_cast<float>((*district).getVotedCit()) / static_cast<float>(district->getNumOfElectors())), district->getNumOfElectors(),E->getPartyArray().getNumofParties());

		if (typeid(*district) == typeid(DividedDistrict)) {
			DividedDistrict* DS = dynamic_cast<DividedDistrict*>(district);
			addElectorsToFinalResults(finalElectorsRes, electorsDistributeArr, E->getPartyArray().getNumofParties());
			printDDistrictDetails(DS, CCprtarr(E->getPartyArray()), array, electorsDistributeArr);
		}
		else {
			finalElectorsRes[array[0]] += district->getNumOfElectors();
			printUDistrictDetails(district, CCprtarr(E->getPartyArray()), array);
		}

		printPartyResults(district, CCprtarr(E->getPartyArray()), polls, electorsDistributeArr);
		std::cout << "################################ " << std::endl;
		std::cout << "################################ " << std::endl;
		std::cout << std::endl;
	}

	printCandidateResults(finalElectorsRes, polls);
}


void StandardMenu::printUDistrictDetails(District* district, PartyArray& partyarray, DynamicArray<size_t>& array) {
	STRING districtname = district->getDistrictName();
	size_t electors = district->getNumOfElectors();

	float districtvotingpercent = 0;
	if (district->getNumOfEligibleCitizens())
		districtvotingpercent = ((static_cast<float>(district->getVotedCit()) / static_cast<float>(district->getNumOfEligibleCitizens()))) * 100;
	else
		std::cout << "There are no Eligible Citizens in this District " << std::endl;
	STRING candidatename = partyarray[array[0]].getCandidate()->getName();
	STRING partyname = partyarray[array[0]].getPrtName();
	std::cout << "District ID: " << district->getSN().getDistrictID() << " --District Type: " << district->getDistrictType() << "--- District name: " << districtname.getString() << "--- Number of Electors in district: " << electors << "--- Winner: " << candidatename.getString() << "--- From party: " << partyname.getString() << "--- Voting percent: " << districtvotingpercent << "%" << std::endl;
	std::cout << "---------------------------- " << std::endl;
}


void StandardMenu::printDDistrictDetails(DividedDistrict* district, PartyArray& partyarray, DynamicArray<size_t>& array, DynamicArray<size_t>& electorsDistributeArr) {
	STRING districtname = district->getDistrictName();
	size_t electors = district->getNumOfElectors();

	float districtvotingpercent = 0;
	if (district->getNumOfEligibleCitizens())
		districtvotingpercent = ((static_cast<float>(district->getVotedCit()) / static_cast<float>(district->getNumOfEligibleCitizens()))) * 100;
	else
		std::cout << "There are no Eligible Citizens in this District " << std::endl;

	std::cout << "District ID: " << district->getSN().getDistrictID() << " --District Type: " << district->getDistrictType() << "--- District name: " << districtname.getString() << "--- Number of Electors in district: " << electors << "--- Voting percent: " << districtvotingpercent << "%" << std::endl;
	for (int i = 0; i < partyarray.getNumofParties(); i++) {
		if (electorsDistributeArr[array[i]] > 0) {
			std::cout << "Candidate: " << const_cast<STRING&>(partyarray[array[i]].getCandidate()->getName()).getString() << " ---Num of electors in this district: " << electorsDistributeArr[array[i]] << std::endl;
			std::cout << "-----------------------------" << std::endl;
		}
	}
}