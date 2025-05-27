#pragma once

#include <vector>

#include "Rochie.h"

class Magazin
{
private:
	vector<Rochie> listaRochii;
	string numeFisier;

public:
	Magazin(string numeFisier) : numeFisier{ numeFisier }
	{
		adaugaRochii();
	}
	void adaugaRochii();
	vector<Rochie>& getListaRochii();
	vector<Rochie>& sortareDupaMarime();
	vector<Rochie>& sortareDupaPret();
};

