#include "repository.h"
#include <algorithm>
#include <Windows.h>

void Repository::setVictimsFile(const string& filePath)
{
	ifstream fin(filePath);
	bool ok = 0;
	if (fin.good())
	{
		this->victimsFile = filePath;
		fin.close();
	}
	else {
		ofstream f(filePath);
		if (f.fail()){
			this->victimsFile = "repository/victims.txt";
			ifstream fin(victimsFile);
			if (fin.fail()){ ofstream f(victimsFile); f.close(); } 
			fin.close();
			throw RepositoryException("File couldn't be created at the provided location. Default file 'victims.txt' was set."); }
		this->victimsFile = filePath;
		f.close();
	}
	//filePath = filePath.substr(0, filePath.find_last_of('\\')+1) + "newDataFile.txt";    studiu de caz :)
}

vector<Victim> Repository::loadVictimsFromFile()
{
	if (victimsFile == "")
		throw RepositoryException("No repository file given!");
	vector<Victim> victims;
	Victim victim;
	ifstream fin(this->victimsFile);
	while (fin >> victim)
		if(victim.getName() != "")
			victims.push_back(victim);
	fin.close();
	return victims;
}

void Repository::writeVictimsToFile(vector<Victim> victims)
{
	if (victimsFile == "") throw RepositoryException("No repository file given!");
	ofstream fout(this->victimsFile);
	for (const Victim& victim : victims)
		fout << victim;
	fout.close();
}

Victim Repository::getVictim(const string& name)
{
	Victim v(name,"",0,"");
	auto victims = loadVictimsFromFile();
	auto it = find(victims.begin(), victims.end(), v);
	if (it == victims.end())
		throw RepositoryException("There is no victim with this name!");
	return *it;
}

void Repository::addVictim(const Victim& v)
{
	auto victims = loadVictimsFromFile();
	auto it = find(victims.begin(), victims.end(), v);
	if (it != victims.end())
		throw RepositoryException("There already exists a victim with this name!");
	victims.push_back(v);
	writeVictimsToFile(victims);
}

void Repository::updateVictim(const Victim& newVictim)
{
	auto victims = loadVictimsFromFile();
	auto it = find(victims.begin(), victims.end(), newVictim);
	if (it == victims.end())
		throw RepositoryException("There is no victim with this name!");
	*it = newVictim;
	writeVictimsToFile(victims);
}

void Repository::deleteVictim(const Victim& v)
{
	auto victims = loadVictimsFromFile();
	auto it = find(victims.begin(), victims.end(), v);
	if (it == victims.end())
		throw RepositoryException("There is no victim with this name!");
	victims.erase(it);
	if (this->iterPos > 0)
		this->iterPos--;
	writeVictimsToFile(victims);
}

Victim Repository::getNextVictim()
{
	auto victims = loadVictimsFromFile();
	if (!victims.size())
		throw RepositoryException("There are no victims!");
	if (this->iterPos == victims.size())
		this->iterPos = 0;
	Victim v = victims[iterPos];
	this->iterPos++;
	return v;
}


/// ASSISTANT repository

AssistantRepository::AssistantRepository(string filePath)
{
	ofstream fin(filePath);
	if (fin.fail())
		filePath = "repository/selectedVictims.txt";
	fin.close();
	this->file = filePath;
	ofstream fout(this->file);
	fout.close();
}

void AssistantRepository::writeVictimsToFile() const
{
	ofstream fout(file);
	for_each(assistantVictims.begin(), assistantVictims.end(), [&](const Victim& v) {fout << v; });
	fout.close();
}

void AssistantRepository::addVictim(const Victim& v)
{
	this->assistantVictims.push_back(v);
	fstream fout;
	fout.open(file, ios::app); // append instead of overwrite
	fout << v;
}

void AssistantRepository::openInApplication()
{
	string path = "\"" + this->file + "\"";
	/// Windows specific
	ShellExecuteA(NULL, NULL, "C:/Windows/system32/notepad.exe", path.c_str(), NULL, SW_SHOWMAXIMIZED);
}