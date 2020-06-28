#pragma once
#include <string>
#include <sstream>
using namespace std;

class Astronomer
{
private:
	string name, constel;
public:
	Astronomer(const string& n="", const string& c="") : name(n), constel(c) {}
	string getName() const { return name; }
	string getConstellation() const { return constel; }
	bool operator==(const Astronomer& i) { return this->name == i.name; }

	friend istream& operator>>(istream& in, Astronomer& w)
	{
		string line, token;
		getline(in, line);
		if (line == "") return in;
		stringstream tokenStream(line);
		getline(tokenStream, token, ',');
		w.name = token;
		getline(tokenStream, token, ',');
		w.constel = token;
		return in;
	}
};

class Star
{
private:
	string name, constel;
	int RA, Dec, diam;
public:
	Star(const string& name = "", const string& cs = "", int RA = 0, int D = 0 , int diam = 0) : name(name), constel(cs), RA(RA), Dec(D), diam(diam) {}
	string getName() const { return name; }
	string getConstellation() const { return constel; }
	int getRA() { return RA; }
	int getDec() { return Dec; }
	int getDiam() { return diam; }

	//void setStatus(const string& newS) { this->status = newS; }
	//void setAct(const string& newA) { this->act = newA; }
	//void setDescription(const string& newD) { this->name = newD; }

	bool operator==(const Star& i) { return this->name == i.name; }

	friend istream& operator>>(istream& in, Star& i)
	{
		string line, token;
		getline(in, line);
		if (line == "") return in;
		stringstream tokenStream(line);
		getline(tokenStream, token, ',');
		i.name = token;
		getline(tokenStream, token, ',');
		i.constel = token;
		getline(tokenStream, token, ',');
		i.RA = stoi(token);
		getline(tokenStream, token, ',');
		i.Dec = stoi(token);
		getline(tokenStream, token, ',');
		i.diam = stoi(token);
		return in;
	}

	friend ostream& operator<<(ostream& out, const Star& i) {
		out << i.name << ',' << i.constel << ',' << i.RA << ',' << i.Dec <<',' << i.diam << "\n";
		return out;
	}

};