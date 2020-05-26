#include "controller.h"
#include <qdebug.h>

Person Service::getEnt(string name)
{
	auto e = find(ents.begin(), ents.end(), Person(name));
	if (e == ents.end())
		throw exception("No ent!");
	return *e;
}

/*
Function that filters the persons by category or name
Input: string (name or category)
Output: vector<Person> containing the selected persons
(the test is called in main)
*/
vector<Person> Service::filter(const string& namecat)
{
	vector<Person> newEnts;
	auto goodE = [&](Person& e)->bool {return e.getName().find(namecat)!=std::string::npos || e.getBody().find(namecat) != std::string::npos; };
	copy_if(ents.begin(), ents.end(), back_inserter(newEnts), goodE);
	return newEnts;
}


void Service::loadEntsFromFile()
{
	Person e;
	ifstream fin(file);
	while (fin >> e)
		if (e.getName() != "")
			this->ents.push_back(e);
	fin.close();
}

//void Service::writeEntsToFile()
//{
//	ofstream fout(file);
//	for_each(ents.begin(), ents.end(), [&](Entity& e) {fout << e.getID()<<','<<e.getName() << endl; });
//}


