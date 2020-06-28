#pragma once
#include "Repository.h"
#include "TableModel.h"
using namespace std;


class Controller
{
private:
	Repository& repo;
	TableModel* model;
public:
	Controller(Repository& r, TableModel* m): repo(r), model(m) {}

	void updateModel();

	/*
	Method that adds a star to the repository
	Input: name, c - constellation (strings), RA, D (int) - coordinates of the star, diam (int) - diameter of the star
	Output: - ; the mothod adds the newly created star to the repository
	Throws: exception if star is invalid
	*/
	void addStar(const string& name, const string& c, int RA,int D,  int diam);

	vector<Star> filterStars(const string& str);

	vector<Star> getConstellationsStars(const string& cs);

	string str_tolower(string s);

	void saveSortedStars();

	~Controller() { saveSortedStars(); }
};

