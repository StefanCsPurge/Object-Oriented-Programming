//
// Created by M Stefan on 3/10/2020.
//
#include "tests.h"

void testFile()
{
    File *f = createFile(11,"okIsh","idk",343);
    assert(getID(f) == 11);
    assert(strcmp(getStateOfDeterioration(f),"okIsh")==0);
    assert(strcmp(getType(f),"idk")==0);
    assert(getCreationYear(f) == 343);
    destroyFile(f);
}

void testFilesDynamicVector()
{
    DynamicVector* v = createDynamicVector(2, (DestroyElementFunction) &destroyFile);
    File* f1 = createFile(11,"good","pap",400);
    File* f2 = createFile(22,"bad","paper",555);
    File* f3 = createFile(33,"med","pdf",420);

    add(v, f1);
    assert(v->len == 1);
    assert(v->elements[0] == f1); //test add
    add(v,f2);
    add(v,f3);
    assert(v->len == 3); // test add
    assert(v->cap == 4); // test resize
    removeF(v,1);
    assert(v->len == 2);
    assert(v->elements[1] == f3); // test remove
    destroyDynamicVector(v); // also destroys the elements of the vector
}

void testVectorsDynamicVector()
{
    DynamicVector* v1 = createDynamicVector(2, (DestroyElementFunction) &destroyFile);
    File* f1 = createFile(11,"good","pap",400);
    File* f2 = createFile(22,"bad","paper",555);
    add(v1, f1);
    add(v1, f2);

    DynamicVector* v2 = createDynamicVector(2, (DestroyElementFunction) &destroyFile);
    File* f3 = createFile(33,"med","pdf",420);
    add(v2, f3);

    DynamicVector* vOfVectors = createDynamicVector(2, (DestroyElementFunction) &destroyDynamicVector);
    add(vOfVectors, v1);
    assert(vOfVectors->len == 1);
    add(vOfVectors, v2);
    assert(vOfVectors->len == 2);
    removeF(vOfVectors,0);
    assert(vOfVectors->len == 1);
    assert(vOfVectors->elements[0] == v2);

    destroyDynamicVector(vOfVectors);
}

void runAllTests()
{
    testFile();
    testFilesDynamicVector();
    testVectorsDynamicVector();
}