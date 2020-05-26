#pragma once
#include <string>
#include <sstream>
#include <vector>
using namespace std;

class Person
{
protected:
	string name;
	string body;
	string traits;
public:
	Person(string name = "", string body = "",string traits = "") : name(name), body(body) , traits(traits){}
	string getName() const { return name; }
	string getBody() const { return body; }
	vector<string> getTraits();
	friend istream& operator>>(std::istream& is, Person& e);
	//virtual string getString() const { return to_string(ID) + " " + name; }
	bool operator==(const Person& e) { return this->name == e.name; }
};
