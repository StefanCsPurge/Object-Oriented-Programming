#pragma once
#include "../repository/repository.h"
#include "../repository/MYSQLrepository.h"
#include "../repository/CSVassistantRepository.h"
#include "../repository/HTMLassistantRepository.h"
#include "../domain/victimValidator.h"
#include <algorithm>

class Service
{
private:
	Repository* repo;
	AssistantRepository* assistantRepo;
	Victim currentVictim;

public:
	Service(Repository* r): repo(r), assistantRepo(NULL) {}

	void setFile(const string& filePath);

	void createMylistRepo(const string& filePath,const string& extension);

	vector<Victim> getAllVictims() const;
	
	// Adds some entries for testing purposes
	void addEntries();
	
	/// Adds a victim with the given data to the repository.
	void addVictimToRepo(const string& name, const string& placeOfOrigin,int age, const string& photo);

	/// Updates a victim with the given data.
	void updateVictim(const string& name, const string& newPlaceOfOrigin, int newAge, const string& newPhoto);

	/// Deletes the victim with a given name.
	void deleteVictim(const string& name);

	/// Gets the next victim for the assistant.
	void nextVictim();

	/// Gets the current victim for the assistant.
	Victim getCurrentVictim();

	/// Moves a victim to the assistant's "to be transferred" list
	void moveVictimToAssistantList(const string& name);

	void showAssistantVictims() const;

	/// Selects the victims from a given placeOfOrigin that have the age less than a given age
	vector<Victim> filterVictims(const string& placeOfOrigin, int age) const;

	~Service() { delete assistantRepo; delete repo; }
};