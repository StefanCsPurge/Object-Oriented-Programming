#include "UI.h"
#include <iostream>
#include <algorithm>
#include <sstream>
using namespace std;

void UI::printMenu()
{
	cout << endl;
	cout << "1 - Add normal client" << endl;
	cout << "2 - Add wealthy client" << endl;
	cout << "3 - Add dwelling" << endl;
	cout << "4 - List" << endl;
	cout << "5 - List dwelling type" << endl;
	cout << "6 - Save client to file" << endl;
	cout << "0 - Exit." << endl;
}

void UI::addNClient()
{
	double sal;
	string name;
	cout << "Insert name ";
	getline(cin, name);
	cout << "Insert sal ";
	cin >> sal;
	//cin.ignore();
	srv.addNCl(name, sal);
}

void UI::addWClient()
{
	double sal,inv;
	string name;
	cout << "Insert name ";
	getline(cin, name);
	cout << "Insert sal ";
	cin >> sal;
	cout << "Insert investments ";
	cin >> inv;
	//cin.ignore();
	srv.addWCl(name, sal,inv);
}

void UI::addDwelling()
{
	double pr;
	string type;
	bool prof;
	cout << "Insert type ";
	cin >> type;
	cout << "Insert price ";
	cin >> pr;
	cout << "Insert profitable (0/1) ";
	cin >> prof;
	//cin.ignore();
	srv.addDw(type, pr,prof);
}

void UI::displayDwType()
{
	/// Show all clients interested in in any dwelling of the type!
	string type;
	cout << "Insert type: ";
	cin >> type;
	vector<Client*> v = srv.getAllDwType(type);
	for_each(v.begin(), v.end(), [&](auto a) {cout << a->getString(); });
}

void UI::list()
{
	vector<Client*> v1 =  srv.getAllClients();
	vector<Dwelling> v2 = srv.getAllDw();
	for_each(v1.begin(), v1.end(), [&](auto a) {cout << a->getString(); });
	cout << endl;
	for_each(v2.begin(), v2.end(), [&](auto a) {cout << a.getString(); });
}

void UI::saveClients()
{
	string file;
	cout << "Insert file: ";
	getline(cin, file);
	srv.saveClToFile(file);
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
				addNClient();
			}
			else if (command == 2)
			{
				addWClient();
			}
			else if (command == 3)
			{
				addDwelling();
			}
			else if (command == 4)
			{
				list();
			}
			else if (command == 5)
			{
				displayDwType();
			}
			else if (command == 6)
			{
				saveClients();
			}
		}
		catch (exception& e)
		{
			cout << e.what() << endl;
		}
	}
}

string UI::trim(const string& str)
{
	size_t first = str.find_first_not_of(' ');
	if (string::npos == first)
		return "";
	size_t last = str.find_last_not_of(' ');
	return str.substr(first, (last - first + 1));
	//restCmd.erase(remove_if(restCmd.begin(), restCmd.end(), isspace), restCmd.end());  this erases all spaces
}

vector<string> UI::split(const string& s, char delimiter)
{
	vector<string> tokens;
	string token;
	istringstream tokenStream(s);
	while (getline(tokenStream, token, delimiter))
		tokens.push_back(trim(token));
	return tokens;
}