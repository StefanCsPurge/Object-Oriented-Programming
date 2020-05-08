//
// Created by M Stefan on 3/2/2020.
//

#pragma once
#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "controller.h"

typedef struct{
    Controller* ctrl;
} UI;

UI* createUI(Controller* ctrl);

void printFiles(DynamicVector v);

void destroyUI(UI* ui);

/** The possible console commands:

    add archiveCatalogueNumber, stateOfDeterioration, fileType, yearOfCreation
    update archiveCatalogueNumber, newStateOfDeterioration, newFileType, newYearOfCreation
    delete archiveCatalogueNumber
    list
    list fileType
    list yearOfCreation
    undo
    redo
    exit
*/
void MyConsole(UI* ui);
