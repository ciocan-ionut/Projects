#pragma once

#include <string>

using namespace std;

class Joc
{
private:
	string titlu, platforma;
	double pret;
	int rating;

public:
	Joc(string titlu, string platforma, double pret, int rating)
	{
		this->titlu = titlu;
		this->platforma = platforma;
		this->pret = pret;
		this->rating = rating;
	}
	string getTitlu() const { return titlu; }
	string getPlatforma() const { return platforma; }
	double getPret() const { return pret; }
	int getRating() const { return rating; }
};

