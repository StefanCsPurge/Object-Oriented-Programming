// Lab5 C++.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <crtdbg.h>
#include <iostream>
#include "tests.h"
#include "UI.h"

using namespace std;

int main()
{
    /// MY LOVELY MORGUE APP :)
    testAll(); // here we run all the required tests
    {
        Repository repo{};
        Service service{ repo };
        service.addEntries();
        consoleUI ui{ service };
        // Morgue start point
        ui.run();
    }
    //_CrtDumpMemoryLeaks();
}

