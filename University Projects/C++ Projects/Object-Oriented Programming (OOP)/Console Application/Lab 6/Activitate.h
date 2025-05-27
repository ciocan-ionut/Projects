#pragma once

#include <string>
#include <iostream>
using namespace std;

class Activitate
{
private:
	string titlu, descriere, tip;
	int durata = 0;

public:
	Activitate() = default;

	Activitate(const string& titlu, const string& descriere, const string& tip, const int& durata) :titlu{ titlu }, descriere{ descriere }, tip{ tip }, durata{ durata } {}

	Activitate(const Activitate& ot) : titlu { ot.titlu }, descriere{ ot.descriere }, tip{ ot.tip }, durata{ ot.durata }
	{
		//cout << "S-a copiat! ";
	}

	Activitate& operator=(const Activitate& ot) {
		if (this == &ot) return *this;
		titlu = ot.titlu;
		descriere = ot.descriere;
		tip = ot.tip;
		durata = ot.durata;
		return *this;
	}

	/// Functie care returneaza titlul unei activitati
	/// @returns Titlul activitatii
	string getTitlu() const;

	/// Functie care returneaza descrierea unei activitati
	/// @returns Descrierea activitatii
	string getDescriere() const;

	/// Functie care returneaza tipul unei activitati
	/// @returns Tipul activitatii
	string getTip() const;

	/// Functie care returneaza durata unei activitati
	/// @returns Durata activitatii
	int getDurata() const;

	/// Functie care suprascrie operatia de egalitate a doua activitati
	/// @param other este cealalta activitate
	/// @returns True (daca campurile sunt egale) / False (in caz contrar)
	bool operator==(const Activitate& other) const
	{
		return this->titlu == other.titlu && this->descriere == other.descriere && this->tip == other.tip && this->durata == other.durata;
	}

	/// Functie care suprascrie operatia de afisare a unei activitati
	/// pentru a permite afisarea detaliata a acesteia
	/// @param out este o referinta catre fluxul de iesire
	/// @param activity este activitatea care trebuie afisata
	/// @returns Referinta catre fluxul de iesire
	friend ostream& operator<<(ostream& out, const Activitate& activity)
	{
		out << "Titlu: " << activity.titlu << ", Descriere: " << activity.descriere << ", Tip: " << activity.tip << ", Durata: " << activity.durata << " minute";
		return out;
	}

	/// Functie care compara titlurile a doua activitati
	/// @param a prima activitate
	/// @param b a doua activitate
	/// @param ascending indica daca se sorteaza crescator sau descrescator
	/// @returns True (daca respecta conditia) / False (in caz contrar)
	bool static compareTitlu(const Activitate& a, const Activitate& b, const bool& ascending);

	/// Functie care compara descrierile a doua activitati
	/// @param a prima activitate
	/// @param b a doua activitate
	/// @param ascending indica daca se sorteaza crescator sau descrescator
	/// @returns True (daca respecta conditia) / False (in caz contrar)
	bool static compareDescriere(const Activitate& a, const Activitate& b, const bool& ascending);

	/// Functie care compara tipurile si durata a doua activitati
	/// @param a prima activitate
	/// @param b a doua activitate
	/// @param ascending indica daca se sorteaza crescator sau descrescator
	/// @returns True (daca respecta conditia) / False (in caz contrar)
	bool static compareTipSiDurata(const Activitate& a, const Activitate& b, const bool& ascending);
};

