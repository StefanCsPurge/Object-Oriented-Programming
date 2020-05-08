#pragma once
#include "aircraft.h"
#include <vector>
#include <memory>
using namespace std;

class Repository
{
private:
	vector<Aircraft*> aircrafts;

public:
	vector<Aircraft*> getAll() { return aircrafts; }
	void addAicraft(Aircraft*);
	bool findByID(int ID);
	~Repository();
};