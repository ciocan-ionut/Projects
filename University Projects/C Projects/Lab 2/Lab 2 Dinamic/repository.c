#include "repository.h"
#include <stdlib.h>
#include <string.h>

//Implementarea metodelor repository-ului

/*
* Functie care creeaza repository-ul pentru stocarea materiilor prime
* :param repository: referinta catre posibilul repository
* :return: true (daca repository-ul s-a creat cu succes) / false (in caz contrar)
*/
bool createRepository(Repository* repository)
{
	repository->cp = 1;
	repository->stoc = (MateriePrima*)malloc(repository->cp * sizeof(MateriePrima));
	repository->dim = 0;
	return true;
}

/*
* Functie care mareste capacitatea vectorului in caz de overflow
* :param repository: referinta catre repository
* :return: true (daca operatia a avut loc cu succes sau nu a fost nevoie de marire) / false (in caz contrar)
*/
bool ensureCapacity(Repository* repository)
{
	if (repository->cp <= repository->dim)
	{
		int newCapacity = repository->cp * 2;
		MateriePrima* newStoc = (MateriePrima*)realloc(repository->stoc, newCapacity * sizeof(MateriePrima));
		repository->stoc = newStoc;
		repository->cp = newCapacity;
	}
	return true;
}

/*
* Functie care elibereaza memoria ocupata de repository
* :param repository: referinta catre repository
*/
void destroyRepository(Repository* repository)
{
	for (int i = 0; i < repository->dim; i++)
	{
		MateriePrima m = repository->stoc[i];
		destroyMateriePrima(&m);
	}
	free(repository->stoc);
}

/*
* Functie care adauga o materie prima in repository
* :param repository: referinta catre repository
* :param materie: materia prima de adaugat
* :return: true (daca materia a fost adaugata cu succes) / false (in caz contrar)
*/
bool addMaterieInRepository(Repository* repository, MateriePrima materie)
{
	if (repository == NULL || !ensureCapacity(repository))
		return false;
	for (int i = 0; i < repository->dim; i++)
		if (areEqual(&materie, &repository->stoc[i]))
		{
			setCantitate(&repository->stoc[i], repository->stoc[i].cantitate + materie.cantitate);
			return true;
		}
	repository->stoc[repository->dim++] = materie;
	return true;
}

/*
* Functie care returneaza numarul de elemente din repository
* :param repository: referinta catre repository
* :return: numarul de elemente
*/
int getRepositoryDim(Repository* repository)
{
	return repository->dim;
}

/*
* Functie care actualizeaza materia prima din repository de pe pozitia 'index' cu noile argumente
* :param index: pozitia materiei de actualizat
* :param repository: referinta catre repository
* :param nume: referinta catre posibilul nou nume
* :param producator: referinta catre posibilul nou producator
* :param cantitate: posibila noua cantitate
* :return: true (daca s-a actualizat cu succes) / false (in caz contrar)
*/
bool updateMaterieFromRepositoryByIndex(int index, Repository* repository, char* nume, char* producator, int cantitate)
{
	if (index < 0 || index >= repository->dim)
		return false;
	if (validateString(nume))
		setNume(&repository->stoc[index], nume);
	if (validateString(producator))
		setProducator(&repository->stoc[index], producator);
	if (validateCantitate(cantitate))
		setCantitate(&repository->stoc[index], cantitate);
	return true;
}

/*
* Functie care returneaza materia aflata pe pozitia 'index'
* :param index: pozitia materiei in repository
* :param repository: referinta catre repository
* :return: materia de pe pozitia 'index'
*/
MateriePrima* getMaterieFromRepositoryByIndex(int index, Repository* repository)
{
	if (index < 0 || index >= repository->dim)
		return false;
	return &repository->stoc[index];
}

/*
* Functie care sterge materia aflata pe pozitia 'index'
* :param index: pozitia materiei in repository
* :param repository: referinta catre repository
* :return: true (daca s-a sters materia cu succes) / false (in caz contrar)
*/
bool deleteMaterieFromRepositoryByIndex(int index, Repository* repository)
{
	if (index < 0 || index >= repository->dim)
		return false;
	destroyMateriePrima(&repository->stoc[index]);
	for (int i = index; i < repository->dim; i++)
		repository->stoc[i] = repository->stoc[i + 1];
	repository->dim--;
	return true;
}

/*
* Functie care returneaza materiile din repository
* :param repository: referinta catre repository
* :return: vectorul cu materii / NULL (daca vectorul e gol)
*/
MateriePrima* getMateriiFromRepository(Repository* repository)
{
	if (repository->dim == 0)
		return NULL;
	return repository->stoc;
}