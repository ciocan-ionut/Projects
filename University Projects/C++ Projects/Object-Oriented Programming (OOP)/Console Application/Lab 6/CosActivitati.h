#pragma once

#include "Activitate.h"
#include <vector>

using namespace std;

class CosActivitati
{
private:
	vector<Activitate> cos;

public:
	CosActivitati() = default;

	/// Functie care sterge toate activitatile din cos
	void deleteCos();

	/// Functie care adauga o activitate in cos
	/// @param a este activitatea care urmeaza sa fie adaugata
	void addActivitateInCos(const Activitate& a);

	/// Functie care exporta cosul intr-un fisier CSV
	/// @param numeFisier este numele fisierului in care se va exporta cosul
	void exportCSV(const string& numeFisier) const;

	/// Functie care returneaza cosul cu activitati
	/// @returns cosul cu activitati
	const vector<Activitate>& getActivitatiCos() const;
};

