#include "repository.h"
#include <exception>

void Repository::addAicraft(Aircraft* a)
{
	if (findByID(a->getID()))
		throw exception("This ID already exists!");
	aircrafts.push_back(a);
}

bool Repository::findByID(int ID)
{
	for (auto a : this->aircrafts)
		if (a->getID() == ID)
			return true;
	return false;
}

Repository::~Repository()
{
	for (auto a : aircrafts)
		delete a;
}