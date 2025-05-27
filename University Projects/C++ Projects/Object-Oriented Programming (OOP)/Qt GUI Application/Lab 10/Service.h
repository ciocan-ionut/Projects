#pragma once

#include "RepositoryAbstract.h"
#include "Repository.h"
#include "Validator.h"
#include "BaseException.h"
#include "CosActivitati.h"
#include "ActiuneUndo.h"
#include "Observer.h"
#include "DTO.h"
#include <string>
#include <functional>
#include <algorithm>
#include <map>
using namespace std;

class ServiceException : public BaseException
{
public:
	explicit ServiceException(string msg) : BaseException(msg) {}
};

class Service : public Observable
{
private:
	RepositoryAbstract& repo;
	CosActivitati& cos;
	vector<unique_ptr<ActiuneUndo>> undoActions;

	map<string, DTO> raport;

public:
	Service(RepositoryAbstract& repo, CosActivitati& cos) : repo{ repo }, cos{ cos } {}
	Service(const Service& ot) = delete;

	/// Functie care creeaza, valideaza si adauga o activitate in service
	/// @param titlu este titlul activitatii
	/// @param descriere este descrierea activitatii
	/// @param tip este tipul activitatii
	/// @param durata este durata activitatii
	/// @returns True (daca toate operatiile au avut loc cu succes)
	/// @throws ValidatorException cu mesajele aferente
	/// @throws RepoException cu mesajul "Activitatea exista deja in lista ta!" 
	/// (activitatea exista deja in repository)
	bool addService(const string& titlu, const string& descriere, const string& tip, const int& durata);

	/// Functie care sterge o activitate din service
	/// @param index este pozitia activitatii din lista
	/// @returns True (daca operatia a avut loc cu succes)
	/// @throws ServiceException cu mesajul "Index invalid!" (se acceseaza o pozitie invalida)
	bool deleteService(const int& index);

	/// Functie care modifica o activitate din service
	/// @param index este pozitia activitatii din lista
	/// @param titlu este titlul activitatii
	/// @param descriere este descrierea activitatii
	/// @param tip este tipul activitatii
	/// @param durata este durata activitatii
	/// @returns True (daca operatia a avut loc cu succes)
	/// @throws ServiceException cu mesajul "Index invalid!" (se acceseaza o pozitie invalida)
	/// @throws RepoException cu mesajul "Activitatea exista deja in lista ta!"
	/// (noua activitate e aceeasi cu una deja existenta)
	bool modifyService(const int& index, string titlu, string descriere, string tip, int durata);

	/// Functie care returneaza lista de activitati din service
	/// @returns lista de activitati
	/// @throws ServiceException cu mesajul "Nu exista activitati in lista ta!"
	/// (lista de activitati este goala)
	const vector<Activitate>& getActivitatiService() const;

	/// Functie care returneaza lista de activitati care respecta un anumit criteriu
	/// @param getter este functia ca returneaza atributul dupa care se face filtrarea
	/// @param filtru este criteriul dupa care se face filtrarea
	/// @returns lista de activitati filtrata
	/// @throws ServiceException cu mesajul "Nu exista activitati care iti respecta criteriile!"
	/// (nu exista nicio activitate care sa respecte criteriul)
	/// @throw ValidatorException cu mesajul "Nu ati introdus nimic!" (string-ul este un sir gol)
	vector<Activitate> filterService(function<string(const Activitate&)> getter, const string& filtru) const;

	/// Functie care returneaza lista de activitati sortata dupa un anumit criteriu
	/// @param compare este functia pe baza careia se face compararea
	/// @param ascending indica daca sortarea se va face crescator sau descrescator
	/// @returns lista de activitati sortata
	vector<Activitate> sortedService(function<bool(const Activitate&, const Activitate&, const bool&)> compare, const bool& ascending) const;

	/// Functie care sterge toate activitatile din cos
	void emptyCos();

	/// Functie care adauga o activitate in cos dupa un anumit titlu
	/// @param titlu este titlul activitatii
	/// @throw ValidatorException cu mesajul "Nu ati introdus nimic!" (string-ul este un sir gol)
	/// @throw ServiceException cu mesajul "Nu exista activitate cu titlul dat!"
	/// (daca nicio activitate din lista nu are titlul dat)
	void addInCos(const string& titlu);

	/// Functie care genereaza activitati aleatoriu dintr-o lista de atribute prestabilite
	/// @param nr este numarul de activitati generate
	/// @throw ServiceException cu mesajul "Introduceti un numar strict pozitiv!"
	/// (daca numarul dat este mai mic sau egal cu 0)
	void generateActivitati(int nr);

	/// Functie care exporta cosul intr-un fisier CSV
	/// @param fisier este numele fisierului in care se va exporta cosul
	/// @throw ServiceException cu mesajul "Nu exista activitati in cosul tau!"
	/// (daca cosul cu activitati este gol)
	void exportCosCSV(const string& fisier) const;

	/// Functie care returneaza cosul cu activitati
	/// @returns cosul cu activitati
	/// @throw ServiceException cu mesajul "Nu exista activitati in cosul tau!"
	/// (daca cosul cu activitati este gol)
	const vector<Activitate>& getActivitatiCosService() const;

	/// Functie care creeaza raportul activitatilor
	/// @returns raportul activitatilor
	map<string, DTO> createMap();

	/// Functie care salveaza repository-ul intr-un fisier txt
	void saveToFile();

	/// Functie care incarca repository-ul dintr-un fisier txt
	void loadFromFile();

	/// Functie care executa actiunea de undo
	/// @throw ServiceException cu mesajul "Nu mai exista operatii pentru undo!"
	void undo();
};