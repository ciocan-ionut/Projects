#pragma once

#include "Activitate.h"
#include "BaseException.h"
#include <vector>
#include <random>

using namespace std;

class RepoRandomException : public BaseException
{
public:
	explicit RepoRandomException(string msg) : BaseException(msg) {}
};

class RepositoryAbstract
{
private:
	vector<Activitate> listaActivitati;

public:
	RepositoryAbstract() = default;
	RepositoryAbstract(const RepositoryAbstract& ot) = delete;

	/// Functie care adauga o activitate in repository
	/// @param a este activitatea care trebuie adaugata
	virtual bool addActivitate(const Activitate& a) = 0;

	/// Functie care sterge o activitate din repository
	/// @param index este pozitia activitatii care urmeaza sa fie stearsa
	virtual void deleteActivitateByIndex(const int& index) = 0;

	/// Functie care modifica o activitate din repository cu alta
	/// @param index este pozitia activitatii care urmeaza sa fie modificata
	/// @param newActivity este noua activitate
	/// @returns True (daca activitatea a fost modificata cu succes)
	/// @throws RepoException cu mesajul "Activitatea exista deja in lista ta!"
	/// (noua activitate e aceeasi cu una deja existenta)
	virtual bool modifyActivitateByIndex(const int& index, const Activitate& newActivity) = 0;

	/// Functie care returneaza activitatea de pe pozitia index din repository
	/// @param index este pozitia activitatii
	/// @returns Activitatea
	virtual Activitate getActivitateByIndex(const int& index) const = 0;

	/// Functie care returneaza toate activitatile din repository
	/// @returns vector de activitati
	virtual const vector<Activitate>& getActivitati() const = 0;

	virtual ~RepositoryAbstract() = default;
};

class RepositoryRandom : public RepositoryAbstract
{
private:
	vector<Activitate> listaActivitati;
	mutable default_random_engine generator{ random_device{}() };
	mutable uniform_real_distribution<double> unif{ 0.0, 2.0 };

public:
	RepositoryRandom() = default;

	/// Functie care adauga o activitate in repository
	/// @param a este activitatea care trebuie adaugata
	bool addActivitate(const Activitate& activity) override
	{
		if (unif(generator) < 1.0)
			throw RepoRandomException("Random exception occurred!");
		for (const auto& a : listaActivitati)
			if (a == activity)
				throw RepoRandomException("Activitatea exista deja in lista ta!\n");
		listaActivitati.push_back(activity);
		return true;
	}

	const vector<Activitate>& getActivitati() const override
	{
		if (unif(generator) < 1.0)
			throw RepoRandomException("Random exception occurred!");
		return listaActivitati;
	}

	void deleteActivitateByIndex(const int& index) override
	{
		if (unif(generator) < 1.0)
			throw RepoRandomException("Random exception occurred!");
		listaActivitati.erase(listaActivitati.begin() + index);
	}

	bool modifyActivitateByIndex(const int& index, const Activitate& newActivity) override
	{
		if (unif(generator) < 1.0)
			throw RepoRandomException("Random exception occurred!");
		for (const auto& a : listaActivitati)
			if (a == newActivity)
				throw RepoRandomException("Activitatea exista deja in lista ta!\n");
		listaActivitati.erase(listaActivitati.begin() + index);
		if (listaActivitati.size() == 0)
			listaActivitati.push_back(newActivity);
		else
			listaActivitati.insert(listaActivitati.begin() + index, newActivity);
		return true;
	}

	Activitate getActivitateByIndex(const int& index) const override
	{
		if (unif(generator) < 1.0)
			throw RepoRandomException("Random exception occurred!");
		return listaActivitati[index];
	}
};