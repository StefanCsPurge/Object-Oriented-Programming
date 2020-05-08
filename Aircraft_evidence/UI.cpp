#include "UI.h"
#include <iostream>
#include <algorithm>
using namespace std;

void UI::printMenu()
{
	cout << endl;
	cout << "1 - Add helicopter." << endl;
	cout << "2 - Add plane." << endl;
	cout << "3 - Add hot air balloon." << endl;
	cout << "4 - Display all aircraft which can be used for a certain activity." << endl;
	cout << "5 - Diplay all aircraft which can reach at least a given altitude." << endl;
	cout << "0 - Exit." << endl;
}


void UI::addHelicopter()
{
	int ID, maxAlt;
	string priv, model, suitable;
	bool isPrivate;
	cout << "ID: ";
	cin >> ID;
	cout << "Model: ";
	cin >> model;
	cin.ignore();
	cout << "Suitable for: ";
	getline(cin, suitable);
	cout << "Max altitude: ";
	cin >> maxAlt;
	cout << "Private? [y/n] ";
	cin >> priv;
	if (priv == "y")
		isPrivate = true;
	else isPrivate = false;
	serv.addHelicopterToRepo(ID, model, suitable, maxAlt, isPrivate);
}
void UI::addPlane()
{
	int ID, maxAlt;
	string priv, model, suitable, mainWings;
	bool isPrivate;
	cout << "ID: ";
	cin >> ID;
	cout << "Model: ";
	cin >> model;
	cin.ignore();
	cout << "Suitable for: ";
	getline(cin, suitable);
	cout << "Max altitude: ";
	cin >> maxAlt;
	cout << "Private? [y/n] ";
	cin >> priv;
	if (priv == "y")
		isPrivate = true;
	else isPrivate = false;
	cout << "Main wings (monoplane/biplane): ";
	cin >> mainWings;
	serv.addPlaneToRepo(ID, model, suitable, maxAlt, isPrivate, mainWings);
}
void UI::addBalloon()
{
	int ID, maxAlt, weightLim;
	string priv, model, suitable;
	cout << "ID: ";
	cin >> ID;
	cout << "Model: ";
	cin >> model;
	cout << "Max altitude: ";
	cin >> maxAlt;
	cout << "Weight limit: ";
	cin >> weightLim;
	serv.addBalloonToRepo(ID, model, maxAlt, weightLim);
	
}
void UI::displayActivityAircraft()
{
	string act;
	cout << "Insert activity: ";
	getline(cin, act);
	listAircraft(serv.getActivityAircraft(act));
}
void UI::displayAltitudeAircraft()
{
	int alt;
	cout << "Insert min altitude: ";
	cin >> alt;
	listAircraft(serv.getAltitudeAircraft(alt));
}

void UI::listAircraft(vector<Aircraft*> v)
{
	for_each(v.begin(), v.end(), [&](auto a) {cout << a->getString(); });
}

void UI::run()
{
	while (true)
	{
		UI::printMenu();
		int command{ 0 };
		cout << "Input the command: ";
		cin >> command;
		cin.ignore();
		if (command == 0)
			break;
		try {
			if (command == 1)
			{
				addHelicopter();
			}
			else if (command == 2)
			{
				addPlane();
			}
			else if (command == 3)
			{
				addBalloon();
			}
			else if (command == 4)
			{
				displayActivityAircraft();
			}
			else if (command == 5)
			{
				displayAltitudeAircraft();
			}
		}
		catch (exception& e)
		{
			cout << e.what() << endl;
		}
	}
}