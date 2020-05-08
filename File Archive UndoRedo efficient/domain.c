//
// Created by M Stefan on 3/4/2020.
//
#include "domain.h"

File* createFile(int ID, char *dState, char *type, int creationYear)
{
    File* f = malloc(sizeof(File));
    if(f == NULL)
        return NULL;
    f->id= ID;
    f->creationYear = creationYear;
    f->dState = malloc(sizeof(char) * (strlen(dState) + 1));
    strcpy(f->dState,dState);
    f->type = malloc(sizeof(char) * (strlen(type)+1));
    strcpy(f->type,type);
    return f;
}

File* deepcopyFile(File* f)
{
    return createFile(f->id,f->dState,f->type,f->creationYear);
}

void destroyFile(File* f)
{
    if(f == NULL)
        return;
    free(f->dState);
    free(f->type);
    free(f);
}

char* getStateOfDeterioration(File* f)
{
    return f->dState;
}

char* getType(File* f)
{
    return f->type;
}

int getID(File* f)
{
    return f->id;
}

int getCreationYear(File* f)
{
    return f->creationYear;
}

Operation* createOperation(char* opName, File* f)
{
    Operation* op = malloc(sizeof(Operation));
    if (op == NULL)
        return NULL;
    op->name = malloc(sizeof(char) * (strlen(opName) + 1));
    strcpy(op->name, opName);
    op->file = f;
    return op;
}

void destroyOperation(Operation* op)
{
    free(op->name);
    destroyFile(op->file);
    free(op);
}