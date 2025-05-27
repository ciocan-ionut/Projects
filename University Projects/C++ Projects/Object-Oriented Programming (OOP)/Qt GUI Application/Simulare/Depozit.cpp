#include "Depozit.h"
#include <fstream>
#include <sstream>
#include <algorithm>

void Depozit::loadFromFile()
{
	produse.clear();
	ifstream fin(fileName);
	while (fin)
	{
		string line;
		getline(fin, line);
		if (line.empty())
			break;
		stringstream ss(line);
		string codString, tip, brand, consumString;
		getline(ss, codString, ',');
		getline(ss, tip, ',');
		getline(ss, brand, ',');
		getline(ss, consumString, ',');
		int cod = stoi(codString);
		double consum = stod(consumString);
		Produs p{ cod, tip, brand, consum };
		produse.push_back(p);
	}
	fin.close();
}

vector<Produs> Depozit::filterByCod(int cod)
{
	vector<Produs> produseFiltrate;
	for (const auto& p : produse)
		if (p.getCod() == cod)
			produseFiltrate.push_back(p);
	return produseFiltrate;
}

vector<Produs> Depozit::filterByBrand(string brand)
{
	vector<Produs> produseFiltrate;
	for (const auto& p : produse)
		if (p.getBrand() == brand)
			produseFiltrate.push_back(p);
	return produseFiltrate;
}

vector<Produs> Depozit::getProduse()
{
	return produse;
}