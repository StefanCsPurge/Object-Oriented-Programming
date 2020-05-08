//
// Created by M Stefan on 3/4/2020.
//
#pragma once
#define _CRT_SECURE_NO_DEPRECATE
#include <string.h>
#include <stdlib.h>
#include "repo.h"

typedef struct{
    Repository* repo;
} Controller;

Controller* createController(Repository* repo);

// Function that deallocates the memory of the controller.
void destroyController(Controller *c);


/*  Function that gets the archive sorted descending by the year. 
    input: c - the pointer to the controller struct
    output: the sorted dynamic vector containing all the files */
DynamicVector getArchive(Controller* c);


/*  Function that returns a pointer to a new dynamic vector containing the pointers to the files
    which have yearOfCreation greater than a given year.
    input: c - the pointer to the controller struct
           year - int, the given year
    output: the pointer to the new dynamic vector */
DynamicVector* filter_year(Controller* c, int year);


/*  Function that returns a pointer to a new dynamic vector containing the pointers to the files
    which have a given type.
    input: c - the pointer to the controller struct
           type - pointer to a string (the given type)
    output: the pointer to the new dynamic vector. */
DynamicVector* filter_type(Controller* c, char* type);


int srv_addFile(Controller* c, int ID, char *dState, char *type, int cYear);

int srv_updateFile(Controller *c, int ID, char *dState, char *type, int cYear);

int srv_deleteFile(Controller* c, int ID);

int srv_undo(Controller* c);

int srv_redo(Controller* c);