#pragma once
#include "victim.h"
#include "DynamicVector.h"

class Repository
{
private:
	DynamicVector<Victim> victims;
	DynamicVector<Victim>::Iterator it;
	DynamicVector<Victim> assistantVictims;

public:
	///Default constructor
	Repository() {}
	
	/*	Checks if there already exists a victim with a given name.
		Input: name - string
		Output: true/false */
	int getVictimPosition(const string name);


	/*	Adds a victim to the repository.
		Input: v - Victim
		Output: the victim is added to the repository */
	void addVictim(const Victim& v);

	/*	Updates a victim in the repository.
		Input: newVictim - Victim
		Output: the victim is updated in the repository */
	void updateVictim(const Victim& newVictim);

	/*	Deletes a victim from the repository.
		Input: name - string (the name of the victim to remove)
		Output: the victim is eliminated from the repository */
	void deleteVictim(const string& name);

	/// Gets an immutable DynamicVector with all the victims
	DynamicVector<Victim> getVictims() const { return this->victims; }

	/// Gets an immutable DynamicVector with all the victims saved by the assistant
	DynamicVector<Victim> getAssistantVictims() const { return this->assistantVictims; }

	/// Iterate through the victims
	Victim getNextVictim();

	/// Transfers a victim to the assistant's list
	void assistantTransferVictim(const Victim v);
};