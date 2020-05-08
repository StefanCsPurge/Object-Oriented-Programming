#include "service.h"
#include <algorithm>
#include <fstream>
using namespace std;


void Service::addNCl(string& name, double sal) {
	Client* c = new NormalClient{name,sal };
	repo.addC(c);
}

void Service::addWCl(string& name, double sal, double inv) {
	Client* c = new WealthyClient{ name,sal,inv };
	repo.addC(c);
}

void Service::addDw(string& type, double price,bool profitable) {
	Dwelling d{ type,price,profitable };
	repo.addD(d);
}

vector<Client*> Service::getAllDwType(string& type)
{
	vector<Client*> newv, v = repo.getAllCl();
	vector<Dwelling> dlist = repo.getAllDw();
	for (Client* cl : v)
		for (Dwelling d : dlist)
			if (d.getType() == type && cl->isInterested(d))
			{
				newv.push_back(cl);
				break;
			}
	//auto good = [&](auto a) {return a.getType() == type; };
	//copy_if(v.begin(), v.end(), back_inserter(newv), good);
	return newv;
}

void Service::saveClToFile(string& file)
{
	vector<Client*> v = repo.getAllCl();
	ofstream fout(file);
	for_each(v.begin(), v.end(), [&](auto a) {fout << a->getString(); });
}