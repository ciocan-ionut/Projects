#pragma once

#include "materie.h"

//Interfata ce defineste repository-ul

typedef struct repository
{
	MateriePrima stoc[10];
	int dim;
} Repository;

/*
* Functie care creeaza repository-ul pentru stocarea materiilor prime
* :param repository: referinta catre posibilul repository
* :return: true (daca repository-ul s-a creat cu succes) / false (in caz contrar)
*/
bool createRepository(Repository* repository);




/*
* Functie care adauga o materie prima in repository
* :param repository: referinta catre repository
* :param materie: materia prima de adaugat
* :return: true (daca materia a fost adaugata cu succes) / false (in caz contrar)
*/
bool addMaterieInRepository(Repository* repository, MateriePrima materie);

/*
* Functie care returneaza numarul de elemente din repository
* :param repository: referinta catre repository
* :return: numarul de elemente
*/
int getRepositoryDim(Repository* repository);

/*
* Functie care actualizeaza materia prima din repository de pe pozitia 'index' cu noile argumente
* :param index: pozitia materiei de actualizat
* :param repository: referinta catre repository
* :param nume: referinta catre posibilul nou nume
* :param producator: referinta catre posibilul nou producator
* :param cantitate: posibila noua cantitate
* :return: true (daca s-a actualizat cu succes) / false (in caz contrar)
*/
bool updateMaterieFromRepositoryByIndex(int index, Repository* repository, char* nume, char* producator, int cantitate);

/*
* Functie care returneaza materia aflata pe pozitia 'index'
* :param index: pozitia materiei in repository
* :param repository: referinta catre repository
* :return: materia de pe pozitia 'index'
*/
MateriePrima* getMaterieFromRepositoryByIndex(int index, Repository* repository);

/*
* Functie care sterge materia aflata pe pozitia 'index'
* :param index: pozitia materiei in repository
* :param repository: referinta catre repository
* :return: true (daca s-a sters materia cu succes) / false (in caz contrar)
*/
bool deleteMaterieFromRepositoryByIndex(int index, Repository* repository);

/*
* Functie care returneaza materiile din repository
* :param repository: referinta catre repository
* :return: vectorul cu materii / NULL (daca vectorul e gol)
*/
MateriePrima* getMateriiFromRepository(Repository* repository);