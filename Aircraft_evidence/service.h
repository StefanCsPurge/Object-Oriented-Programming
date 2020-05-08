#pragma once
#include "repository.h"
using namespace std;

class Service
{
private:
	Repository& repo;
public:
	Service(Repository& r) : repo(r) {}
	void addHelicopterToRepo(int ID, string& model, string& suitable, int maxAlt, bool priv);
	void addPlaneToRepo(int ID, string& model, string& suitable, int maxAlt, bool priv, string& mainWings);
	void addBalloonToRepo(int ID, string& model, int maxAlt, int weightLim);
	vector<Aircraft*> getActivityAircraft(const string& activity);
	vector<Aircraft*> getAltitudeAircraft(int altitude);
};