#include "BaseMenu.h"

void BaseMenu::MainMenu(bool& flag) {
	int userchoice = 0;

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
			catch (const Generalexcep & e) {
				std::cout << "Error: " << e.what() << std::endl;
			}
			catch (const std::bad_alloc & e) {
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
			try
			{
				AddCitizen();
			}
			catch (const Generalexcep & ex)
			{
				std::cout << "Error: " << ex.what() << std::endl;;
			}
			catch (const std::bad_alloc & e) {
				std::cout << "Allocation failed: " << e.what() << std::endl;
				throw;
			}
			catch (const std::out_of_range e) {
				std::cout << e.what() << std::endl;
			}
			break;

		case Select::APARTY://ADD Party
			try
			{
				AddParty();
			}
			catch (const Generalexcep & ex)
			{
				std::cout << "Error: " << ex.what() << std::endl;;
			}
			catch (const std::bad_alloc & e) {
				std::cout << "Allocation failed: " << e.what() << std::endl;
				throw;
			}
			catch (const std::out_of_range & e) {
				std::cout << "Out of range error: " << e.what() << std::endl;
			}
			break;

		case Select::AELECTOR://ADD Citizen as Elector
			try
			{
				AddElector();
			}
			catch (const Generalexcep & ex)
			{
				std::cout << "Error: " << ex.what() << std::endl;;
			}
			catch (const std::bad_alloc & e) {
				std::cout << "Allocation failed: " << e.what() << std::endl;
				throw;
			}
			catch (const std::invalid_argument & e) {
				std::cout << e.what() << std::endl;
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
			catch (const Generalexcep & ex)
			{
				std::cout << "Error: " << ex.what() << std::endl;;
			}
			break;

		case Select::RESULTS://SHOW Election Results
			try
			{
				ShowResults();
			}
			catch (const std::bad_alloc & e) {
				std::cout << "Allocation failed: " << e.what() << std::endl;
				throw;
			}
			catch (const std::out_of_range & e) {
				std::cout << "Out of range error: " << e.what() << std::endl;
			}
			break;

		case Select::EXIT:
			flag = false;
			break;//Exit

		case Select::SAVE: {
			std::cout << "Enter file name to save" << std::endl;
			STRING Fname;
			std::cin.ignore();
			Fname.getStrInput();
			try
			{
				Save(Fname, *E, 1);
			}
			catch (const std::ios_base::failure & e)
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
		default:
			std::cout << "Wrong choice , please select number from the menu" << std::endl;
			break;
		}
	}

}

void BaseMenu::printCandidateResults(DynamicArray<int> finalElectorsRes, Polls& _polls) {

	std::cout << std::endl;
	std::cout << "!!!_____Final Results_____!!!" << std::endl;

	for (int i = 0; i < E->getPartyArray().getNumofParties(); i++) {
		size_t temp = _polls.findMax(finalElectorsRes, E->getPartyArray().getNumofParties());
		STRING candidateName = E->getPartyArray()[temp].getCandidate()->getName();
		size_t totalVotes = _polls.totalVotesByParty(temp);
		std::cout << "Candidate: " << candidateName.getString() << "--- Total Votes: " << totalVotes << "--- Total Electors: " << finalElectorsRes[temp] << std::endl;
		finalElectorsRes[temp] = -1;
	}
}

void BaseMenu::addElectorsToFinalResults(DynamicArray<int>& finalElectorsRes, DynamicArray<size_t>& electorsDistributeArr, size_t NumofParties) {
	for (int i = 0; i < NumofParties; i++) {
		finalElectorsRes[i] += electorsDistributeArr[i];
	}
}


void BaseMenu::printMenu() {
	std::cout << "  Choose an option" << std::endl;
	std::cout << "--- --- --- --- ---" << std::endl;
	std::cout << "1. Add District" << std::endl;
	std::cout << "2. Add Citizen" << std::endl;
	std::cout << "3. Add Party" << std::endl;
	std::cout << "4. Add Elector" << std::endl;
	std::cout << "5. Show All Districts" << std::endl;
	std::cout << "6. Show All Citizens" << std::endl;
	std::cout << "7. Show All Parties" << std::endl;
	std::cout << "8. Voting" << std::endl;
	std::cout << "9. Show Election Results" << std::endl;
	std::cout << "10. Exit" << std::endl;
	std::cout << "11. Save the election to file" << std::endl;
	std::cout << "12. Load election from file" << std::endl;

}

void BaseMenu::AddVote() {
	size_t citId;
	std::cout << "Enter Citizen ID" << std::endl;
	std::cin.ignore();
	std::cin >> citId;
	Citizen* cit = const_cast<Citizen*>(E->getVoterbook().get(citId));
	if (!cit)
		throw Generalexcep("Citizen not found");

	if (cit->getCitVoted())//check if the citizen already vote
		throw Generalexcep("The Citizen already voted!");

	size_t pId;
	std::cout << "Enter Party ID" << std::endl;
	std::cin >> pId;
	PartyID partyID = pId;
	if (pId > E->getPartyArray().getNumofParties())
		throw Generalexcep("There is no party with this Id!");

	const_cast<Polls&>(E->getPolls()).voteToParty(E->getPartyArray().getPrtIDX(partyID), E->getDistrictArray().getDistrictIDX(cit->getDistrict().getSN()));
	const_cast<District&>(cit->getDistrict()).setVotedCit(true);
	cit->setCitVoted(true);
	std::cout << "The Vote Added" << std::endl;

}

void BaseMenu::AddCitizen() {
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
		DistrictID stID = districtNum;
		District* st{};
		if (!(E->getDistrictArray().getDistrictIDX(stID) < E->getDistrictArray().getNumofDistricts())) {
			throw std::out_of_range("ERROR: There is no district with this id, choose another district");
		}
		st = const_cast<District*>(const_cast<DistrictsArray&>(E->getDistrictArray())[stID]);

		Citizen* newcit = new Citizen(name, citid, d, st);
		const_cast<Voterbook&>(E->getVoterbook()).insertCitizen(newcit);
		const_cast<District&>(newcit->getDistrict()).setNumOfEligibleCitizens(true);
		std::cout << "Citizen Added" << std::endl;

	}
}

void BaseMenu::AddElector() {
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

	std::cout << "Enter district id:" << std::endl;
	size_t districtid;
	std::cin >> districtid;
	if (districtid > E->getDistrictArray().getArr().size())
		throw Generalexcep("district id is invalid");

	DistrictID dID(districtid);

	CCprt(CCprtarr(E->getPartyArray())[partyID]).setElectArrSize(E->getDistrictArray().getNumofDistricts());
	CCprt(CCprtarr(E->getPartyArray())[partyID]).insertElect(cit, E->getDistrictArray().getDistrictIDX(dID));
	std::cout << "Elector Added" << std::endl;

}

void BaseMenu::AddParty() {
	if (E->getDistrictArray().getNumofDistricts() == 0) {
		throw Generalexcep("You Must add district before citizens");
	}
	else {
		std::cout << "Enter the name of Party" << std::endl;
		std::cin.ignore();
		STRING name;
		name.getStrInput();

		int canId;
		std::cout << "Enter Candidate Id" << std::endl;
		std::cin >> canId;
		const Citizen* cit = E->getVoterbook().get(canId);
		if (cit == nullptr) {
			throw Generalexcep("Citizen Not Found");
		}

		CCprtarr(E->getPartyArray()).addParty(name, cit);
		const_cast<Polls&>(E->getPolls()).updateNumOfParties(E->getPartyArray().getNumofParties());//party addition
		std::cout << "Party Added" << std::endl;

		size_t numOfParties = E->getPartyArray().getNumofParties();
		for (size_t i = 0; i < numOfParties; ++i) {
			CCprt(E->getPartyArray()[i]).setElectArrSize(E->getDistrictArray().getNumofDistricts());
		}
	}
}


void BaseMenu::printElectors(Party& p, size_t districtindex, size_t& numofelectors)
{

	if (const_cast<ElectorsList&>(p.getElecList(districtindex)).getlist().empty()) {

		std::cout << "The Party has no electores in the current district " << std::endl;
		std::cout << "--------------------------" << std::endl;
	}
	else
		for (Elector el : const_cast<ElectorsList&>(p.getElecList(districtindex)).getlist())
			std::cout << el;


}

void BaseMenu::printPartyResults(District* district, PartyArray& partyarray, Polls& _polls, DynamicArray<size_t>& electorsDistributeArr) {

	for (int j = 0; j < partyarray.getNumofParties(); j++) {
		size_t numOfVotes = _polls[(district->getSN().getDistrictID()) - 1][j];
		size_t partyvotingpercent = 0;
		if (district->getVotedCit() != 0) {
			partyvotingpercent = (static_cast<float>(numOfVotes) / static_cast<float>(district->getVotedCit())) * 100;
		}
		else {
			std::cout << "There are no votes in this district" << std::endl;
		}

		STRING partyname = partyarray[j].getPrtName();
		std::cout << "Party name: " << partyname.getString() << "--- Votes in this district: " << numOfVotes << "--- Electors in this district: " << electorsDistributeArr[j] << "--- Percentage of votes: " << partyvotingpercent << "%" << std::endl;
		std::cout << "Electors elected in this district: " << std::endl;
		printElectors(const_cast<Party&>(partyarray[j]), E->getDistrictArray().getDistrictIDX(district->getSN().getDistrictID()), electorsDistributeArr[j]);
		std::cout << "--------------------------------------" << std::endl;
	}

}

bool BaseMenu::IDCheck(size_t id)
{
	int count = 0;
	while (id != 0) {
		id /= 10;
		count++;
	}

	return count == 9 ? true : false;
}


