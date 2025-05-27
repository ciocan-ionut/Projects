#pragma once

#include "Joc.h"
#include <vector>

class Jocuri
{
private:
	vector<Joc> jocuri;
	string numeFisier;

public:
	Jocuri(string numeFisier) : numeFisier{ numeFisier } 
	{
		loadFromFile();
	}
	void loadFromFile();
	vector<Joc> getJocuri();
	vector<Joc> sortJocuri();
	vector<Joc> filterJocuri();
};

