#pragma once

#include "Activitate.h"
#include "BaseException.h"
#include "RepositoryAbstract.h"
#include <vector>

class RepoException : public BaseException
{
public:
	explicit RepoException(string msg) : BaseException(msg) {}
};

class Repository : public RepositoryAbstract
{
private:
	vector<Activitate> listaActivitati;

public:
	Repository(const Repository& ot) = delete;
	Repository() = default;

	/// Functie care adauga o activitate in repository
	/// @param activity este activitatea care urmeaza sa fie adaugata
	/// @returns True (daca activitatea a fost adaugata cu succes)
	/// @throws RepoException cu mesajul "Activitatea exista deja in lista ta!" 
	/// (activitatea exista deja in repository)
	bool addActivitate(const Activitate& activity) override;

	/// Functie care sterge o activitate din repository
	/// @param index este pozitia activitatii care urmeaza sa fie stearsa
	void deleteActivitateByIndex(const int& index) override;

	/// Functie care modifica o activitate din repository cu alta
	/// @param index este pozitia activitatii care urmeaza sa fie modificata
	/// @param newActivity este noua activitate
	/// @returns True (daca activitatea a fost modificata cu succes)
	/// @throws RepoException cu mesajul "Activitatea exista deja in lista ta!"
	/// (noua activitate e aceeasi cu una deja existenta)
	bool modifyActivitateByIndex(const int& index, const Activitate& newActivity) override;

	/// Functie care returneaza activitatea de pe pozitia index din repository
	/// @param index este pozitia activitatii
	/// @returns Activitatea
	Activitate getActivitateByIndex(const int& index) const override;

	/// Functie care returneaza lista de activitati
	/// @returns Lista de activitati
	const vector<Activitate>& getActivitati() const override;
};