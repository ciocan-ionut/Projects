#pragma once
#include <stdbool.h>

//Interfata ce defineste o materie prima

/*
* Structura unei materii prime
* string nume - numele unic a materiei prime != ""
* string producator - numele producatorului != ""
* int cantitate - cantitatea de materie prima > 0
*/
typedef struct materieprima
{
	char* nume;
	char* producator;
	int cantitate;
} MateriePrima;

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
int createMateriePrima(char* nume, char* producator, int cantitate, MateriePrima* materie);

/*
* Functie care elibereaza memoria ocupata de o materie prima
* :param materie: referinta catre materie
*/
void destroyMateriePrima(MateriePrima* materie);



/*
* Functie care returneaza numele materiei 'materie'
* :param materie: referinta materiei
* :return: referinta catre numele materiei
*/
char* getNume(MateriePrima* materie);

/*
* Functie care returneaza numele producatorului materiei 'materie'
* :param materie: referinta materiei
* :return: referinta catre numele producatorului
*/
char* getProducator(MateriePrima* materie);

/*
* Functie care returneaza cantitatea materiei 'materie'
* :param materie: referinta materiei
* :return: cantitatea de materie
*/
int getCantitate(MateriePrima* materie);




/*
* Functie care seteaza numele materiei 'materie' la numele 'nume'
* :param materie: referinta materiei
* :param nume: referinta catre noul nume al materiei
* :return: true (daca numele este valid) / false (in caz contrar)
*/
bool setNume(MateriePrima* materie, char* nume);

/*
* Functie care seteaza numele producatorului materiei 'materie' la producatorul 'producator'
* :param materie: referinta materiei
* :param producator: referinta catre noul producator al materiei
* :return: true (daca producatorul este valid) / false (in caz contrar)
*/
bool setProducator(MateriePrima* materie, char* producator);

/*
* Functie care seteaza cantitatea materiei 'materie' cu cantitatea 'cantitate'
* :param materie: referinta materiei
* :param cantitate: noua cantitate de materie
* :return: true (daca cantitatea este valida) / false (in caz contrar)
*/
bool setCantitate(MateriePrima* materie, int cantitate);




/*
* Functie care verifica daca string este valid
* :param string: referinta catre sirul de caractere
* :return: true (daca string este valid) / false (in caz contrar)
*/
bool validateString(char* string);

/*
* Functie care verifica daca cantitatea este valida
* :param cantitate: cantitatea de materie
* :return: true (daca cantitatea este valida) / false (in caz contrar)
*/
bool validateCantitate(int cantitate);




/*
* Functie care verifica daca 2 materii prime sunt egale
* :param m1: referinta catre prima materie
* :param m2: referinta catre a doua materie
* :return: true (daca materiile sunt egale) / false (in caz contrar)
*/
bool areEqual(MateriePrima* m1, MateriePrima* m2);

/*
* Functie care ajuta la compararea cantitatilor dintre 2 materii prime in functie de ascending
* :param m1: referinta catre prima materie
* :param m2: referinta catre a doua materie
* :param ascending: true (daca se doreste ordonat crescator) / false (in caz contrar)
* :return: true (daca se respecta conditia) / false (in caz contrar)
*/
bool compareCantitate(MateriePrima* m1, MateriePrima* m2, bool ascending);

/*
* Functie care ajuta la compararea numelor dintre 2 materii prime in functie de ascending
* :param m1: referinta catre prima materie
* :param m2: referinta catre a doua materie
* :param ascending: true (daca se doreste ordonat crescator) / false (in caz contrar)
* :return: true (daca se respecta conditia) / false (in caz contrar)
*/
bool compareNume(MateriePrima* m1, MateriePrima* m2, bool ascending);