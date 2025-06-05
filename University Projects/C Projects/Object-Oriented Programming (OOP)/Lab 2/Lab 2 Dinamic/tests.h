#pragma once

//Interfata ce defineste testele

/*
* Functie care ruleaza toate testele aplicatiei
* :raises: AssertionError (daca cel putin un test nu a rulat cu succes)
*/
void runTests();

/*
* Functie care testeaza domeniul aplicatiei
* :raises: AssertionError (daca cel putin un test nu a rulat cu succes)
*/
void runDomainTests();

/*
* Functie care testeaza repository-ul aplicatiei
* :raises: AssertionError (daca cel putin un test nu a rulat cu succes)
*/
void runRepositoryTests();

/*
* Functie care testeaza serice-ul aplicatiei
* :raises: AssertionError (daca cel putin un test nu a rulat cu succes)
*/
void runServiceTests();