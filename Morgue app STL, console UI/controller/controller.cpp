#include "controller.h"


void Service::setFile(const string& filePath)
{
	this->repo->setVictimsFile(filePath);
}

void Service::createMylistRepo(const string& filePath, const string& extension)
{
	if (extension == "txt")
		assistantRepo = new AssistantRepository(filePath);
	else if (extension == "csv")
		assistantRepo = new CSVassistantRepo(filePath);
	else if (extension == "html")
		assistantRepo = new HTMLassistantRepo(filePath);
	else throw exception("Invalid mylist file extension!\n");
}

vector<Victim> Service::getAllVictims() const
{
	return this->repo->getVictims();
}

void Service::addVictimToRepo(const string& name, const string& placeOfOrigin, int age, const string& photo)
{
	Victim v{ name,placeOfOrigin,age,photo };
	VictimValidator::validateVictim(v);
	this->repo->addVictim(v);
}

void Service::updateVictim(const string& name, const string& newPlaceOfOrigin, int newAge, const string& newPhoto)
{
	Victim newV{ name,newPlaceOfOrigin,newAge,newPhoto };
	VictimValidator::validateVictim(newV);
	this->repo->updateVictim(newV);
}

void Service::deleteVictim(const string& name)
{
	Victim v(name,"dummyPlace",0,"dummyPhoto.png");
	VictimValidator::validateVictim(v);
	this->repo->deleteVictim(v);
}

void Service::nextVictim()
{
	this->currentVictim = this->repo->getNextVictim();
}

Victim Service::getCurrentVictim()
{
	return this->currentVictim;
}

void Service::moveVictimToAssistantList(const string& name)
{
	/// Transfers a victim to the assistant's list
	Victim v = repo->getVictim(name);
	assistantRepo->addVictim(v); 
	this->repo->deleteVictim(v);
}

void Service::showAssistantVictims() const
{
	this->assistantRepo->openInApplication();
}

vector<Victim> Service::filterVictims(const string& orig, int age) const
{
	vector<Victim> newV, victims = getAllVictims();
	auto goodVictim = [&](const Victim& v) {return v.getAge() < age && (orig.size() && v.getPlaceOfOrigin() == orig || !orig.size()); };
	copy_if(victims.begin(), victims.end(), back_inserter(newV), goodVictim);
	return newV;
}

void Service::addEntries()
{
	try {
		addVictimToRepo("Danutz Ilie", "Brasov", 19, "deadNakedDanutz.jpeg");
		addVictimToRepo("Trumpy Boi", "USA", 60, "deadEagle.jpeg");
		addVictimToRepo("YOLO Lover", "Tanzania", 18, "epicParachuteFail.jpeg");
		addVictimToRepo("Hatz Johnule", "Bucales", 27, "tooHeavyLifting.png");
		addVictimToRepo("Gucci Gang", "Italy", 69, "valueOverload.png");
		addVictimToRepo("Costel Biju", "Japan", 19, "hangedEmo.jpeg");
		addVictimToRepo("Edward Snowden", "Russia", 35, "NSA&CIAgotPissed.jpeg");
		addVictimToRepo("Chuck Norris", "Everywhere", 420, "missingBody.wtf");
		addVictimToRepo("Anatoly Boris", "Ukraine", 33, "ChernobySurprise.jpeg");
		addVictimToRepo("Giovanni Ferrari", "Italy", 44, "coronaVirusHadFun.jpeg");
	}
	catch(exception&){ return; }
}