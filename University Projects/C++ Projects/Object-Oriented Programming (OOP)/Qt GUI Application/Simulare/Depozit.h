#pragma once

#include "Produs.h"
#include <vector>

class Depozit
{
private:
	vector<Produs> produse;
	string fileName;

public:
	Depozit(string fileName) : fileName{ fileName } 
	{
		loadFromFile();
	}

	/// Functie care incarca datele din fisier
	void loadFromFile();

	/// Functie care returneaza vectorul de produse
	/// @return vectorul de produse
	vector<Produs> getProduse();

	///	Functie care returneaza vectorul de produse filtrat dupa 'cod'
	/// @param cod este codul dupa care se face filtrarea
	/// @return vectorul de produse filtrat
	vector<Produs> filterByCod(int cod);

	///	Functie care returneaza vectorul de produse filtrat dupa 'brand'
	/// @param brand este brand-ul dupa care se face filtrarea
	/// @return vectorul de produse filtrat
	vector<Produs> filterByBrand(string brand);
};

