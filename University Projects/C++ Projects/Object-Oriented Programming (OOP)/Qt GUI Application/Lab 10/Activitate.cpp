#include "Activitate.h"

string Activitate::getTitlu() const
{
	return titlu;
}

string Activitate::getDescriere() const
{
	return descriere;
}

string Activitate::getTip() const
{
	return tip;
}

int Activitate::getDurata() const
{
	return durata;
}

bool Activitate::compareTitlu(const Activitate& a, const Activitate& b, const bool& ascending)
{
	if (!ascending)
	{
		if (a.titlu > b.titlu)
			return true;
	}
	else
	{
		if (a.titlu < b.titlu)
			return true;
	}
	return false;
}

bool Activitate::compareDescriere(const Activitate& a, const Activitate& b, const bool& ascending)
{
	if (!ascending)
	{
		if (a.descriere > b.descriere)
			return true;
	}
	else
	{
		if (a.descriere < b.descriere)
			return true;
	}
	return false;
}

bool Activitate::compareTipSiDurata(const Activitate& a, const Activitate& b, const bool& ascending)
{
	if (!ascending)
	{
		if (a.tip > b.tip)
			return true;
		if (a.tip == b.tip && a.durata > b.durata)
			return true;
	}
	else
	{
		if (a.tip < b.tip)
			return true;
		if (a.tip == b.tip && a.durata < b.durata)
			return true;
	}
	return false;
}