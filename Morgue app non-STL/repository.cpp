#include "repository.h"


int Repository::getVictimPosition(const string name)
{
	for (int i = 0; i < this->victims.getSize(); i++)
		if (victims[i].getName() == name)
			return i;
	return -1;
}

void Repository::addVictim(const Victim& v)
{
	this->victims.add(v);
}

void Repository::updateVictim(const Victim& newVictim)
{
	int position = getVictimPosition(newVictim.getName());
	this->victims[position] = newVictim;
}

void Repository::deleteVictim(const string& name)
{
	int position = getVictimPosition(name);
	this->victims.deletePosition(position);
}

Victim Repository::getNextVictim()
{
	if (this->it == this->victims.end() || this->it == NULL)
		this->it = victims.begin();
	Victim v = *it;
	it++;
	return v;
}

void Repository::assistantTransferVictim(const Victim v)
{
	this->assistantVictims.add(v);
	this->deleteVictim(v.getName());
	this->it--;
}