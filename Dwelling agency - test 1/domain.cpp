#include "domain.h"
#include <iostream>

NormalClient::NormalClient(const string& name, double salary)
{
	this->name = name;
	this->sal = salary;
}

/*
istream& operator>>(istream& is, Dent& h)
{
	cout << "ID: ";
	is >> h.ID;
	return is;
}

ostream& operator<<(ostream& os, const Dent& h)
{
	os << "ID: " << h.ID << "\n";
	return os;
}
*/
string NormalClient::getString() const
{
	return "Name: " + name + " - Salary: "+ to_string(sal) + "\n";
}

bool NormalClient::isInterested(Dwelling& d)
{
	return d.normalBankRate() <= this->totalIncome();
}

WealthyClient::WealthyClient(const string& name, double salary, double im)
{
	this->name = name;
	this->sal = salary;
	this->moneyFromInvestments = im;
}

string WealthyClient::getString() const
{
	return "Name: " + name + " - Salary: " + to_string(sal) + " - Total income: " + to_string(sal + moneyFromInvestments) + "\n";
}

bool WealthyClient::isInterested(Dwelling& d)
{
	return d.largeBankRate() <= this->totalIncome() && d.getProfitable();
}