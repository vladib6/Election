#include "SimpleMenu.h"

void SimpleMenu::MainMenu(bool& flag) {
	int userchoice = 0;

	if (flag) {
		size_t numOfElect{};
		std::cout << "Enter number of Electors: ";
		std::cin.ignore();
		std::cin >> numOfElect;
		if (numOfElect <= 0)
			throw Generalexcep("invalid number of electors");
		STRING countryName = "Country";

		const_cast<DistrictsArray&>(E->getDistrictArray()) += (new DividedDistrict(countryName, numOfElect));//create a single divided district for simple election
		const_cast<Polls&>(E->getPolls()).updateNumOfDistricts(1);
	}
	while (userchoice != 10) {//main loop
		printMenu();
		std::cin >> userchoice;
		switch (static_cast<Select>(userchoice))
		{
		case Select::ASTATE://ADD STATE
		{
			try
			{
				AddDistrict();
			}
			catch (const Generalexcep& e) {
				std::cout << "Error: " << e.what() << std::endl;
			}
			catch (const std::bad_alloc& e) {
				std::cout << "Allocation failed: " << e.what() << std::endl;
				throw;
			}
			catch (const std::out_of_range e) {
				std::cout << "Out of range error: " << e.what() << std::endl;
			}
			catch (const std::invalid_argument e) {
				std::cout << e.what() << std::endl;
			}
			break;
		}
		case Select::ACITIZEN://ADD Citizen
		{
			try
			{
				AddCitizen();

			}
			catch (const Generalexcep& ex)
			{
				std::cout << "Error: " << ex.what() << std::endl;
			}
			catch (const std::bad_alloc& e) {
				std::cout << "Allocation failed: " << e.what() << std::endl;
				throw;
			}
		
			break;
		}
		case Select::APARTY://ADD Party
			try
			{
				AddParty();
			}
			catch (const Generalexcep& ex)
			{
				std::cout << "Error: " << ex.what() << std::endl;;
			}
			catch (const std::bad_alloc& e) {
				std::cout << "Allocation failed: " << e.what() << std::endl;
				throw;
			}
			catch (const std::out_of_range& e) {
				std::cout << "Out of range error: " << e.what() << std::endl;
			}
			break;

		case Select::AELECTOR://ADD Citizen as Elector
			try
			{
			AddElector();
			}
			catch (const Generalexcep& ex)
			{
				std::cout << "Error: " << ex.what() << std::endl;;
			}
			catch (const std::bad_alloc& e) {
				std::cout << "Allocation failed: " << e.what() << std::endl;
				throw;
			}
			catch (const std::invalid_argument& e) {
				std::cout <<  e.what() << std::endl;
			}
			break;

		case Select::SSTATES://SHOW All Districts
			std::cout << E->getDistrictArray();
			break;

		case Select::SCITIZENS://SHOW All Citizens
			std::cout << E->getVoterbook();
			break;

		case Select::SPARTIES://SHOW All Parties
			std::cout << E->getPartyArray();
			break;

		case Select::AVOTE://Voting
			try
			{
				AddVote();
			}
			catch (const Generalexcep& ex)
			{
				std::cout << "Error: " << ex.what() << std::endl;;
			}
			catch (const std::invalid_argument& ex) {
				std::cout << "Error: " << ex.what() << std::endl;;
			}
			break;

		case Select::RESULTS://SHOW Election Results
			try
			{
				ShowResults();
			}
			catch (const std::bad_alloc& e) {
				std::cout << "Allocation failed: " << e.what() << std::endl;
				throw;
			}
			catch (const std::out_of_range& e) {
				std::cout << "Out of range error: " << e.what() << std::endl;
			}
			break;

		case Select::EXIT:
			flag = false;
			break;//Exit
		default:
			std::cout << "Wrong choice , please select number from the menu" << std::endl;
			break;

		case Select::SAVE: {
			std::cout << "Enter file name to save" << std::endl;
			STRING Fname;
			std::cin.ignore();
			Fname.getStrInput();
			try
			{
			Save(Fname, *E,2);
			}
			catch (const std::ios_base::failure& e)
			{
				std::cout << "Error with file: " << e.what() << std::endl;
			}
			break;
		}
		case Select::LOAD: {
			std::cin.ignore();
			flag = true;
			userchoice = 10;
			break;
		}
		}
	}

}

void SimpleMenu::ShowResults() {
	printWinner();
}
void SimpleMenu::AddElector() {
	std::cout << "Enter elector id:" << std::endl;
	int elecId;
	std::cin >> elecId;
	const Citizen* cit = E->getVoterbook().get(elecId);
	if (cit == nullptr)
		throw Generalexcep("Citizen Not Found");

	std::cout << "Enter party id:" << std::endl;
	size_t partyid;
	std::cin >> partyid;
	if (partyid > E->getPartyArray().getNumofParties())
		throw Generalexcep("Party id is invalid");

	PartyID partyID(partyid);

	CCprt(CCprtarr(E->getPartyArray())[partyID]).setElectArrSize(E->getDistrictArray().getNumofDistricts());
	CCprt(CCprtarr(E->getPartyArray())[partyID]).insertElect(cit, E->getDistrictArray().getDistrictIDX(cit->getDistrict()));
	std::cout << "Elector Added" << std::endl;
	
}

void SimpleMenu::AddDistrict() {
	std::cout << "THIS IS A SIMPLE ELECTION ROUND. NO DISTRICT SPECIFICATION NEEDED!" << std::endl;
}

void SimpleMenu::AddCitizen() {
	if (E->getDistrictArray().getNumofDistricts() == 0) {
		throw Generalexcep("You Must add district before citizens");
	}
	else {
		std::cout << "Enter the name of Citizen :" << std::endl;
		std::cin.ignore();
		STRING name;
		name.getStrInput();

		std::cout << "Enter the ID of Citizen :" << std::endl;
		size_t ID;
		std::cin >> ID;
		if (!IDCheck(ID))
			throw Generalexcep("The id of citizen not include enough digits");

		CitizenID citid(ID);

		std::cout << "Enter the BirthYear of Citizen :" << std::endl;
		size_t year;
		std::cin >> year;
		if (!isValidDate(year))
			throw Generalexcep("The citizen is not in valid age");


		Date d(year);

		std::cout << "Enter the number of District :" << std::endl;
		size_t districtNum;
		std::cin >> districtNum;
		DistrictID stID = E->getDistrictArray()[0]->getSN();
		District* st{};
		if (!(E->getDistrictArray().getDistrictIDX(stID) < E->getDistrictArray().getNumofDistricts())) {
			throw Generalexcep("ERROR: There is no district with this id, choose another district");
		}
		st = const_cast<District*>(const_cast<DistrictsArray&>(E->getDistrictArray())[stID]);

		Citizen* newcit = new Citizen(name, citid, d, st);
		const_cast<Voterbook&>(E->getVoterbook()).insertCitizen(newcit);
		const_cast<District&>(newcit->getDistrict()).setNumOfEligibleCitizens(true);
		std::cout << "Citizen Added" << std::endl;
	
	}
}

void SimpleMenu::printWinner() {
	Polls& polls = const_cast<Polls&>(E->getPolls());
	DynamicArray<int> finalElectorsRes(E->getPartyArray().getNumofParties());//save how many electors get each candidate,index 0 =electors of candidate of party 1 and etc...
	for (int i = 0; i < E->getPartyArray().getNumofParties(); i++) {
		finalElectorsRes.push_back(0);
	}
	std::cout << "---####--------------  State Winner is ---------------####---" << std::endl;
	std::cout << "------------------------------------------------------------- " << std::endl;
	std::cout << "Election " << E->getDate() << std::endl;
	std::cout << "------------------------------------------------------------- " << std::endl;

	for (size_t i = 0; i < E->getDistrictArray().getNumofDistricts(); i++) {
		DynamicArray<size_t> array = polls.selectionSort(polls[i], CCprtarr(E->getPartyArray()), E->getPartyArray().getNumofParties());//return sorted array with index of party in this district that get the most votes Descending
		District* district = const_cast<District*>(E->getDistrictArray()[i]);
		DynamicArray<size_t> electorsDistributeArr = polls.electorsDistribute(polls[i], (static_cast<float>((*district).getVotedCit()) / static_cast<float>(district->getNumOfElectors())), district->getNumOfElectors(), E->getPartyArray().getNumofParties());
		DividedDistrict* DS = dynamic_cast<DividedDistrict*>(district);
		addElectorsToFinalResults(finalElectorsRes, electorsDistributeArr, E->getPartyArray().getNumofParties());

		printDDistrictDetails(DS, CCprtarr(E->getPartyArray()), array, electorsDistributeArr);
		printPartyResults(district, CCprtarr(E->getPartyArray()), polls, electorsDistributeArr);
		std::cout << "################################ " << std::endl;
		std::cout << "################################ " << std::endl;
		std::cout << std::endl;
	}

	printCandidateResults(finalElectorsRes, polls);
}

void SimpleMenu::printDDistrictDetails(DividedDistrict* district, PartyArray& partyarray, DynamicArray<size_t>& array, DynamicArray<size_t>& electorsDistributeArr) {
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




