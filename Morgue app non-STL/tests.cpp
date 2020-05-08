#include "tests.h"

void testVictim()
{
	Victim v{ "name1","origin",10,"ph.png" };
	assert(v.getName() == "name1");
	assert(v.getPlaceOfOrigin() == "origin");
	assert(v.getPhoto() == "ph.png");
	assert(v.getAge() == 10);
	assert(v.toString().size() > 0);
}

void testRepository()
{
	Repository repo;
	Victim v1{ "name1","origin",10,"ph.png" };
	Victim v2{ "name2","origin",10,"ph.png" };
	repo.addVictim(v1);
	assert(repo.getVictims().getSize() == 1);
	assert(repo.getVictims()[0].getName() == v1.getName());
	repo.addVictim(v2);
	assert(repo.getVictims().getSize() == 2);
	Victim v3{ "name2","newOrigin",20,"ph2.png" };
	repo.updateVictim(v3);
	assert(repo.getVictims()[1].getAge() == 20);
	assert(repo.getVictimPosition("name2") == 1);
	repo.deleteVictim("name1");
	assert(repo.getVictims().getSize() == 1);
	assert(repo.getVictims()[0].getName() == "name2");
	Victim v4 = repo.getNextVictim();
	assert(v4.getName() == "name2");
	assert(repo.getNextVictim().getName() == v4.getName());
	assert(repo.getAssistantVictims().getSize() == 0);
	repo.assistantTransferVictim(v4);
	assert(repo.getVictims().getSize() == 0);
	assert(repo.getAssistantVictims().getSize() == 1);
	assert(repo.getAssistantVictims()[0].getName() == "name2");
}


void testService()
{
	Repository repo;
	Service srv{ repo };
	assert(srv.addVictimToRepo("name1", "origin", 10, "ph.png") == 1);
	assert(srv.addVictimToRepo("name1", "origin", 10, "ph.png") == 0);
	assert(srv.getAllVictims()[0].getName() == "name1");
	srv.addVictimToRepo("name2", "origin2", 20, "ph2.png");
	assert(srv.getAllVictims().getSize() == 2);
	srv.updateVictim("name2", "o22", 33, "p22.jgp");
	assert(srv.updateVictim("badName", "o22", 33, "p22.jgp") == 0);
	assert(srv.getAllVictims()[1].getAge() == 33);
	assert(srv.deleteVictim("badName") == 0);
	srv.deleteVictim("name1");
	assert(srv.getAllVictims().getSize() == 1);
	assert(srv.getAllVictims()[0].getName() == "name2");
	assert(srv.filterVictims("", 22).getSize() == 0);
	assert(srv.filterVictims("o22", 44).getSize() == 1);
	srv.nextVictim();
	assert(srv.getCurrentVictim().getName() == "name2");
	assert(srv.moveVictimToAssistantList("badname") == 0);
	assert(srv.moveVictimToAssistantList("name2") == 1);
	assert(srv.getAssistantVictims().getSize() == 1);
	assert(srv.getAllVictims().getSize() == 0);
	srv.addEntries();
	assert(srv.getAllVictims().getSize() == 10);
}

void testDynamicVector()
{
	DynamicVector<int> a;
	a.add(1);
	a.add(2);
	assert(a.getSize() == 2);
	assert(a[0] == 1);
	a[1] = 999;
	assert(a[1] == 999);
	DynamicVector<int> b;
	a = a;
	b = a;
	a.deletePosition(0);
	assert(a[0] == 999);
	assert(b.getSize() == 2);
	assert(b[0] == 1);

	// test iterator
	DynamicVector<int>::Iterator it = b.begin();
	assert(*it == 1);
	assert(it != b.end());
	++it;
	assert(*it == 999);
	b.add(30);
	it++;
	assert(*it == 30);
	++it;
}

void testAll()
{
	testVictim();
	testRepository();
	testService();
	testDynamicVector();
	_CrtDumpMemoryLeaks();
}
