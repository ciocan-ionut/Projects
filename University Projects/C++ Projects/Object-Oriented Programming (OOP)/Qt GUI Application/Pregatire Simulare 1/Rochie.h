#pragma once

#include <string>

using namespace std;

class Rochie
{
private:
	int cod_unic;
	string denumire, marime;
	double pret;
	bool disponibilitate;

public:
	Rochie(int cod_unic, string denumire, string marime, double pret, bool disponibilitate);
	int getCodUnic() const;
	string getDenumire() const;
	string getMarime() const;
	double getPret() const;
	bool getDisponibilitate() const;
	void setDisponibilitate();
	string toString() const;
};

