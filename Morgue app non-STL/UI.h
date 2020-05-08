#pragma once
#include "controller.h"
#include <string>
#include <iostream>
#include <sstream>
using namespace std;

class consoleUI
{
private:
	Service& srv;

public:
	// constructor
	consoleUI(Service& s) : srv(s) {}

	void run();

private:
	static void printHelp();
	static void printVictims(DynamicVector<Victim> victims);
	static bool is_number(const string& s);
	static string trim(const string& str);
	static DynamicVector<string> split(const string& s, char delimiter);
	void runMorgueAdmin();
	void runMorgueAssistant();
	void adminAddVictim();
	void adminUpdateVictim();
	void adminDeleteVictim();
	void adminDisplayVictims();
	void assistantDisplayNext();
	void assistantSaveCurrent();
	void assistantFilterVictims();
	void assistantDisplayVictims();
};