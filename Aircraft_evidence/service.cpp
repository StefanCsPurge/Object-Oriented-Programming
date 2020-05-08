#include "service.h"
#include <algorithm>
#include <fstream>
using namespace std;

void Service::addHelicopterToRepo(int ID, string& model, string& suitable, int maxAlt, bool priv) {
	if (maxAlt > 12)
		throw exception("Max altitude for a helicopter is 12 km!");
	if (!priv && suitable == "leisure time")
		throw exception("Suitable for leisure time only if private!");
	Aircraft* a = new Helicopter{ ID,model,suitable,maxAlt,priv };
	repo.addAicraft(a);
}

void Service::addPlaneToRepo(int ID, string& model, string& suitable, int maxAlt, bool priv, string& mainWings){
	if (maxAlt > 26)
		throw exception("Max altitude for a plane is 26 km!");
	if (mainWings!="biplane" && suitable == "leisure time")
		throw exception("Suitable for leisure time only if it's a biplane!");
	Aircraft* a = new Plane{ ID,model,suitable,maxAlt,priv,mainWings };
	repo.addAicraft(a);
}

void Service::addBalloonToRepo(int ID, string& model, int maxAlt, int weightLim){
	if (maxAlt > 21)
		throw exception("Max altitude for a hot air balloon is 21 km!");
	Aircraft* a = new HotAirBalloon{ ID,model,maxAlt,weightLim };
	repo.addAicraft(a);
}
vector<Aircraft*> Service::getActivityAircraft(const string& activity){
	vector<Aircraft*> newAirc, airc = repo.getAll();

	auto goodAircraft = [&](auto a) {return a->getActivity() == activity; };
	copy_if(airc.begin(), airc.end(), back_inserter(newAirc), goodAircraft);

	const string file = activity + ".txt";
	ofstream fout(file);
	for_each(newAirc.begin(), newAirc.end(), [&](auto a) {fout << a->getString(); });
	return newAirc;
}
vector<Aircraft*> Service::getAltitudeAircraft(int altitude){
	vector<Aircraft*> newAirc, airc = repo.getAll();

	auto goodAircraft = [&](auto a) {return a->getMaxAlt() >= altitude; };
	copy_if(airc.begin(), airc.end(), back_inserter(newAirc), goodAircraft);

	return newAirc;
}