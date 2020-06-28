#include "Repository.h"
#include <fstream>
#include <algorithm>

void Repository::loadAFromFile()
{
	ifstream fin(aFile);
	Astronomer w;
	while (fin >> w)
		this->astron.push_back(w);
	fin.close();
}

void Repository::loadSFromFile()
{
	ifstream fin(sFile);
	Star i;
	while (fin >> i)
		this->stars.push_back(i);
	fin.close();
	//auto sortFct = [](const Star& i1, const Star& i2) {return i1.getAct() < i2.getAct(); };
	//sort(ideas.begin(), ideas.end(), sortFct);
}

void Repository::addStar(Star& i)
{
	auto it = find(stars.begin(), stars.end(), i);
	if (it != stars.end())
		throw exception("There already is a star like this!");
	stars.push_back(i);
	//
}

void Repository::updateIdeaStatus(Star& i, const string& status)
{
	//auto it = find(ideas.begin(), ideas.end(), i);
	//it->setStatus(status);
}

void Repository::addWriter(Astronomer& w)
{
	//auto it = find(writers.begin(), writers.end(), w);
	//if (it != writers.end())
	//	throw exception("There already is a writer with this name!");
	//writers.push_back(w);
}

