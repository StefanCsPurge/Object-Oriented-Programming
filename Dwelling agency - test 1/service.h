#pragma once
#include "repository.h"
using namespace std;

class Service
{
private:
	Repository& repo;
public:
	Service(Repository& r) : repo(r) {}
	void addNCl(string& name, double sal);
	void addWCl(string& name, double sal, double inv);
	void addDw(string& type, double pr, bool profit);
	vector<Client*> getAllClients() { return repo.getAllCl(); }
	vector<Dwelling> getAllDw() { return repo.getAllDw(); }
	vector<Client*> getAllDwType(string& type);
	void saveClToFile(string& file);
};