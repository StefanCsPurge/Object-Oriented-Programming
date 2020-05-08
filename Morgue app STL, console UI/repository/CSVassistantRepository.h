#pragma once
#include "repository.h"


class CSVassistantRepo : public AssistantRepository
{
private:
	void writeVictimsToFile() const override;

public:
	CSVassistantRepo(string filePath = "");
	void addVictim(const Victim& v) override;
	void openInApplication() override;
	~CSVassistantRepo() {}
};