#include "MYSQLrepository.h"


MYSQLRepository::MYSQLRepository()
{
	try {
		driver = get_driver_instance();
		connection = driver->connect("tcp://127.0.0.1:3306", "root", "password");
		connection->setSchema("victims");
	}
	catch (exception& e)
	{
		cout << e.what() << endl;
		exit(1);
	}
}

vector<Victim> MYSQLRepository::getVictimsFromDatabase()
{
	sql::Statement* statement = connection->createStatement();
	sql::ResultSet* resultSet = statement->executeQuery("SELECT * FROM victims");
	vector<Victim> victimsVect;
	string name, placeOfOrigin, photo;
	int age;
	while (resultSet->next())
	{
		name = resultSet->getString(1);
		placeOfOrigin = resultSet->getString(2);
		age = resultSet->getInt(3);
		photo = resultSet->getString(4);
		victimsVect.push_back(Victim{ name,placeOfOrigin,age,photo });
	}
	delete resultSet;
	delete statement;
	return victimsVect;
}

Victim MYSQLRepository::getVictim(const string& name)
{
	Victim v(name, "", 0, "");
	auto victims = getVictimsFromDatabase();
	auto it = find(victims.begin(), victims.end(), v);
	if (it == victims.end())
		throw RepositoryException("There is no victim with this name!");
	return *it;
}

void MYSQLRepository::addVictim(const Victim& v)
{
	auto victims = getVictimsFromDatabase();
	auto it = find(victims.begin(), victims.end(), v);
	if (it != victims.end())
		throw RepositoryException("There already exists a victim with this name!");
	sql::PreparedStatement* preparedStatement;
	preparedStatement = connection->prepareStatement("INSERT INTO victims VALUES (?, ?, ?, ?)");
	preparedStatement->setString(1, v.getName());
	preparedStatement->setString(2, v.getPlaceOfOrigin());
	preparedStatement->setInt(3, v.getAge());
	preparedStatement->setString(4, v.getPhoto());
	preparedStatement->execute();
	delete preparedStatement;
}

void MYSQLRepository::updateVictim(const Victim& newVictim)
{
	auto victims = getVictimsFromDatabase();
	auto it = find(victims.begin(), victims.end(), newVictim);
	if (it == victims.end())
		throw RepositoryException("There is no victim with this name!");
	sql::PreparedStatement* pStatement = connection->prepareStatement("UPDATE victims SET name = ?, placeOfOrigin = ?, age = ?, photo = ? WHERE name = ? ");
	pStatement->setString(1, newVictim.getName());
	pStatement->setString(2, newVictim.getPlaceOfOrigin());
	pStatement->setInt(3, newVictim.getAge());
	pStatement->setString(4, newVictim.getPhoto());
	pStatement->setString(5, newVictim.getName());
	pStatement->execute();
	delete pStatement;
}

void MYSQLRepository::deleteVictim(const Victim& v)
{
	sql::PreparedStatement* preparedStatement;
	preparedStatement = connection->prepareStatement("DELETE FROM victims WHERE name=?");
	preparedStatement->setString(1,v.getName());
	preparedStatement->execute();
	delete preparedStatement;
}

Victim MYSQLRepository::getNextVictim()
{
	auto victims = getVictimsFromDatabase();
	if (!victims.size())
		throw RepositoryException("There are no victims!");
	if (this->iterPos == victims.size())
		this->iterPos = 0;
	Victim v = victims[iterPos];
	this->iterPos++;
	return v;
}