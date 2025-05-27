#include "Magazin.h"

#include <fstream>
#include <sstream>
#include <algorithm>

void Magazin::adaugaRochii()
{
	listaRochii.clear();
	ifstream fin(numeFisier);
	while (fin)
	{
		string line;
		getline(fin, line);
		if (line.empty())
			break;
		stringstream ss(line);
		int cod_unic;
		string cod_unic_string, denumire, marime, pret_string, disponibilitate_string;
		double pret;
		bool disponibilitate;
		getline(ss, cod_unic_string, ',');
		getline(ss, denumire, ',');
		getline(ss, marime, ',');
		getline(ss, pret_string, ',');
		getline(ss, disponibilitate_string, ',');
		cod_unic = stoi(cod_unic_string);
		pret = stod(pret_string);
		disponibilitate = (disponibilitate_string == "True");
		Rochie r(cod_unic, denumire, marime, pret, disponibilitate);
		listaRochii.push_back(r);
	}
	fin.close();
}

vector<Rochie>& Magazin::getListaRochii()
{
	return listaRochii;
}

vector<Rochie>& Magazin::sortareDupaMarime()
{
	sort(listaRochii.begin(), listaRochii.end(), [](const Rochie& r1, const Rochie& r2) {
		return r1.getMarime() < r2.getMarime();
		});
	return listaRochii;
}

vector<Rochie>& Magazin::sortareDupaPret()
{
	sort(listaRochii.begin(), listaRochii.end(), [](const Rochie& r1, const Rochie& r2) {
		return r1.getPret() < r2.getPret();
		});
	return listaRochii;
}