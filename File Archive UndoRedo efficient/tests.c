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

void testRepository()
{
    Repository* repo = createRepo();
    assert(checkExisting(repo, 123) == 0);
    File* f1 = createFile(11, "good", "pap", 400);
    repo_addFile(repo, f1);
    assert(checkExisting(repo, 11) == 1);
    File* f2 = createFile(11, "bad", "paper", 355);
    repo_updateFile(repo, f2);
    assert(getCreationYear(repo->data->elements[0]) == 355);
    File* f3 = createFile(33, "med", "pdf", 420);
    repo_addFile(repo, f3);
    saveOperation(repo, "delete", deepcopyFile(f3));
    repo_deleteFile(repo, 33);
    assert(getAll(repo).len == 1);
    assert(checkExisting(repo, 33) == 0);
    assert(undoLastOperation(repo) == 1);
    assert(undoLastOperation(repo) == 0);
    assert(checkExisting(repo, 33) == 1);
    assert(getAll(repo).len == 2);
    sort_desc_year(repo);
    assert(getCreationYear(repo->data->elements[0]) == 420);
    assert(getCreationYear(repo->data->elements[1]) == 355);
    assert(redoLastOperation(repo) == 1);
    assert(redoLastOperation(repo) == 0);
    assert(getAll(repo).len == 1);
    assert(checkExisting(repo, 33) == 0);
    destroyRepository(repo);
}

void testController()
{
    Repository* r = createRepo();
    Controller* c = createController(r);
    assert(srv_addFile(c, 1, "e", "e2", 44) == 1);
    assert(getArchive(c).len == 1);
    assert(srv_addFile(c, 2, "k", "kt", 55) == 1);
    assert(getArchive(c).len == 2); // this automatically sorts the files descending by year
    assert(srv_undo(c) == 1);
    assert(getArchive(c).len == 1);
    assert(getID(getArchive(c).elements[0]) == 1);
    assert(srv_redo(c) == 1);
    assert(getArchive(c).len == 2);
    assert(getID(getArchive(c).elements[0]) == 2);
    assert(srv_updateFile(c, 2, "new", "new2", 66) == 1);
    assert(srv_updateFile(c, 3, "new", "new2", 66) == 0);
    DynamicVector* v1 = filter_year(c, 44);
    assert(v1->len == 0);
    free(v1->elements);
    free(v1);
    DynamicVector* v2 = filter_year(c, 45);
    assert(v2->len == 1);
    free(v2->elements);
    free(v2);
    assert(srv_deleteFile(c, 1) == 1);
    assert(getArchive(c).len == 1);
    assert(getID(getArchive(c).elements[0]) == 2);
    destroyController(c);
    destroyRepository(r);
}

void runAllTests()
{
    testFile();
    testFilesDynamicVector();
    testVectorsDynamicVector();
    testRepository();
    testController();
    _CrtDumpMemoryLeaks();
}