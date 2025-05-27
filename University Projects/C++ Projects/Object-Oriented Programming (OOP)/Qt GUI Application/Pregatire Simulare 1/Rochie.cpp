#include "Rochie.h"

#include <sstream>
#include <iomanip>

Rochie::Rochie(int cod_unic, string denumire, string marime, double pret, bool disponibilitate)
	: cod_unic(cod_unic), denumire(denumire), marime(marime), pret(pret), disponibilitate(disponibilitate) {}

int Rochie::getCodUnic() const {
	return cod_unic;
}

string Rochie::getDenumire() const {
	return denumire;
}

string Rochie::getMarime() const {
	return marime;
}

double Rochie::getPret() const {
	return pret;
}

bool Rochie::getDisponibilitate() const {
	return disponibilitate;
}

void Rochie::setDisponibilitate() {
	disponibilitate = !disponibilitate;
}

string Rochie::toString() const
{
	return to_string(cod_unic) + " " + denumire + " " + marime + " " + to_string(pret);
}