#include "DynamicVector.h"

/////////////////// This part is dedicated to the DYNAMIC ARRAY implementation. /////////////////////

DynamicVector* createDynamicVector(int capacity, DestroyElementFunction fct)
{
    DynamicVector* v = malloc(sizeof(DynamicVector));
    if (v == NULL)
        return NULL;
    v->len = 0;
    v->cap = capacity;
    v->elements = (TElem*)malloc(capacity * sizeof(TElem));
    if (v->elements == NULL)
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
    if (v == NULL)
        return;
    v->cap *= 2;
    TElem* aux = realloc(v->elements, v->cap * sizeof(TElem)); //this expands the space in a new memory location, doing all the steps
    if (aux == NULL)
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
    for (int i = 0; i < n - 1; i++)
        for (int j = i + 1; j < n; j++)
            if (fct(v->elements[i], v->elements[j]))
            {
                TElem aux = v->elements[i];
                v->elements[i] = v->elements[j];
                v->elements[j] = aux;
            }
}

DynamicVector* filter(DynamicVector* v, filterF fct, TElem criterion)
{
    DynamicVector* newV = createDynamicVector(v->len, v->destroyFct);
    for (int i = 0; i < v->len; i++)
        if (fct(v->elements[i], criterion))
            add(newV, v->elements[i]);
    return newV;
}
