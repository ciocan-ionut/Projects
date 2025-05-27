#include "Repository.h"

bool Repository::addActivitate(const Activitate& activity)
{
	for (const auto& a : listaActivitati)
		if (a == activity)
			throw RepoException("Activitatea exista deja in lista ta!\n");
	listaActivitati.push_back(activity);
	return true;
}

void Repository::deleteActivitateByIndex(const int& index)
{
	listaActivitati.erase(listaActivitati.begin() + index);
}

bool Repository::modifyActivitateByIndex(const int& index, const Activitate& newActivity)
{
	for (const auto& a : listaActivitati)
		if (a == newActivity)
			throw RepoException("Activitatea exista deja in lista ta!\n");
	listaActivitati.erase(listaActivitati.begin() + index);
	if (listaActivitati.size() == 0)
		listaActivitati.push_back(newActivity);
	else
		listaActivitati.insert(listaActivitati.begin() + index, newActivity);
	return true;
}

Activitate Repository::getActivitateByIndex(const int& index) const
{
	return listaActivitati[index];
}

const vector<Activitate>& Repository::getActivitati() const
{
	return listaActivitati;
}