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
* Functie care elibereaza memoria ocupata de service
* :param service: referinta catre service
*/
void destroyService(Service* service)
{
	destroyRepository(service->repository);
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
	{
		destroyMateriePrima(&materie);
		return 4;
	}
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
* Functie care returneaza materiile prime care au cantitatea mai mica decat 'cantitate
* :param service: referinta catre service
* :param length: referinta catre lungimea vectorului
* :param cantitate: cantitatea dupa care se face filtrarea
* :return: vectorul cu materii filtrat / NULL (daca cantitatea nu e valida sau nicio materie nu respecta conditia)
*/
MateriePrima* getMateriiFromServiceByCantitate(Service* service, int* length, int cantitate)
{
	if (!validateCantitate(cantitate))
		return NULL;
	*length = 0;
	MateriePrima* materii = getMateriiFromService(service);
	MateriePrima* solutie = (MateriePrima*)malloc(getServiceDim(service) * sizeof(MateriePrima));
	if (solutie != NULL)
	{
		for (int i = 0; i < getServiceDim(service); i++)
				if (getCantitate(&materii[i]) < cantitate)
				{
					MateriePrima copie;
					createMateriePrima(materii[i].nume, materii[i].producator, materii[i].cantitate, &copie);
					solutie[*length] = copie;
					(*length)++;
				}
	}
	if ((*length) == 0)
	{
		free(solutie);
		return NULL;
	}
	return solutie;
}

/*
* Functie care returneaza o copie a listei transmise ca parametru
* :param repository: referinta catre lista
* :param length: lungimea listei
* :return: copia listei
*/
MateriePrima* copyList(MateriePrima* list, int length)
{
	if (length == 0)
		return NULL;
	MateriePrima* copy = (MateriePrima*)malloc(length * sizeof(MateriePrima));
	if (copy != NULL)
	{
		for (int i = 0; i < length; i++)
		{
			MateriePrima copie;
			createMateriePrima(list[i].nume, list[i].producator, list[i].cantitate, &copie);
			copy[i] = copie;
		}
	}
	return copy;
}

/*
* Functie care returneaza materiile prime ordonate alfabetic dupa nume
* :param service: referinta catre service
* :return: vectorul cu materii ordonat / NULL (daca nu exista nicio materie prima in stoc)
*/
MateriePrima* getMateriiFromServiceOrderedByNume(Service* service, Compare compareNume, bool ascending)
{
	int length = getServiceDim(service);
	if (length == 0)
		return NULL;
	MateriePrima* materii = getMateriiFromService(service);
	MateriePrima* solutie = copyList(materii, length);
	for (int i = 0; i < length - 1; i++)
	{
		bool swapped = false;
		for (int j = 0; j < length - i - 1; j++)
			if (compareNume(&solutie[j], &solutie[j + 1], ascending))
			{
				MateriePrima temp = solutie[j];
				solutie[j] = solutie[j + 1];
				solutie[j + 1] = temp;
				swapped = true;
			}
		if (!swapped)
			break;
	}
	return solutie;
}

/*
* Functie care returneaza materiile prime ordonate descrescator dupa cantitate
* :param service: referinta catre service
* :return: vectorul cu materii ordonat / NULL (daca nu exista nicio materie prima in stoc)
*/
MateriePrima* getMateriiFromServiceOrderedByCantitate(Service* service, Compare compareCantitate, bool ascending)
{
	int length = getServiceDim(service);
	if (length == 0)
		return NULL;
	MateriePrima* materii = getMateriiFromService(service);
	MateriePrima* solutie = copyList(materii, length);
	for (int i = 0; i < length - 1; i++)
	{
		bool swapped = false;
		for (int j = 0; j < length - i - 1; j++)
			if (compareCantitate(&solutie[j], &solutie[j + 1], ascending))
			{
				MateriePrima temp = solutie[j];
				solutie[j] = solutie[j + 1];
				solutie[j + 1] = temp;
				swapped = true;
			}
		if (!swapped)
			break;
	}
	return solutie;
}