#pragma once
#include "repository.h"

class Service
{
private:
	Repository& repo;
	Victim currentVictim;

public:
	Service(Repository& r) : repo(r) {}

	DynamicVector<Victim> getAllVictims() const;
	
	// Adds some entries for testing purposes
	void addEntries();
	
	/// Adds a victim with the given data to the repository.
	int addVictimToRepo(const string& name, const string& placeOfOrigin,int age, const string& photo);

	/// Updates a victim with the given data.
	int updateVictim(const string& name, const string& newPlaceOfOrigin, int newAge, const string& newPhoto);

	/// Deletes the victim with a given name.
	int deleteVictim(const string& name);

	/// Gets the next victim for the assistant.
	void nextVictim();

	/// Gets the current victim for the assistant.
	Victim getCurrentVictim();

	/// Moves a victim to the assistant's "to be transferred" list
	int moveVictimToAssistantList(const string& name);

	DynamicVector<Victim> getAssistantVictims() const;

	/// Selects the victims from a given placeOfOrigin that have the age less than a given age
	DynamicVector<Victim> filterVictims(const string& placeOfOrigin, int age) const;
};