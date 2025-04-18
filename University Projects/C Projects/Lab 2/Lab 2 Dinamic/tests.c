#include "materie.h"
#include "repository.h"
#include "service.h"
#include <assert.h>
#include <string.h>
#include <stdlib.h>

//Implementarea metodelor de testare a aplicatiei

void runDomainTests();
void runRepositoryTests();
void runServiceTests();

/*
* Functie care ruleaza toate testele aplicatiei
* :raises: AssertionError (daca cel putin un test nu a rulat cu succes)
*/
void runTests()
{
	runDomainTests();
	runRepositoryTests();
	runServiceTests();
}

/*
* Functie care testeaza domeniul aplicatiei
* :raises: AssertionError (daca cel putin un test nu a rulat cu succes)
*/
void runDomainTests()
{
	MateriePrima materie;
	char nume_invalid[] = "";
	char nume[] = "Fier";
	char producator_invalid[] = "";
	char producator[] = "MetalProd";
	int cantitate_invalida = 0;
	int cantitate = 12;

	assert(createMateriePrima(nume_invalid, producator, cantitate, &materie) == 1);
	assert(createMateriePrima(nume, producator_invalid, cantitate, &materie) == 2);
	assert(createMateriePrima(nume, producator, cantitate_invalida, &materie) == 3);
	assert(createMateriePrima(nume, producator, cantitate, &materie) == 0);

	assert(strcmp(getNume(&materie), nume) == 0);
	assert(strcmp(getProducator(&materie), producator) == 0);
	assert(getCantitate(&materie) == cantitate);

	assert(setNume(&materie, nume_invalid) == false);
	assert(setNume(&materie, nume) == true);
	assert(setProducator(&materie, producator_invalid) == false);
	assert(setProducator(&materie, producator) == true);
	assert(setCantitate(&materie, cantitate_invalida) == false);
	assert(setCantitate(&materie, cantitate) == true);

	assert(validateString(nume_invalid) == false);
	assert(validateString(nume) == true);
	assert(validateCantitate(cantitate_invalida) == false);
	assert(validateCantitate(cantitate) == true);

	MateriePrima* m1 = NULL;
	MateriePrima* m2 = NULL;
	assert(areEqual(m1, m2) == true);
	assert(areEqual(m1, &materie) == false);
	assert(areEqual(&materie, &materie) == true);

	destroyMateriePrima(&materie);
}

/*
* Functie care testeaza repository-ul aplicatiei
* :raises: AssertionError (daca cel putin un test nu a rulat cu succes)
*/
void runRepositoryTests()
{
	Repository repo;
	assert(createRepository(&repo) == true);

	char nume1[] = "Fier", nume2[] = "Lemn", nume3[] = "Lana";
	char prod1[] = "MetalProd", prod2[] = "NicusorSRL", prod3[] = "Oaie";
	int cant1 = 12, cant2 = 47, cant3 = 84;
	MateriePrima m1, m2, m3, m4;
	createMateriePrima(nume1, prod1, cant1, &m1);
	createMateriePrima(nume2, prod2, cant2, &m2);
	createMateriePrima(nume1, prod1, cant3, &m3);
	createMateriePrima(nume3, prod3, cant3, &m4);

	assert(addMaterieInRepository(NULL, m1) == false);

	assert(getMateriiFromRepository(&repo) == NULL);

	assert(addMaterieInRepository(&repo, m1) == true);
	assert(getRepositoryDim(&repo) == 1);

	assert(addMaterieInRepository(&repo, m2) == true);
	assert(getRepositoryDim(&repo) == 2);

	assert(addMaterieInRepository(&repo, m3) == true);
	assert(getRepositoryDim(&repo) == 2);
	assert(getCantitate(getMaterieFromRepositoryByIndex(0, &repo)) == cant1 + cant3);

	assert(getMaterieFromRepositoryByIndex(3, &repo) == false);

	assert(updateMaterieFromRepositoryByIndex(3, &repo, nume3, prod3, cant3) == false);
	assert(updateMaterieFromRepositoryByIndex(1, &repo, nume3, NULL, -1) == true);
	assert(strcmp(getNume(getMaterieFromRepositoryByIndex(1, &repo)), nume3) == 0);
	assert(strcmp(getProducator(getMaterieFromRepositoryByIndex(1, &repo)), prod2) == 0);
	assert(getCantitate(getMaterieFromRepositoryByIndex(1, &repo)) == cant2);
	assert(updateMaterieFromRepositoryByIndex(1, &repo, NULL, prod3, -1) == true);
	assert(strcmp(getProducator(getMaterieFromRepositoryByIndex(1, &repo)), prod3) == 0);
	assert(updateMaterieFromRepositoryByIndex(1, &repo, NULL, NULL, cant3) == true);
	assert(areEqual(getMaterieFromRepositoryByIndex(1, &repo), &m4) == true);
	assert(updateMaterieFromRepositoryByIndex(1, &repo, nume2, prod2, cant2) == true);
	assert(areEqual(getMaterieFromRepositoryByIndex(1, &repo), &m2) == true);

	assert(addMaterieInRepository(&repo, m4) == true);
	assert(getRepositoryDim(&repo) == 3);
	assert(deleteMaterieFromRepositoryByIndex(3, &repo) == false);
	assert(deleteMaterieFromRepositoryByIndex(1, &repo) == true);
	assert(getRepositoryDim(&repo) == 2);

	destroyMateriePrima(&m3);

	destroyRepository(&repo);
}

/*
* Functie care testeaza service-ul aplicatiei
* :raises: AssertionError (daca cel putin un test nu a rulat cu succes)
*/
void runServiceTests()
{
	Repository repo;
	createRepository(&repo);

	Service sv;
	assert(createService(&repo, &sv) == true);

	char nume_invalid[] = "", nume[] = "Fier";
	char producator_invalid[] = "", producator[] = "MetalProd";
	int cantitate_invalida = 0, cantitate = 12;

	sv.repository = NULL;
	assert(addMaterieInService(&sv, nume, producator, cantitate) == 4);

	assert(createService(&repo, &sv) == true);

	int length_test = 0;
	assert(copyList(getMateriiFromService(&sv), length_test) == NULL);

	bool ascending = true;
	assert(getMateriiFromServiceOrderedByNume(&sv, *compareNume, ascending) == NULL);

	assert(getMateriiFromServiceOrderedByCantitate(&sv, *compareCantitate, ascending) == NULL);

	assert(addMaterieInService(&sv, nume_invalid, producator, cantitate) == 1);
	assert(addMaterieInService(&sv, nume, producator_invalid, cantitate) == 2);
	assert(addMaterieInService(&sv, nume, producator, cantitate_invalida) == 3);
	assert(addMaterieInService(&sv, nume, producator, cantitate) == 0);
	assert(getServiceDim(&sv) == 1);

	char nume2[] = "Lemn", nume3[] = "Lana";
	char prod2[] = "NicusorSRL", prod3[] = "Oaie";
	int cant2 = 84, cant3 = 47;

	addMaterieInService(&sv, nume2, prod2, cant2);
	assert(updateMaterieFromServiceByIndex(3, &sv, nume3, prod3, cant3) == false);
	assert(updateMaterieFromServiceByIndex(1, &sv, nume3, NULL, -1) == true);
	assert(strcmp(getNume(getMaterieFromServiceByIndex(1, &sv)), nume3) == 0);
	assert(strcmp(getProducator(getMaterieFromServiceByIndex(1, &sv)), prod2) == 0);
	assert(getCantitate(getMaterieFromServiceByIndex(1, &sv)) == cant2);
	assert(updateMaterieFromServiceByIndex(1, &sv, NULL, prod3, -1) == true);
	assert(strcmp(getProducator(getMaterieFromServiceByIndex(1, &sv)), prod3) == 0);
	assert(updateMaterieFromServiceByIndex(1, &sv, NULL, NULL, cant3) == true);
	assert(getCantitate(getMaterieFromServiceByIndex(1, &sv)) == cant3);
	assert(updateMaterieFromServiceByIndex(1, &sv, nume2, prod2, cant2) == true);
	assert(strcmp(getNume(getMaterieFromServiceByIndex(1, &sv)), nume2) == 0);
	assert(strcmp(getProducator(getMaterieFromServiceByIndex(1, &sv)), prod2) == 0);
	assert(getCantitate(getMaterieFromServiceByIndex(1, &sv)) == cant2);
	assert(getServiceDim(&sv) == 2);
	assert(updateMaterieFromServiceByIndex(3, &sv, NULL, NULL, 0) == false);
	assert(updateMaterieFromServiceByIndex(1, &sv, NULL, NULL, 0) == true);
	assert(getServiceDim(&sv) == 1);

	assert(deleteMaterieFromServiceByIndex(3, &sv) == false);
	assert(deleteMaterieFromServiceByIndex(0, &sv) == true);
	assert(getServiceDim(&sv) == 0);

	addMaterieInService(&sv, nume, producator, cantitate);
	addMaterieInService(&sv, nume2, prod2, cant2);
	addMaterieInService(&sv, nume3, prod3, cant3);
	MateriePrima m1, m2, m3;
	createMateriePrima(nume, producator, cantitate, &m1);
	createMateriePrima(nume2, prod2, cant2, &m2);
	createMateriePrima(nume3, prod3, cant3, &m3);

	assert(copyList(NULL, length_test) == NULL);

	int length, cantitate_test1 = 10, cantitate_test2 = 50;
	MateriePrima* test = getMateriiFromServiceByCantitate(&sv, &length, cantitate_invalida);
	assert(test == NULL);
	free(test);

	test = getMateriiFromServiceByCantitate(&sv, &length, cantitate_test1);
	assert(test == NULL);
	free(test);

	test = getMateriiFromServiceByCantitate(&sv, &length, cantitate_test2);
	assert(length == 2);
	assert(areEqual(&test[0], &m1));
	assert(areEqual(&test[1], &m3));
	for (int i = 0; i < length; i++)
		destroyMateriePrima(&test[i]);
	free(test);

	test = getMateriiFromServiceOrderedByNume(&sv, *compareNume, ascending);
	assert(areEqual(&test[0], &m1));
	assert(areEqual(&test[1], &m3));
	assert(areEqual(&test[2], &m2));
	for (int i = 0; i < getServiceDim(&sv); i++)
		destroyMateriePrima(&test[i]);
	free(test);

	test = getMateriiFromServiceOrderedByCantitate(&sv, *compareCantitate, ascending);
	assert(areEqual(&test[0], &m1));
	assert(areEqual(&test[1], &m3));
	assert(areEqual(&test[2], &m2));
	for (int i = 0; i < getServiceDim(&sv); i++)
		destroyMateriePrima(&test[i]);
	free(test);

	ascending = false;
	test = getMateriiFromServiceOrderedByNume(&sv, *compareCantitate, ascending);
	assert(areEqual(&test[0], &m2));
	assert(areEqual(&test[1], &m3));
	assert(areEqual(&test[2], &m1));
	for (int i = 0; i < getServiceDim(&sv); i++)
		destroyMateriePrima(&test[i]);
	free(test);

	test = getMateriiFromServiceOrderedByCantitate(&sv, *compareCantitate, ascending);
	assert(areEqual(&test[0], &m2));
	assert(areEqual(&test[1], &m3));
	assert(areEqual(&test[2], &m1));
	for (int i = 0; i < getServiceDim(&sv); i++)
		destroyMateriePrima(&test[i]);
	free(test);

	deleteMaterieFromServiceByIndex(0, &sv);
	deleteMaterieFromServiceByIndex(0, &sv);
	deleteMaterieFromServiceByIndex(0, &sv);
	assert(getServiceDim(&sv) == 0);

	addMaterieInService(&sv, nume3, prod3, cant2);
	addMaterieInService(&sv, nume2, prod2, cant3);
	addMaterieInService(&sv, nume, producator, cantitate);

	test = getMateriiFromServiceOrderedByCantitate(&sv, *compareCantitate, ascending);
	assert(areEqual(&test[0], &m3));
	assert(areEqual(&test[1], &m2));
	assert(areEqual(&test[2], &m1));
	for (int i = 0; i < getServiceDim(&sv); i++)
		destroyMateriePrima(&test[i]);
	free(test);

	deleteMaterieFromServiceByIndex(0, &sv);
	deleteMaterieFromServiceByIndex(0, &sv);
	deleteMaterieFromServiceByIndex(0, &sv);

	addMaterieInService(&sv, nume3, prod3, cant2);
	addMaterieInService(&sv, nume2, prod2, cant3);
	addMaterieInService(&sv, nume, producator, cantitate);

	test = getMateriiFromServiceOrderedByNume(&sv, *compareNume, ascending);
	assert(areEqual(&test[0], &m2));
	assert(areEqual(&test[1], &m3));
	assert(areEqual(&test[2], &m1));
	for (int i = 0; i < getServiceDim(&sv); i++)
		destroyMateriePrima(&test[i]);
	free(test);

	destroyMateriePrima(&m1);
	destroyMateriePrima(&m2);
	destroyMateriePrima(&m3);

	destroyService(&sv);
}