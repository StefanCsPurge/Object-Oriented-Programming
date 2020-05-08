#pragma once
#include "../domain/victim.h"
#include "../exceptions/exceptions.h"
#include <vector>
#include <fstream>


class Repository
{
protected:
	string victimsFile;
	int iterPos;
	vector<Victim> loadVictimsFromFile();
	void writeVictimsToFile(vector<Victim>);

public:
	///Default constructor
	Repository() : iterPos(0), victimsFile("") {}

	void setVictimsFile(const string& filePath);

	virtual Victim getVictim(const string& name);

	/*	Adds a victim to the repository.
		Input: v - Victim
		Output: the victim is added to the repository */
	virtual void addVictim(const Victim& v);

	/*	Updates a victim in the repository.
		Input: newVictim - Victim
		Output: the victim is updated in the repository */
	virtual void updateVictim(const Victim& newVictim);

	/*	Deletes a victim from the repository.
		Input: name - string (the name of the victim to remove)
		Output: the victim is eliminated from the repository */
	virtual void deleteVictim(const Victim& v);

	/// Gets an immutable DynamicVector with all the victims
	virtual vector<Victim> getVictims() { return this->loadVictimsFromFile(); }

	/// Iterate through the victims
	virtual Victim getNextVictim();
};


/// Default txt class for the assistant repository
class AssistantRepository
{
protected:
	string file;
	vector<Victim> assistantVictims;
	virtual void writeVictimsToFile() const;

public:
	AssistantRepository(string filePath = "");

	/// Gets an immutable DynamicVector with all the victims saved by the assistant
	vector<Victim> getVictims() const { return this->assistantVictims; }

	/*	Adds a victim to the repository.
		Input: v - Victim
		Output: the victim is added to the repository */
	virtual void addVictim(const Victim& v);

	virtual void openInApplication();

	virtual ~AssistantRepository() {}
};
