#pragma once
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

class Victim
{
private:
	string name;
	string placeOfOrigin;
	string photo;
	int age;

public:
	// default constructor
	Victim() : name(""), placeOfOrigin(""), age(-1), photo("") {}
	// constructor
	Victim(const string& name, const string& placeOfOrigin, const int& age, const string& photo);

	string getName() const { return name; }
	string getPlaceOfOrigin() const { return placeOfOrigin; }
	string getPhoto() const { return photo; }
	int getAge() const { return age; }

	bool operator==(const Victim& v) { return this->name == v.name; }
	bool operator!=(const Victim& v) { return this->name != v.name; }

	friend ostream& operator<<(ostream& out, const Victim& c);
	friend istream& operator>>(istream& in, Victim& c);

	// returns a string with the Victim's data
	string toString();
	string getHTMLString() const;
};