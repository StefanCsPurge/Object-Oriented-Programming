//
// Created by M Stefan on 3/4/2020.
//
#pragma once
#include <stdio.h>
#include "domain.h"
#include "DynamicVector.h"


typedef struct
{
    DynamicVector* data; // vector used to store all the files
    DynamicVector* opHistory; // vector used to store all the operations that modified the repository 
    int hIndex; // the history index used to figure out which operation is currently considered next for undo/redo
}Repository;

Repository* createRepo();

void destroyRepository(Repository* repo);


/*  Function that checks if a file with a given ID exists in the repository.
    input: repo - pointer to the repository struct
           ID - int, the given ID 
    output: 1 if the ID was found in the repository, 0 otherwise */
int checkExisting(Repository* repo,int ID);


/*  Function that adds a given file to the repository.
    input: repo - pointer to the repository struct 
           f - pointer to the File to add
    output: nothing */
void repo_addFile(Repository* repo, File* f);


/*  Function that updates a file in the repository.
    input: repo - pointer to the repository struct
           f - pointer to the new File
    output: nothing */
void repo_updateFile(Repository* repo, File* f);


/*  Function that removes a given file from the repository.
    input: repo - pointer to the repository struct
           ID - int, the given ID of the file to remove
    output: nothing */
void repo_deleteFile(Repository* repo, int ID);


/*  Function that sorts the files from the repository descending by yearOfCreation.
    input: repo - pointer to the repository struct
    output: nothing */
void sort_desc_year(Repository* repo);


/*  Function gets a deepcopy of a file with a given ID.
    input: repo - pointer to the repository struct
           ID - int, the given ID of the file to find
    output: File type pointer of the deepcopy*/
File* getFile(Repository* repo, int ID);


/*  Function that gets all the files from the repository.
    input: repo - pointer to the repository struct
    output: DynamicVector containing all the files */
DynamicVector getAll(Repository* repo);


/*  Function that saves an operation that modified the files repository.
    input: repo - pointer to the repository struct
           opName - pointer to char, the operation name
           f - pointer to File type, the file specific to the operation 
    output: nothing*/
void saveOperation(Repository* repo, char *opName, File* f);


/*  Function that tries to undo the last operation that modified the repository
    input: repo - pointer to the repository struct
    output: 1 if there was an operation to undo, 0 otherwise */
int undoLastOperation(Repository* repo);


/*  Function that tries to redo the last operation that modified the repository
    input: repo - pointer to the repository struct
    output: 1 if there was an operation to redo, 0 otherwise */
int redoLastOperation(Repository* repo);
