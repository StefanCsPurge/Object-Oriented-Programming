#pragma once
#include <vector>
#include <algorithm>
#include <fstream>
#include <exception>
#include "domain.h"

class Service
{
private:
	vector<Person> ents;
	string file;

public:
	Service(const string& f) : file(f) { loadEntsFromFile(); }

	Person getEnt(string name);

	vector<Person> getAll() { return ents; }

	// Returns filtered by name sorted by ID
	vector<Person> filter(const string& name);

	void loadEntsFromFile();

	//void writeEntsToFile();
};