#pragma once

#include "repository.h"
#include "materie.h"

//Interfata ce defineste service-ul

typedef struct
{
	Repository* repository;
} Service;

typedef bool(*Compare)(MateriePrima* m1, MateriePrima* m2, bool ascending);

/*
* Functie care creeaza service-ul aplicatiei
* :param repository: referinta catre repository
* :param service: referinta catre posibilul service
* :return: true (daca service-ul s-a creat cu succes) / false (in caz contrar)
*/
bool createService(Repository* repository, Service* service);

/*
* Functie care elibereaza memoria ocupata de service
* :param service: referinta catre service
*/
void destroyService(Service* service);

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
int addMaterieInService(Service* service, char* nume, char* producator, int cantitate);

/*
* Functie care returneaza numarul de elemente din service
* :param service: referinta catre service
* :return: numarul de elemente
*/
int getServiceDim(Service* service);

/*
* Functie care sterge materia prima de pe pozitia 'index' daca cantitatea este actualizata la 0 sau o actualizeaza cu noile argumente
* :param index: pozitia materiei de actualizat
* :param service: referinta catre service
* :param nume: referinta catre posibilul nou nume
* :param producator: referinta catre posibilul nou producator
* :param cantitate: posibila noua cantitate
* :return: true (daca operatia a avut loc cu succes) / false (in caz contrar)
*/
bool updateMaterieFromServiceByIndex(int index, Service* service, char* nume, char* producator, int cantitate);

/*
* Functie care returneaza materia aflata pe pozitia 'index'
* :param index: pozitia materiei in service
* :param service: referinta catre service
* :return: materia de pe pozitia 'index'
*/
MateriePrima* getMaterieFromServiceByIndex(int index, Service* service);

/*
* Functie care sterge materia aflata pe pozitia 'index'
* :param index: pozitia materiei in service
* :param service: referinta catre service
* :return: true (daca s-a sters materia cu succes) / false (in caz contrar)
*/
bool deleteMaterieFromServiceByIndex(int index, Service* service);

/*
* Functie care returneaza materiile din service
* :param service: referinta catre service
* :return: vectorul cu materii / NULL (daca vectorul e gol)
*/
MateriePrima* getMateriiFromService(Service* service);

/*
* Functie care returneaza materiile prime care au cantitatea mai mica decat 'cantitate
* :param service: referinta catre service
* :param length: referinta catre lungimea vectorului
* :param cantitate: cantitatea dupa care se face filtrarea
* :return: vectorul cu materii filtrat / NULL (daca cantitatea nu e valida sau nicio materie nu respecta conditia)
*/
MateriePrima* getMateriiFromServiceByCantitate(Service* service, int* length, int cantitate);

/*
* Functie care returneaza o copie a listei transmise ca parametru
* :param repository: referinta catre lista
* :param length: lungimea listei
* :return: copia listei
*/
MateriePrima* copyList(MateriePrima* list, int length);

/*
* Functie care returneaza materiile prime ordonate alfabetic dupa nume
* :param service: referinta catre service
* :return: vectorul cu materii ordonat / NULL (daca nu exista nicio materie prima in stoc)
*/
MateriePrima* getMateriiFromServiceOrderedByNume(Service* service, Compare compareNume, bool ascending);

/*
* Functie care returneaza materiile prime ordonate descrescator dupa cantitate
* :param service: referinta catre service
* :return: vectorul cu materii ordonat / NULL (daca nu exista nicio materie prima in stoc)
*/
MateriePrima* getMateriiFromServiceOrderedByCantitate(Service* service, Compare compareCantitate, bool ascending);