//
// Created by M Stefan on 3/4/2020.
//
#include "controller.h"


Controller* createController(Repository* repo)
{
    Controller* c = malloc(sizeof(Controller));
    c->repo = repo;
    return c;
}

void destroyController(Controller* c)
{
    free(c);
}

DynamicVector getArchive(Controller* c)
{
    sort_desc_year(c->repo);
    return getAll(c->repo);
}

int compMaxYear(File* f, int* maxYear)
{
    //Function used to compare with the maximum year.
    return f->creationYear < *maxYear;
}

int compareDeterioration(File* f1, File* f2)
{
    //Function used to compare the state of deterioration of 2 files.
    return strlen(f1->dState) > strlen(f2->dState);
}

DynamicVector* filter_year(Controller* c, int year)
{
    TElem max_year = &year;
    DynamicVector* newV = filter(c->repo->data, &compMaxYear, max_year);
    sort(newV, &compareDeterioration);
    return newV;
}

int compareType(File *f, char* wanted_type)
{
    if(!strcmp(f->type, wanted_type))
        return 1;
    return 0;
}

DynamicVector* filter_type(Controller* c, char* type)
{
    return filter(c->repo->data, (filterF) &compareType, type);
}

int srv_addFile(Controller* c, int ID, char *dState, char *type, int cYear)
{
    if(checkExisting(c->repo,ID))
        return 0;
    File *f = createFile(ID,dState,type,cYear);
    saveOperation(c->repo, "add", deepcopyFile(f)); // save for undo/redo
    repo_addFile(c->repo,f);
    return 1;
}

int srv_updateFile(Controller* c, int ID, char *dState, char *type, int cYear)
{
    if(!checkExisting(c->repo,ID))
        return 0;
    File* newF = createFile(ID,dState,type,cYear);
    saveOperation(c->repo, "update", getFile(c->repo, ID));  // save for undo/redo
    repo_updateFile(c->repo,newF);
    return 1;
}

int srv_deleteFile(Controller* c, int ID)
{
    if(!checkExisting(c->repo,ID))
        return 0;
    saveOperation(c->repo, "delete", getFile(c->repo,ID));  // save for undo/redo
    repo_deleteFile(c->repo,ID);
    return 1;
}

int srv_undo(Controller* c)
{
    return undoLastOperation(c->repo);
}

int srv_redo(Controller* c)
{
    return redoLastOperation(c->repo);
}