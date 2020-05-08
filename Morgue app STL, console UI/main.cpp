// Lab5 C++.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include "tests/tests.h"
#include "user interface/UI.h"
using namespace std;

void main()
{
    /// MY LOVELY MORGUE APP :)
    testAll(); // here we run all the required tests
    {
        Repository* repo;
        cout << "Press 1 usual repository / 2 for SQL repository -> ";
        int choice; bool sqlRepo = false;
        cin >> choice;
        if (choice == 1)
            repo = new Repository{};
        else {
            cout << "Using Connector C++ 8.0 (certain dll's from lib64 directory are required at execution)" << endl;
            repo = new MYSQLRepository{};
            sqlRepo = true;
        }
        Service service{ repo };
        consoleUI ui{ service , sqlRepo};
        // Morgue start point
        ui.run();
    }
    _CrtDumpMemoryLeaks();
}

