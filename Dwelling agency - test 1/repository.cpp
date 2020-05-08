#include "repository.h"
#include <exception>

void Repository::addC(Client* a)
{
	//if (findByID(a->getID()))
		//throw exception("This ID already exists!");
	cls.push_back(a);
}

void Repository::addD(Dwelling& a)
{
	//if (findByID(a->getID()))
		//throw exception("This ID already exists!");
	dws.push_back(a);
}

/*
bool Repository::findByID(int ID)
{
	for (auto a : this->ents)
		if (a->getID() == ID)
			return true;
	return false;
}*/

Repository::~Repository()
{
	for (auto a : cls)
		delete a;
}