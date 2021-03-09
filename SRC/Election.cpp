#include "Election.h"


Election::Election(Date & elecDate):date(new Date(elecDate)),districts(new DistrictsArray()),voterbook(new Voterbook()),
partyarray(new PartyArray()),polls(new Polls())
{
}

Election::~Election() {
	delete(date);
	delete(districts);
	delete(voterbook);
	delete(partyarray);
	delete(polls);
}

void Election::save(std::ostream & out) const
{
	date->save(out);
	districts->save(out);
	voterbook->save(out);
	partyarray->save(out);
	polls->save(out);
}



void Election::resetElections() {
	delete(date); date = new Date();
	delete(partyarray); partyarray = new PartyArray();
	delete(districts); districts = new DistrictsArray();
	delete(voterbook); voterbook = new Voterbook();
	delete(polls); polls = new Polls();

}

void Election::load(std::istream& _in, bool _existelection) {
	if (_existelection) {
		resetElections();
	}
	date->load(_in);
	
	districts->load(_in);

	voterbook->load(_in,*districts);

	partyarray->load(_in, *voterbook);

	polls->load(_in);

}