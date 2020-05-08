#pragma once
#include "domain.h"
#include <vector>
#include <memory>
using namespace std;

class Repository
{
private:
	vector<Client*> cls;
	vector<Dwelling> dws;

public:
	vector<Client*> getAllCl() { return cls; }
	vector<Dwelling> getAllDw() { return dws; }
	void addC(Client*);
	void addD(Dwelling&);
	//bool findByID(int ID);
	~Repository();
};