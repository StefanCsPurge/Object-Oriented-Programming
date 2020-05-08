#include "aircraft.h"
#include <iostream>

Helicopter::Helicopter(int ID, const string& model, const string& suitable, int maxAlt, bool isPriv)
{
	this->ID = ID;
	this->model = model;
	this->suitable = suitable;
	this->isPrivate = isPriv;
	this->maxAlt = maxAlt;
}

istream& operator>>(istream& is, Helicopter& h)
{
	cout << "ID: ";
	is >> h.ID;
	cout << "Model: ";
	is >> h.model;
	cout << "Suitable for: ";
	getline(is, h.suitable);
	is.ignore();
	cout << "Max altitude: ";
	is >> h.maxAlt;
	cout << "Private? [y/n] ";
	string priv;
	is >> priv;
	if (priv == "y")
		h.isPrivate = true;
	else h.isPrivate = false;
	return is;
}

ostream& operator<<(ostream& os, const Helicopter& h)
{
	os << "Helicopter:\n";
	os <<"ID: "<< h.ID << " - " <<"Model: "<< h.model << " - " <<"Suitable for: "<< h.suitable <<" - "<<"Max altitude: "<< h.maxAlt << " - " <<"Private: "<< h.isPrivate <<"\n";
	return os;
}

string Helicopter::getString() const 
{
	return "Helicopter: ID: " + to_string(ID) + " - " + "Model: " + model + " - " + "Suitable for: " + suitable + " - " + "Max altitude: " + to_string(maxAlt) + " - " + "Private: " + to_string(isPrivate) + "\n";
}

Plane::Plane(int ID, const string& model, const string& suitable, int maxAlt, bool isPriv, const string& mainWings)
{
	this->ID = ID;
	this->model = model;
	this->suitable = suitable;
	this->isPrivate = isPriv;
	this->maxAlt = maxAlt;
	this->mainWings = mainWings;
}

ostream& operator<<(ostream& os, const Plane& h)
{
	os << "Plane:\n";
	os << "ID: " << h.ID << " - " << "Model: " << h.model << " - " << "Suitable for: " << h.suitable << " - " << "Max altitude: " << h.maxAlt << " - " << "Private: " << h.isPrivate << " - "<<"Main wings: "<<h.mainWings<<"\n";
	return os;
}

string Plane::getString() const
{
	return "Plane: ID: " + to_string(ID) + " - " + "Model: " + model + " - " + "Suitable for: " + suitable + " - " + "Max altitude: " + to_string(maxAlt) + " - " + "Private: " + to_string(isPrivate) + " - " + "Main wings: " + mainWings + "\n";
}

HotAirBalloon::HotAirBalloon(int ID, const string& model, int maxAlt, int weightLim)
{
	this->ID = ID;
	this->model = model;
	this->suitable = "leisure time";
	this->maxAlt = maxAlt;
	this->weightLimit = weightLim;
}

ostream& operator<<(ostream& os, const HotAirBalloon& h)
{
	os << "Hot air balloon:\n";
	os << "ID: " << h.ID << " - " << "Model: " << h.model << " - " << "Suitable for: " << h.suitable << " - " << "Max altitude: " << h.maxAlt << " - " << "Weight limit: " << h.weightLimit<< "\n";
	return os;
}

string HotAirBalloon::getString() const
{
	return "Hot air balloon: ID: " + to_string(ID) + " - " + "Model: " + model + " - " + "Suitable for: " + suitable + " - " + "Max altitude: " + to_string(maxAlt) + " - " + "Weight limit: " + to_string(weightLimit) + "\n";
}