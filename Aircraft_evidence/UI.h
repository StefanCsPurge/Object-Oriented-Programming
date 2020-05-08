#pragma once
#include "service.h"

class UI
{
private:
	Service& serv;

public:
	UI(Service& s) : serv(s) {}
	void run();

private:
	static void printMenu();
	void addHelicopter();
	void addPlane();
	void addBalloon();
	void displayActivityAircraft();
	void displayAltitudeAircraft();
	static void listAircraft(vector<Aircraft*>);
};