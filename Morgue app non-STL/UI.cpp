#include "UI.h"

void consoleUI::printHelp()
{
	cout << "The possible commands are: \n";
	cout << "\t mode X (e.g. mode A - works off-mode)\n";
	cout << "In morgue administrator mode:\n";
	cout << "\t add name, placeOfOrigin, age, photograph\n";
	cout << "\t update name, newPlaceOfOrigin, newAge, newPhotograph\n";
	cout << "\t delete name\n";
	cout << "\t list\n";
	cout << "In morgue assistant mode:\n";
	cout << "\t next\n";
	cout << "\t save name\n";
	cout << "\t list placeOfOrigin, age\n";
	cout << "\t mylist\n";
	cout << "\t help (any mode)\n";
	cout << "\t exit (to exit the current mode/program)\n";
}

void consoleUI::printVictims(DynamicVector<Victim> victims)
{
	if (!victims.getSize()) { cout << "There are no victims!\n"; return; }
	cout << "Your dead bodies are:\n";
	for (int i = 0; i < victims.getSize(); i++)
		cout << victims[i].toString() << endl;
}

bool consoleUI::is_number(const string& s)
{
	string::const_iterator it = s.begin();
	while (it != s.end() && isdigit(*it)) ++it;
	return !s.empty() && it == s.end();
}

string consoleUI::trim(const string& str)
{
	size_t first = str.find_first_not_of(' ');
	if (string::npos == first)
		return str;
	size_t last = str.find_last_not_of(' ');
	return str.substr(first, (last - first + 1));
	//restCmd.erase(remove_if(restCmd.begin(), restCmd.end(), isspace), restCmd.end());  this erases all spaces
}

DynamicVector<string> consoleUI::split(const string& s, char delimiter)
{
	DynamicVector<string> tokens;
	string token;
	istringstream tokenStream(s);
	while (getline(tokenStream, token, delimiter))
		tokens.add(trim(token));
	return tokens;
}

void consoleUI::adminAddVictim()
{
	string restCmd;
	getline(cin, restCmd);
	DynamicVector<string> args = split(restCmd, ',');
	if (args.getSize() < 4) {cout << "Too few arguments!\n"; return;}
	string name = args[0];
	string placeOfOrigin = args[1];
	if (!is_number(args[2])) { cout << "Invalid age!\n"; return; }
	int age = stoi(args[2]);
	string photo = args[3];
	if (!this->srv.addVictimToRepo(name, placeOfOrigin, age, photo))
		cout << "There already exists a victim with this name!\n";
}

void consoleUI::adminUpdateVictim()
{
	string restCmd;
	getline(cin, restCmd);
	DynamicVector<string> args = split(restCmd, ',');
	if (args.getSize() < 4) { cout << "Too few arguments!\n"; return; }
	string name = args[0];
	string newPlaceOfOrigin = args[1];
	if (!is_number(args[2])) { cout << "Invalid age!\n"; return; }
	int newAge = stoi(args[2]);
	string newPhoto = args[3];
	if (!this->srv.updateVictim(name, newPlaceOfOrigin, newAge, newPhoto))
		cout << "There is no victim with this name!\n";
}

void consoleUI::adminDeleteVictim()
{
	string name;
	getline(cin, name);
	name = trim(name);
	if (!this->srv.deleteVictim(name))
		cout << "There is no victim with this name!\n";
}

void consoleUI::adminDisplayVictims()
{
	printVictims(this->srv.getAllVictims());
}
void consoleUI::assistantDisplayNext()
{
	this->srv.nextVictim();
	Victim v = this->srv.getCurrentVictim();
	cout << v.toString() << endl;
}

void consoleUI::assistantSaveCurrent()
{
	string name;
	getline(cin, name);
	name = trim(name);
	if(!this->srv.moveVictimToAssistantList(name))
		cout << "There was no victim with this name!\n";
}

void consoleUI::assistantFilterVictims()
{
	DynamicVector<Victim> selectedVictims;
	string restCmd, name;
	getline(cin, restCmd);
	DynamicVector<string> args = split(restCmd, ',');
	if (!args.getSize()) { cout << "No arguments!\n"; return; }
	if (args.getSize() == 1)
	{
		if (!is_number(args[0])) { cout << "Invalid age!\n"; return; }
		int age = stoi(args[0]);
		selectedVictims = this->srv.filterVictims("", age);
	}
	else
	{
		if (!is_number(args[1])) { cout << "Invalid age!\n"; return; }
		int age = stoi(args[1]);
		selectedVictims = this->srv.filterVictims(args[0], age);
	}
	printVictims(selectedVictims);
}

void consoleUI::assistantDisplayVictims()
{
	printVictims(this->srv.getAssistantVictims());
}

void consoleUI::runMorgueAdmin()
{
	system("cls");
	cout << "You are now in EC-PD MORGUE administrator mode. Have fun!\n";
	string cmd;
	while (true)
	{
		cout << ">>";
		cin >> cmd;
		if (cmd == "add")
			adminAddVictim();
		else if (cmd == "update")
			adminUpdateVictim();
		else if (cmd == "delete")
			adminDeleteVictim();
		else if (cmd == "list")
			adminDisplayVictims();
		else if (cmd == "help")
			printHelp();
		else if (cmd == "exit")
			break;
			//exit(0);
		else if (cmd == "mode")
		{
			cin >> cmd;
			if (cmd == "B")
			{
				runMorgueAssistant();
				return;
			}
		}
		else
		{
			cout << "Non-existent command!\n";
			getline(cin, cmd);
		}
	}
	cout << "You are not a morgue administrator anymore. The dead bodies thank you for your service.\n\n";
}

void consoleUI::runMorgueAssistant()
{
	system("cls");
	cout << "You are now in EC-PD MORGUE assistant mode. Have fun!\n";
	string cmd;
	while (true)
	{
		cout << ">>";
		cin >> cmd;
		if (cmd == "help")
			printHelp();
		else if (cmd == "next")
			assistantDisplayNext();
		else if (cmd == "save")
			assistantSaveCurrent();
		else if (cmd == "mylist")
			assistantDisplayVictims();
		else if (cmd == "list")
			assistantFilterVictims();
		else if (cmd == "exit")
			break;
			//exit(0);
		else if (cmd == "mode")
		{
			cin >> cmd;
			if (cmd == "A")
			{
				runMorgueAdmin();
				return;
			}
		}
		else
		{
			cout << "Non-existent command!\n";
			getline(cin, cmd);
		}
	}
	cout << "You are not a morgue assistant anymore. The dead bodies thank you for your service.\n\n";
}

void consoleUI::run()
{
	cout << "WELCOME TO THE MORGUE ! \n\n";
	cout << "Enter 'help' to see the possible commands\n\n";
	string cmd;
	while (true)
	{
		cout << "Choose between:  EC-PD morgue admin (mode A)  OR  EC-PD morgue assistant (mode B)\n";
		cout << ">>";
		cin >> cmd;
		if (cmd == "help")
			this->printHelp();
		else if (cmd == "exit")
			break;
		else if (cmd == "mode")
		{
			cin >> cmd;
			if (cmd == "A")
				runMorgueAdmin();
			else if (cmd == "B")
				runMorgueAssistant();
			else 
				cout << "N/A mode!\n";
		}
		else
			cout << "Invalid command!\n";
		
		getline(cin, cmd); // get rid of the remaining user garbage on the line
	}
}