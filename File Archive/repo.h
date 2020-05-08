//
// Created by M Stefan on 3/4/2020.
//
#pragma once
#include <stdlib.h>
#include <stdio.h>
#include "domain.h"

typedef void* TElem;

typedef int (*compF)(TElem ,TElem);

typedef int (*filterF)(TElem);

typedef void (*DestroyElementFunction)(void*);

typedef struct
{
    TElem* elements;
    int len,cap;
    DestroyElementFunction destroyFct;
}DynamicVector;

DynamicVector* createDynamicVector(int capacity, DestroyElementFunction fct);
void destroyDynamicVector(DynamicVector* v);
void add(DynamicVector* v, TElem elem);
void removeF(DynamicVector* v, int position);
void sort(DynamicVector* v, compF fct);

/// Functions that return new dynamic vectors of files.
DynamicVector* filter(DynamicVector* v, filterF fct);
DynamicVector* deepcopyFiles(DynamicVector* v);

typedef struct
{
    DynamicVector* data;
    DynamicVector* dataHistory;
    int hIndex;
}Repository;

Repository* createRepo();

void destroyRepository(Repository* repo);

int checkExisting(Repository* repo,int ID);

void repo_addFile(Repository* repo, File* f);

void repo_updateFile(Repository* repo, File* f);

void repo_deleteFile(Repository* repo, int ID);

void sort_desc_year(Repository* repo);

DynamicVector getAll(Repository* repo);

void saveRepoState(Repository* repo);

int restorePreviousRepo(Repository* repo);

int restoreNextRepo(Repository* repo);
