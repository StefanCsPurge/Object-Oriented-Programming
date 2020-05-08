#pragma once

#include "repository.h"
#include <mysql.h>
#include <jdbc/cppconn/driver.h>
#include <jdbc/cppconn/exception.h>
#include <jdbc/cppconn/statement.h>
#include <jdbc/cppconn/prepared_statement.h>
#include <jdbc/cppconn/resultset.h>

using namespace std;

class MYSQLRepository : public Repository
{
private:
	sql::Driver* driver;
	sql::Connection* connection;
	vector<Victim> getVictimsFromDatabase();
public:
	MYSQLRepository();
	Victim getVictim(const string& name) override;
	void addVictim(const Victim& v) override;
	void updateVictim(const Victim& newVictim) override;
	void deleteVictim(const Victim& v) override;
	vector<Victim> getVictims() override { return getVictimsFromDatabase(); }
	Victim getNextVictim() override;
};