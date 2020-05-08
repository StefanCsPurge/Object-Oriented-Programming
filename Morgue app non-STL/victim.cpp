/// The VICTIM implementation
#include "victim.h"



Victim::Victim(const string& name, const string& placeOfOrigin, const int& age, const string& photo)
{
	this->name = name;
	this->placeOfOrigin = placeOfOrigin;
	this->age = age;
	this->photo = photo;
}

string Victim::toString()
{
	return "NAME: " + this->name + " - " +"PLACE OF ORIGIN: " + this->placeOfOrigin + " - "+ "AGE: " + to_string(this->age) + " - " + "PHOTO: " + this->photo;
}