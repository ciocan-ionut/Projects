#include "service.h"
#include <stdlib.h>
#include <string.h>

//Implementarea metodelor service-ului

/*
* Functie care creeaza service-ul aplicatiei
* :param repository: referinta catre repository
* :param service: referinta catre posibilul service
* :return: true (daca service-ul s-a creat cu succes) / false (in caz contrar)
*/
bool createService(Repository* repository, Service* service)
{
	service->repository = repository;
	return true;
}




/*
* Functie care creeaza si adauga o materie prima in service
* :param service: referinta catre service
* :param nume: numele unic a materiei prime, string != ""
* :param producator: numele producatorului, string != ""
* :param cantitate: cantitatea de materie prima, int > 0
* :return: 0 (materia a fost creata cu succes)
*		   1 (nume invalid)
*		   2 (producator invalid)
*		   3 (cantitate invalida)
*		   4 (eroare la repository)
*/
int addMaterieInService(Service* service, char* nume, char* producator, int cantitate)
{
	MateriePrima materie;
	int errorCode = createMateriePrima(nume, producator, cantitate, &materie);
	if (errorCode != 0)
		return errorCode;
	if (!addMaterieInRepository(service->repository, materie))
		return 4;
	return 0;
}

/*
* Functie care returneaza numarul de elemente din service
* :param service: referinta catre service
* :return: numarul de elemente
*/
int getServiceDim(Service* service)
{
	return getRepositoryDim(service->repository);
}

/*
* Functie care sterge materia prima de pe pozitia 'index' daca cantitatea este actualizata la 0 sau o actualizeaza cu noile argumente
* :param index: pozitia materiei de actualizat
* :param service: referinta catre service
* :param nume: referinta catre posibilul nou nume
* :param producator: referinta catre posibilul nou producator
* :param cantitate: posibila noua cantitate
* :return: true (daca operatia a avut loc cu succes) / false (in caz contrar)
*/
bool updateMaterieFromServiceByIndex(int index, Service* service, char* nume, char* producator, int cantitate)
{
	if (cantitate == 0)
		if (!deleteMaterieFromRepositoryByIndex(index, service->repository))
			return false;
		else
			return true;
	if (!updateMaterieFromRepositoryByIndex(index, service->repository, nume, producator, cantitate))
		return false;
	return true;
}

/*
* Functie care returneaza materia aflata pe pozitia 'index'
* :param index: pozitia materiei in service
* :param service: referinta catre service
* :return: materia de pe pozitia 'index'
*/
MateriePrima* getMaterieFromServiceByIndex(int index, Service* service)
{
	return getMaterieFromRepositoryByIndex(index, service->repository);
}

/*
* Functie care sterge materia aflata pe pozitia 'index'
* :param index: pozitia materiei in service
* :param service: referinta catre service
* :return: true (daca s-a sters materia cu succes) / false (in caz contrar)
*/
bool deleteMaterieFromServiceByIndex(int index, Service* service)
{
	return deleteMaterieFromRepositoryByIndex(index, service->repository);
}

/*
* Functie care returneaza materiile din service
* :param service: referinta catre service
* :return: vectorul cu materii / NULL (daca vectorul e gol)
*/
MateriePrima* getMateriiFromService(Service* service)
{
	return getMateriiFromRepository(service->repository);
}

/*
* Functie care pune in vectorul 'solutie' materiile prime care au cantitatea mai mica decat 'cantitate'
* :param service: referinta catre service
* :param solutie: referinta catre vectorul cu materii filtrat
* :param length: referinta catre lungimea vectorului
* :param cantitate: cantitatea dupa care se face filtrarea
* :return: 0 (operatia a avut loc cu succes)
*		   1 (cantitate invalida)
*		   2 (nu exista nicio materie care respecta conditia)
*/
int getMateriiFromServiceByCantitate(Service* service, MateriePrima* solutie, int* length, int cantitate)
{
	if (!validateCantitate(cantitate))
		return 1;
	*length = 0;
	MateriePrima* materii = getMateriiFromService(service);
	for (int i = 0; i < getServiceDim(service); i++)
		if (getCantitate(&materii[i]) < cantitate)
		{
			solutie[*length] = materii[i];
			(*length)++;
		}
	if ((*length) == 0)
		return 2;
	return 0;
}

/*
* Functie care pune in vectorul 'solutie' materiile prime ordonate alfabetic dupa nume
* :param service: referinta catre service
* :param solutie: referinta catre vectorul cu materii ordonat
* :return: 0 (operatia a avut loc cu succes)
*		   1 (nu exista nicio materie prima in stoc)
*/
int getMateriiFromServiceOrderedByNume(Service* service, MateriePrima* solutie)
{
	int length = getServiceDim(service);
	if (length == 0)
		return 1;
	MateriePrima* materii = getMateriiFromService(service);
	for (int i = 0; i < length; i++)
		solutie[i] = materii[i];
	for (int i = 0; i < length - 1; i++)
	{
		bool swapped = false;
		for (int j = 0; j < length - i - 1; j++)
			if (strcmp(getNume(&solutie[j]), getNume(&solutie[j + 1])) > 0)
			{
				MateriePrima temp = solutie[j];
				solutie[j] = solutie[j + 1];
				solutie[j + 1] = temp;
				swapped = true;
			}
		if (!swapped)
			break;
	}
	return 0;
}

/*
* Functie care pune in vectorul 'solutie' materiile prime ordonate descrescator dupa cantitate
* :param service: referinta catre service
* :param solutie: referinta ctare vectorul cu materii ordonat
* :return: 0 (operatia a avut loc cu succes)
*		   1 (nu exista nicio materie prima in stoc)
*/
int getMateriiFromServiceOrderedByCantitate(Service* service, MateriePrima* solutie)
{
	int length = getServiceDim(service);
	if (length == 0)
		return 1;
	MateriePrima* materii = getMateriiFromService(service);
	for (int i = 0; i < length; i++)
		solutie[i] = materii[i];
	for (int i = 0; i < length - 1; i++)
	{
		bool swapped = false;
		for (int j = 0; j < length - i - 1; j++)
			if (getCantitate(&solutie[j]) < getCantitate(&solutie[j + 1]))
			{
				MateriePrima temp = solutie[j];
				solutie[j] = solutie[j + 1];
				solutie[j + 1] = temp;
				swapped = true;
			}
		if (!swapped)
			break;
	}
	return 0;
}