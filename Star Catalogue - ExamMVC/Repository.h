#pragma once
#include "domain.h"
#include <vector>

class Repository
{
private:
	string aFile, sFile;
	vector<Astronomer> astron;
	vector<Star> stars;

public:
	Repository(const string& w = "", const string i = "") : aFile(w), sFile(i) {
		if (aFile.size()) loadAFromFile();
		if (sFile.size()) loadSFromFile();
	}

	void loadAFromFile();
	vector<Astronomer> getAstronomers() { return astron; }
	void loadSFromFile();
	vector<Star> getStars() { return stars; }
	string getStarsFile() const { return sFile; }

	//void writeQuestionsToFile();
	//void writeParticipantsToFile();

	/// <summary>
	/// Method which adds an unique idea to the list
	/// </summary>
	/// <param name="i"> Object of type Idea </param>
	void addStar(Star& i);

	/// <summary>
	/// Method which updates an idea's status
	/// </summary>
	/// <param name="i"> Object of type Idea </param>
	/// <param name="status"> string - the new status </param>
	void updateIdeaStatus(Star& i, const string& status);

	void addWriter(Astronomer& w);

	~Repository() {
	}

};

