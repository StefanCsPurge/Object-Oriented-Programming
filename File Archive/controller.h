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

void destroyController(Controller *c);

DynamicVector getArchive(Controller* c);

DynamicVector* filter_year(Controller* c, int year);

DynamicVector* filter_type(Controller* c, char* type);

int srv_addFile(Controller* c, int ID, char *dState, char *type, int cYear);

int srv_updateFile(Controller *c, int ID, char *dState, char *type, int cYear);

int srv_deleteFile(Controller* c, int ID);

int srv_undo(Controller* c);

int srv_redo(Controller* c);