#include "controller.h"

DynamicVector<Victim> Service::getAllVictims() const
{
	return this->repo.getVictims();
}


int Service::addVictimToRepo(const string& name, const string& placeOfOrigin, int age, const string& photo)
{
	if (repo.getVictimPosition(name)!=-1)
		return 0;
	Victim v{ name,placeOfOrigin,age,photo };
	this->repo.addVictim(v);
	return 1;
}

int Service::updateVictim(const string& name, const string& newPlaceOfOrigin, int newAge, const string& newPhoto)
{
	if (repo.getVictimPosition(name)==-1)
		return 0;
	Victim newV{ name,newPlaceOfOrigin,newAge,newPhoto };
	this->repo.updateVictim(newV);
	return 1;
}

int Service::deleteVictim(const string& name)
{
	if (repo.getVictimPosition(name)==-1)
		return 0;
	this->repo.deleteVictim(name);
	return 1;
}

void Service::nextVictim()
{
	this->currentVictim = this->repo.getNextVictim();
}

Victim Service::getCurrentVictim()
{
	return this->currentVictim;
}

int Service::moveVictimToAssistantList(const string& name)
{
	int position = repo.getVictimPosition(name);
	if (position == -1)
		return 0;
	this->repo.assistantTransferVictim(this->getAllVictims()[position]);
	return 1;
}

DynamicVector<Victim> Service::getAssistantVictims() const
{
	return this->repo.getAssistantVictims();
}

DynamicVector<Victim> Service::filterVictims(const string& orig, int age) const
{
	DynamicVector<Victim> newV, victims = getAllVictims();
	for (int i = 0; i < victims.getSize(); i++)
	{
		Victim v = victims[i];
		if (v.getAge() < age && (orig.size() && v.getPlaceOfOrigin() == orig || !orig.size()))
			newV.add(v);
	}
	return newV;
}

void Service::addEntries()
{
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