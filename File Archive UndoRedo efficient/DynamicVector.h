#pragma once
#include <stdlib.h>

typedef void* TElem;

typedef int (*compF)(TElem, TElem);

typedef int (*filterF)(TElem, TElem);

typedef void (*DestroyElementFunction)(void*);

typedef struct
{
    TElem* elements;
    int len, cap;
    DestroyElementFunction destroyFct;
}DynamicVector;


/// Function that allocates new memory in order to create a new dynamic vector.
DynamicVector* createDynamicVector(int capacity, DestroyElementFunction fct);

///  Function that frees the memory that was allocated for the dynamic vector.
void destroyDynamicVector(DynamicVector* v);


/*  Function that adds a new element to the dynamic vector.
    input: v - pointer to the dynamic vector to append to
           elem - pointer to the element to append
    output: nothing*/
void add(DynamicVector* v, TElem elem);


/*  Function that removes the element of the vector from a given position.
    input: v - pointer to the dynamic vector to filter
           position - int, the given position
    output: nothing */
void removeF(DynamicVector* v, int position);


/*  Function that sorts the dynamic vector.
    input: v - pointer to the dynamic vector to filter
           fct - pointer to the function used to sort the elements
    output: nothing */
void sort(DynamicVector* v, compF fct);


/*  Function that creates a new dynamic vector with the elemets that respect a given criteria.
    input: v - pointer to the dynamic vector to filter
           fct - pointer to the function used to filter the elements
           critertion - pointer to the criterion used to filter the elements
    output: the pointer to the new dynamic vector containing the pointers of the selected elements */
DynamicVector* filter(DynamicVector* v, filterF fct, TElem criterion);

