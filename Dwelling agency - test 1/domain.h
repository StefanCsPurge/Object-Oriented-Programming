#pragma once
#include <string>
using namespace std;


class Dwelling
{
private:
	string type;
	double price;
	bool isProfitable;
public:
	Dwelling(string t, double pr, bool profi) : type(t), price(pr), isProfitable(profi) {}
	string getType() { return type; }
	bool getProfitable() { return isProfitable; }
	double normalBankRate() { return price / 1000.0; }
	double largeBankRate() { return price / 100.0; }
	string getString() { return type + " " + to_string(price) + " " + to_string(isProfitable); }
};

class Client
{
protected:
	string name;
	double sal;
	
public:
	string getName() { return name; }
	bool operator==(const Client& v) { return this->name == v.name; }
	bool operator!=(const Client& v) { return this->name != v.name; }
	virtual double totalIncome() { return sal; }
	virtual string getString() const = 0;
	virtual bool isInterested(Dwelling&) =0;
	virtual ~Client() {}
};

class NormalClient : public Client
{
private:
public:
	NormalClient(const string& name,double salary);
	//friend istream& operator>>(std::istream& is, Dent& h);
	//friend ostream& operator<<(std::ostream& os, const Dent& h);
	bool isInterested(Dwelling& d) override;
	string getString() const override;
};

class WealthyClient : public Client
{
private:
	double moneyFromInvestments;
public:
	WealthyClient(const string& name, double salary, double investMoney);
	double totalIncome() override { return sal + moneyFromInvestments; }
	//friend istream& operator>>(std::istream& is, Dent& h);
	//friend ostream& operator<<(std::ostream& os, const Dent& h);
	bool isInterested(Dwelling& d) override;
	string getString() const override;
};