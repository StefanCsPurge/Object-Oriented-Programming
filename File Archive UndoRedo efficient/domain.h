//
// Created by M Stefan on 3/4/2020.
//
#pragma once
#define _CRT_SECURE_NO_DEPRECATE
#include <string.h>
#include <stdlib.h>

typedef struct
{
    int id,creationYear;
    char *dState,*type;
}File;

File* createFile(int ID, char *dState, char *type, int creationYear);
void destroyFile(File* f);
File* deepcopyFile(File * f);
char* getStateOfDeterioration(File* f);
char* getType(File* f);
int getID(File* f);
int getCreationYear(File* f);


///  Operation type used for undo/redo functionality.
typedef struct
{
    char* name;
    File* file;

}Operation;

Operation* createOperation(char* opName, File* f);

void destroyOperation(Operation* op);