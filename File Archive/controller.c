//
// Created by M Stefan on 3/4/2020.
//
#include "controller.h"

int max_year = 0;

char wanted_type[55];

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

int compMaxYear(File* f)
{
    return (f->creationYear) < max_year;
}

int compareDeterioration(File* f1, File* f2)
{
    return strlen(f1->dState) > strlen(f2->dState);
}

DynamicVector* filter_year(Controller* c, int year)
{
    max_year = year;
    DynamicVector* newV = filter(c->repo->data, (filterF) &compMaxYear);
    sort(newV, (compF) &compareDeterioration);
    return newV;
}

int compareType(File *f)
{
    if(!strcmp(f->type, wanted_type))
        return 1;
    return 0;
}

DynamicVector* filter_type(Controller* c, char* type)
{
    strcpy(wanted_type,type);
    return filter(c->repo->data, (filterF) &compareType);
}

int srv_addFile(Controller* c, int ID, char *dState, char *type, int cYear)
{
    if(checkExisting(c->repo,ID))
        return 0;
    File *f = createFile(ID,dState,type,cYear);
    repo_addFile(c->repo,f);
    saveRepoState(c->repo);
    return 1;
}

int srv_updateFile(Controller* c, int ID, char *dState, char *type, int cYear)
{
    if(!checkExisting(c->repo,ID))
        return 0;
    File* newF = createFile(ID,dState,type,cYear);
    repo_updateFile(c->repo,newF);
    saveRepoState(c->repo);
    return 1;
}

int srv_deleteFile(Controller* c, int ID)
{
    if(!checkExisting(c->repo,ID))
        return 0;
    repo_deleteFile(c->repo,ID);
    saveRepoState(c->repo);
    return 1;
}

int srv_undo(Controller* c)
{
    return restorePreviousRepo(c->repo);
}

int srv_redo(Controller* c)
{
    return restoreNextRepo(c->repo);
}