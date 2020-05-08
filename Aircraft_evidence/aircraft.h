#pragma once
#include <string>
using namespace std;

class Aircraft
{
protected:
	int ID;
	string model;
	string suitable;
	int maxAlt;
public:
	int getID() { return ID; }
	string getActivity() const { return suitable; }
	int getMaxAlt() { return maxAlt; }	
	virtual string getString() const=0;
};

class Helicopter : public Aircraft
{
private:
	bool isPrivate;

public:
	Helicopter(int ID=0,const string& model="",const string& suitable="",int maxAlt=0, bool isPriv=false);
	friend istream& operator>>(std::istream& is, Helicopter& h);
	friend ostream& operator<<(std::ostream& os, const Helicopter& h);
	string getString() const override;
};

class Plane : public Aircraft
{
private:
	bool isPrivate;
	string mainWings;

public:
	Plane(int ID=0,const string& model ="",const string& suitable ="",int maxAlt = 0, bool isPriv = false, const string& mainWings="");
	//friend istream& operator>>(std::istream& is, Plane& p);
	friend ostream& operator<<(std::ostream& os, const Plane& p);
	string getString() const override;
};

class HotAirBalloon : public Aircraft
{
private:
	int weightLimit;

public:
	HotAirBalloon(int ID = 0, const string& model = "", int maxAlt = 0, int weightLim=0);
	//friend istream& operator>>(std::istream& is, HotAirBalloon& b);
	friend ostream& operator<<(std::ostream& os, const HotAirBalloon& b);
	string getString() const override;
};