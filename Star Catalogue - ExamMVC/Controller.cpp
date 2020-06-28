#include "Controller.h"
#include <fstream>

void Controller::updateModel()
{
	this->model->update();
}

/*
Method that adds a star to the repository
Input: name, c - constellation (strings), RA, D (int) - coordinates of the star, diam (int) - diameter of the star
Output: - ; the mothod adds the newly created star to the repository
Throws: exception if star is invalid
*/
void Controller::addStar(const string& name, const string& c, int RA, int D, int diam)
{
	if (name == "" || diam <= 0)
		throw exception("Invalid star!");
	this->repo.addStar(Star(name, c, RA, D, diam));
	this->model->update();
}


vector<Star> Controller::filterStars(const string& str)
{
	vector<Star> all = this->repo.getStars();
	vector<Star> newS;
	auto good = [&](Star& e)->bool {return str_tolower(e.getName()).find(str_tolower(str)) != std::string::npos; };
	copy_if(all .begin(), all.end(), back_inserter(newS), good);
	return newS;
}

vector<Star> Controller::getConstellationsStars(const string& cs)
{
	vector<Star> all = this->repo.getStars();
	vector<Star> newS;
	auto good = [&](Star& e)->bool {return e.getConstellation() == cs; };
	copy_if(all.begin(), all.end(), back_inserter(newS), good);
	return newS;
}

string Controller::str_tolower(string s) {
	std::transform(s.begin(), s.end(), s.begin(), [](unsigned char c) { return std::tolower(c); });
	return s;
}

void Controller::saveSortedStars()
{
	ofstream fout(repo.getStarsFile());
	auto allStars = this->repo.getStars();
	auto sortFct = [](const Star& i1, const Star& i2) {return i1.getConstellation() < i2.getConstellation(); };
	sort(allStars.begin(), allStars.end(), sortFct);
	for (auto star : allStars)
		fout << star;
	fout.close();
}


