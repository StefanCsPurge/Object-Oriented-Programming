//
// Created by M Stefan on 3/2/2020.
//
#include "repo.h"


Repository* createRepo()
{
    Repository* repo = malloc(sizeof(Repository));
    repo->data = createDynamicVector(8, &destroyFile);
    repo->opHistory = createDynamicVector(8, &destroyOperation);
    repo->hIndex = -1;
    return repo;
}

void destroyRepository(Repository* repo)
{
    if(repo == NULL)
        return;
    destroyDynamicVector(repo->data);
    destroyDynamicVector(repo->opHistory);
    free(repo);
}

int checkExisting(Repository* repo, int ID)
{
    for(int i=0;i<repo->data->len;i++)
        if(getID(repo->data->elements[i]) == ID)
            return 1;
    return 0;
}

File* getFile(Repository* repo, int ID)
{
    for (int i = 0; i < repo->data->len; i++)
        if (getID(repo->data->elements[i]) == ID)
            return deepcopyFile(repo->data->elements[i]);
    return NULL;
}

void repo_addFile(Repository* repo, File* f)
{
    if(repo == NULL)
        return;
    add(repo->data,f);
}

void repo_updateFile(Repository* repo, File* f)
{
    for(int i=0;i<repo->data->len;i++)
        if(getID(repo->data->elements[i])==f->id)
        {
            destroyFile(repo->data->elements[i]);
            repo->data->elements[i] = f;
            break;
        }
}

void repo_deleteFile(Repository* repo, int ID)
{
    for(int i=0;i<repo->data->len;i++)
        if(getID(repo->data->elements[i]) == ID) {
            removeF(repo->data, i);
            break;
        }
}

int compareYear(File* f1, File* f2)
{
    //Function used to compare the creation years of two given files.
    return f1->creationYear < f2->creationYear;
}

void sort_desc_year(Repository* repo)
{
    sort(repo->data, (compF) &compareYear);
}

DynamicVector getAll(Repository* repo)
{
    return *(repo->data);
}

void saveOperation(Repository* repo, char* opName, File* f)
{
    repo->hIndex ++;

    // First, we have to delete the instances that were kept for the 'redo' functionality.
    for(int i=repo->hIndex; i<repo->opHistory->len;i++)
        destroyOperation(repo->opHistory->elements[i]);
    repo->opHistory->len = repo->hIndex;

    Operation* op = createOperation(opName,f);
    add(repo->opHistory,op);
}

int undoLastOperation(Repository* repo)
{
    if(repo->hIndex < 0)
        return 0;
    Operation* lastOp = repo->opHistory->elements[repo->hIndex];
    if (!strcmp(lastOp->name, "add"))
        repo_deleteFile(repo, lastOp->file->id);
    else if (!strcmp(lastOp->name, "delete"))
        repo_addFile(repo, deepcopyFile(lastOp->file));
    else if (!strcmp(lastOp->name, "update"))
    {
        File* replacementFile = lastOp->file;
        lastOp->file = getFile(repo, replacementFile->id); // save the old file for redo
        repo_updateFile(repo, replacementFile);
    }
    repo->hIndex --;
    return 1;
}

int redoLastOperation(Repository* repo)
{
    if(repo->hIndex+1 >= repo->opHistory->len)
        return 0;
    repo->hIndex ++;
    Operation* lastOp = repo->opHistory->elements[repo->hIndex];
    if (!strcmp(lastOp->name, "add"))
        repo_addFile(repo, deepcopyFile(lastOp->file));
    else if (!strcmp(lastOp->name, "delete"))
        repo_deleteFile(repo, lastOp->file->id);
    else if (!strcmp(lastOp->name, "update"))
    {
        File* replacementFile = lastOp->file;
        lastOp->file = getFile(repo, replacementFile->id); // save the old file for undo
        repo_updateFile(repo, replacementFile);
    }
    return 1;
}