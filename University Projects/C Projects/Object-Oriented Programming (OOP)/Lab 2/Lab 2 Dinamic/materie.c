#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "materie.h"

//Implementarea metodelor unei materii prime

/*
* Functie care creeaza o materie prima cu numele 'nume', producatorul 'producator' si cu cantitatea 'cantitate'
* :param nume: numele unic a materiei prime, string != ""
* :param producator: numele producatorului, string != ""
* :param cantitate: cantitatea de materie prima, int > 0
* :param materie: referinta catre posibila materie
* :return: 0 (materia a fost creata cu succes)
*		   1 (nume invalid)
*		   2 (producator invalid)
*		   3 (cantitate invalida)
*/
int createMateriePrima(char* nume, char* producator, int cantitate, MateriePrima* materie)
{
	if (!validateString(nume))
		return 1;
	if (!validateString(producator))
		return 2;
	if (!validateCantitate(cantitate))
		return 3;
	materie->nume = (char*)malloc(strlen(nume) + 1);
	if (materie->nume != NULL)
		strcpy_s(materie->nume, strlen(nume) + 1, nume);
	materie->producator = (char*)malloc(strlen(producator) + 1);
	if (materie->producator != NULL)
		strcpy_s(materie->producator, strlen(producator) + 1, producator);
	materie->cantitate = cantitate;
	return 0;
}

/*
* Functie care elibereaza memoria ocupata de o materie prima
* :param materie: referinta catre materie
*/
void destroyMateriePrima(MateriePrima* materie)
{
	free(materie->nume);
	free(materie->producator);
}




/*
* Functie care returneaza numele materiei 'materie'
* :param materie: referinta materiei
* :return: referinta catre numele materiei
*/
char* getNume(MateriePrima* materie)
{
	return materie->nume;
}

/*
* Functie care returneaza numele producatorului materiei 'materie'
* :param materie: referinta materiei
* :return: referinta catre numele producatorului
*/
char* getProducator(MateriePrima* materie)
{
	return materie->producator;
}

/*
* Functie care returneaza cantitatea materiei 'materie'
* :param materie: referinta materiei
* :return: cantitatea de materie
*/
int getCantitate(MateriePrima* materie)
{
	return materie->cantitate;
}




/*
* Functie care seteaza numele materiei 'materie' la numele 'nume'
* :param materie: referinta materiei
* :param nume: referinta catre noul nume al materiei
* :return: true (daca numele este valid) / false (in caz contrar)
*/
bool setNume(MateriePrima* materie, char* nume)
{
	if (!validateString(nume))
		return false;
	strcpy_s(materie->nume, strlen(nume) + 1, nume);
	return true;
}

/*
* Functie care seteaza numele producatorului materiei 'materie' la producatorul 'producator'
* :param materie: referinta materiei
* :param producator: referinta catre noul producator al materiei
* :return: true (daca producatorul este valid) / false (in caz contrar)
*/
bool setProducator(MateriePrima* materie, char* producator)
{
	if (!validateString(producator))
		return false;
	strcpy_s(materie->producator, strlen(producator) + 1, producator);
	return true;
}

/*
* Functie care seteaza cantitatea materiei 'materie' cu cantitatea 'cantitate'
* :param materie: referinta materiei
* :param cantitate: noua cantitate de materie
* :return: true (daca cantitatea este valida) / false (in caz contrar)
*/
bool setCantitate(MateriePrima* materie, int cantitate)
{
	if (!validateCantitate(cantitate))
		return false;
	materie->cantitate = cantitate;
	return true;
}




/*
* Functie care verifica daca string este valid
* :param string: referinta catre sirul de caractere
* :return: true (daca string este valid) / false (in caz contrar)
*/
bool validateString(char* string)
{
	return string != NULL && strlen(string) > 0 && strcmp(string, "\n") != 0;
}

/*
* Functie care verifica daca cantitatea este valida
* :param cantitate: cantitatea de materie
* :return: true (daca cantitatea este valida) / false (in caz contrar)
*/
bool validateCantitate(int cantitate)
{
	return cantitate > 0;
}




/*
* Functie care verifica daca 2 materii prime sunt egale
* :param m1: referinta catre prima materie
* :param m2: referinta catre a doua materie
* :return: true (daca materiile sunt egale) / false (in caz contrar)
*/
bool areEqual(MateriePrima* m1, MateriePrima* m2)
{
	if (m1 == NULL && m2 == NULL)
		return true;
	if (m1 == NULL || m2 == NULL)
		return false;
	return strcmp(m1->nume, m2->nume) == 0 && strcmp(m1->producator, m2->producator) == 0;
}

/*
* Functie care ajuta la compararea cantitatilor dintre 2 materii prime in functie de ascending
* :param m1: referinta catre prima materie
* :param m2: referinta catre a doua materie
* :param ascending: true (daca se doreste ordonat crescator) / false (in caz contrar)
* :return: true (daca se respecta conditia) / false (in caz contrar)
*/
bool compareCantitate(MateriePrima* m1, MateriePrima* m2, bool ascending)
{
	if (ascending)
	{
		if (m1->cantitate > m2->cantitate)
			return true;
	}
	else
	{
		if (m1->cantitate < m2->cantitate)
			return true;
	}
	return false;
}

/*
* Functie care ajuta la compararea numelor dintre 2 materii prime in functie de ascending
* :param m1: referinta catre prima materie
* :param m2: referinta catre a doua materie
* :param ascending: true (daca se doreste ordonat crescator) / false (in caz contrar)
* :return: true (daca se respecta conditia) / false (in caz contrar)
*/
bool compareNume(MateriePrima* m1, MateriePrima* m2, bool ascending)
{
	if (ascending)
	{
		if (strcmp(m1->nume, m2->nume) > 0)
			return true;
	}
	else
	{
		if (strcmp(m1->nume, m2->nume) < 0)
			return true;
	}
	return false;
}