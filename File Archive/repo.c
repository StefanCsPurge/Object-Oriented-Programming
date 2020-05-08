//
// Created by M Stefan on 3/2/2020.
//
#include "repo.h"

/// This part is dedicated to the dynamic array implementation.

DynamicVector* createDynamicVector(int capacity, DestroyElementFunction fct)
{
    DynamicVector* v = malloc(sizeof(DynamicVector));
    if(v == NULL)
        return NULL;
    v->len = 0;
    v->cap = capacity;
    v->elements = (TElem*) malloc(capacity * sizeof(TElem));
    if(v->elements == NULL)
        return NULL;
    v->destroyFct = fct;
    return v;
}

void destroyDynamicVector(DynamicVector* v)
{
    if (v == NULL)
        return;
    for (int i = 0; i < v->len; i++)
        v->destroyFct(v->elements[i]);
    free(v->elements);
    free(v);
}

void resize(DynamicVector* v)
{
    if(v == NULL)
        return;
    v->cap *= 2;
    TElem* aux = realloc(v->elements, v->cap * sizeof(TElem)); //this expands the space in a new memory location, doing all the steps
    if(aux == NULL)
        return;
    v->elements = aux;
}

void add(DynamicVector* vector, TElem elem)
{
    if (vector == NULL)
        return;
    if (vector->len == vector->cap) {
        resize(vector);
    }
    vector->elements[vector->len++] = elem;
}

void removeF(DynamicVector* v, int position)
{
    v->destroyFct(v->elements[position]);
    for (int j = position; j < v->len - 1; j++)
        v->elements[j] = v->elements[j + 1];
    v->len -= 1;
}

void sort(DynamicVector* v, compF fct)
{
    int n = v->len;
    for(int i=0;i<n-1;i++)
        for(int j=i+1;j<n;j++)
            if(fct(v->elements[i],v->elements[j]))
            {
                TElem aux = v->elements[i];
                v->elements[i] = v->elements[j];
                v->elements[j] = aux;
            }
}

DynamicVector* filter(DynamicVector* v, filterF fct)
{
    DynamicVector* newV = createDynamicVector(v->len, (DestroyElementFunction) &destroyFile);
    for(int i=0;i<v->len;i++)
        if(fct(v->elements[i]))
            add(newV,deepcopyFile(v->elements[i]));
    return newV;
}

DynamicVector* deepcopyFiles(DynamicVector* v)
{
    DynamicVector* new = createDynamicVector(v->cap,v->destroyFct);
    for(int i=0;i<v->len;i++)
        add(new,deepcopyFile(v->elements[i]));
    return new;
}


/// The next part is dedicated to the repository itself.

Repository* createRepo()
{
    Repository* repo = malloc(sizeof(Repository));
    repo->data = createDynamicVector(8, (DestroyElementFunction) &destroyFile);
    repo->dataHistory = createDynamicVector(8,(DestroyElementFunction) &destroyDynamicVector);
    repo->hIndex = -1;
    saveRepoState(repo);
    return repo;
}

void destroyRepository(Repository* repo)
{
    if(repo == NULL)
        return;
    destroyDynamicVector(repo->data);
    destroyDynamicVector(repo->dataHistory);
    free(repo);
}

int checkExisting(Repository* repo, int ID)
{
    for(int i=0;i<repo->data->len;i++)
        if(getID(repo->data->elements[i]) == ID)
            return 1;
    return 0;
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

void saveRepoState(Repository* repo)
{
    repo->hIndex ++;
    // First, we have to delete the instances that were kept for the 'redo' functionality.
    for(int i=repo->hIndex; i<repo->dataHistory->len;i++)
        destroyDynamicVector(repo->dataHistory->elements[i]);
    repo->dataHistory->len = repo->hIndex;

    add(repo->dataHistory,deepcopyFiles(repo->data));
}

int restorePreviousRepo(Repository* repo)
{
    if(repo->hIndex <= 0)
        return 0;
    destroyDynamicVector(repo->data);
    repo->hIndex --;
    repo->data = deepcopyFiles(repo->dataHistory->elements[repo->hIndex]);
    return 1;
}

int restoreNextRepo(Repository* repo)
{
    if(repo->hIndex+1 >= repo->dataHistory->len)
        return 0;
    destroyDynamicVector(repo->data);
    repo->hIndex ++;
    repo->data = deepcopyFiles(repo->dataHistory->elements[repo->hIndex]);
    return 1;
}