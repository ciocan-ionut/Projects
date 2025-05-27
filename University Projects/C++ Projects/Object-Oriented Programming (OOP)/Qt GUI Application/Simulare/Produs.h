#pragma once

#include <string>

using namespace std;

class Produs
{
private:
	int cod;
	string tip, brand;
	double consumEnergetic;

public:
	Produs(int cod, string tip, string brand, double consum) : cod{ cod }, tip{ tip }, brand{ brand }, consumEnergetic{ consum } {}
	
	/// Functie care returneaza codul unui produs
	/// @return codul unui produs
	int getCod() const;

	/// Functie care returneaza tipul unui produs
	/// @return tipul unui produs
	string getTip() const;

	/// Functie care returneaza brand-ul unui produs
	/// @return brand-ul unui produs
	string getBrand() const;

	/// Functie care returneaza consumul unui produs
	/// @return consumul unui produs
	double getConsum() const;
};

