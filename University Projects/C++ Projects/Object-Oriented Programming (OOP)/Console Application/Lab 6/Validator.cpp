#include "Validator.h"

bool Validator::validateActivitate(const Activitate& activity)
{
	string errorMessage = "";
	if (activity.getTitlu() == "")
		errorMessage += "Nu ati introdus niciun titlu!\n";
	if (activity.getDescriere() == "")
		errorMessage += "Nu ati introdus nicio descriere!\n";
	if (activity.getTip() == "")
		errorMessage += "Nu ati introdus niciun tip!\n";
	if (activity.getDurata() <= 0)
		errorMessage += "Durata trebuie sa fie un numar strict pozitiv!\n";
	if (errorMessage != "")
		throw ValidatorException(errorMessage);
	return true;
}

bool Validator::validateString(const string& string)
{
	if (string == "")
		throw ValidatorException("Nu ati introdus nimic!\n");
	return true;
}