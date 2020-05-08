#pragma once
#include "service.h"

class UI
{
private:
	Service& srv;

public:
	UI(Service& s) : srv(s) {}
	void run();

private:
	static void printMenu();
	void addNClient();
	void addWClient();
	void addDwelling();
	void displayDwType();
	void list();
	void saveClients();
	static string trim(const string& str);
	static vector<string> split(const string& s, char delimiter);
};