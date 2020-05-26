#include "domain.h"


istream& operator >> (istream& in, Person& e)
{
	string line, token;
	getline(in, line);
	if (line == "")
		return in;
	stringstream tokenStream(line);
	getline(tokenStream, token, '|');
	e.body = token;
	getline(tokenStream, token, '|');
	e.name = token;
	getline(tokenStream, token, '|');
	e.traits = token;
	return in;
}

vector<string> Person::getTraits()
{
	vector<string> tokens;
	string token;
	istringstream tokenStream(traits);
	while (getline(tokenStream, token, ','))
		tokens.push_back(token);
	return tokens;
}
