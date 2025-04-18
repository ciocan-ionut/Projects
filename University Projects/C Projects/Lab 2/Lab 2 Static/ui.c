#include <stdio.h>
#include <string.h>
#include "service.h"

//Implementarea ui-ului aplicatiei

//Functia afiseaza meniul principal al aplicatieiS
void MainMenu()
{
	printf("~~~SC Cofetarie SRL~~~\n");
	printf("Gestioneaza stocul:\n");
	printf("1. Adauga materie prima\n");
	printf("2. Modifica o materie prima\n");
	printf("3. Sterge o materie prima\n");
	printf("4. Afiseaza stocul cu cantitatea mai mica decat cea aleasa\n");
	printf("5. Afiseaza stocul ordonat alfabetic sau descrescator dupa cantitate\n");
	printf("6. Iesire\n");
	printf("Alegeti optiunea: ");
}

/*
* Functie care citeste input-ul utilizatorului si verifica daca e numar natural
* :param nr: referinta catre numarul citit
* :return: true (daca numarul e intreg) / false (in caz contrar)
*/
bool intValid(int* nr)
{
	char buffer[100], extra;
	if (fgets(buffer, sizeof(buffer), stdin))
		if (sscanf_s(buffer, "%d %c", nr, &extra, 1) == 1)
			return true;
	return false;
}

/*
* Functie care preia de la utilizator un nume, un producator si o cantitate
* :return: true (daca datele au fost introduse corect) / false (in caz contrar)
*/
bool input(char* nume, char* producator, int* cantitate)
{
	printf("Nume: ");
	fgets(nume, 20, stdin);
	nume[strcspn(nume, "\n")] = '\0';
	printf("Producator: ");
	fgets(producator, 20, stdin);
	producator[strcspn(producator, "\n")] = '\0';
	printf("Cantitate: ");
	if (!intValid(cantitate))
	{
		printf("Valoarea introdusa nu este valida!\n");
		return false;
	}
	return true;
}

/*
* Functie care ajuta utilizatorul sa adauge o materie prima in repository prin service
* :param service: referinta catre service
*/
void addMaterie(Service* service)
{
	char nume[20], producator[20];
	int cantitate;
	printf("Introduceti detaliile materiei prime:\n");
	if (!input(nume, producator, &cantitate))
		return;
	int errorCode = addMaterieInService(service, nume, producator, cantitate);
	switch (errorCode)
	{
	case 0:
		printf("Materia prima a fost adaugata cu succes!\n");
		return;
	case 1:
		printf("Numele introdus este invalid!\n");
		return;
	case 2:
		printf("Producatorul introdus este invalid!\n");
		return;
	case 3:
		printf("Cantitatea introdusa este invalida!\n");
		return;
	case 4:
		printf("Eroare la repository!\n");
		return;
	default:
		break;
	}
}

/*
* Functie care afiseaza materiile din repository prin service
* :param service: referinta catre service
*/
bool showMaterii(Service* service)
{
	MateriePrima* materii = getMateriiFromService(service);
	int length = getServiceDim(service);
	if (length == 0)
		return false;
	printf("In stoc:\n");
	for (int i = 0; i < length; i++)
	{
		printf("%d. ", i);
		printf("%s, %s | Cantitate: %d", materii[i].nume, materii[i].producator, materii[i].cantitate);
		printf("\n");
	}
	return true;
}
/*
* Functie care ajuta utilizatorul sa actualizeze o materie prima din repository prin service
* :param service: referinta catre service
*/
void updateMaterie(Service* service)
{
	if (!showMaterii(service))
	{
		printf("Nu exista materii prime in stoc!\n");
		return;
	}
	int id, cantitate;
	char nume[20], producator[20];
	printf("Introduceti detaliile materiei prime:\n");
	printf("ID: ");
	if (!intValid(&id))
	{
		printf("Valoarea introdusa nu este valida!\n");
		return;
	}
	printf("*Campurile 'Nume' si 'Producator' pot fi lasate goale in caz ca nu doriti sa fie modificate.\nUn numar negativ in campul 'Cantitate' produce acelasi efect!\n");
	if (!input(nume, producator, &cantitate))
		return;
	if (updateMaterieFromServiceByIndex(id, service, nume, producator, cantitate))
		printf("Materia prima a fost actualizata cu succes!\n");
	else
		printf("Nu exista nicio materie prima cu acel ID!\n");
}

/*
* Functie care ajuta utilizatorul sa stearga o materie prima din repository prin service
* :param service: referinta catre service
*/
void deleteMaterie(Service* service)
{
	if (!showMaterii(service))
	{
		printf("Nu exista materii prime in stoc!\n");
		return;
	}
	int id;
	printf("Introduceti ID-ul materiei prime: ");
	if (!intValid(&id))
	{
		printf("Valoarea introdusa nu este valida!\n");
		return;
	}
	if (deleteMaterieFromServiceByIndex(id, service))
		printf("Materia prima a fost stearsa cu succes!\n");
	else
		printf("Nu exista nicio materie prima cu acel ID!\n");
}

/*
* Functie care ajuta utilizatorul sa afiseze stocul cu cantitatea mai mica decat cea aleasa prin service
* :param service: referinta catre service
*/
void showStocMinim(Service* service)
{
	printf("Alege cantitatea: ");
	int cantitate;
	if (!intValid(&cantitate))
	{
		printf("Valoarea introdusa nu este valida!\n");
		return;
	}
	int length;
	MateriePrima filtru[10];
	if (getMateriiFromServiceByCantitate(service, filtru, &length, cantitate) == 0)
		for (int i = 0; i < length; i++)
		{
			printf("%s, %s | Cantitate: %d", filtru[i].nume, filtru[i].producator, filtru[i].cantitate);
			printf("\n");
		}
	else
		printf("Nu exista nicio materie prima care respecta conditia ceruta!\n");
}

//Functia afiseaza meniul pentru ordonarea stocului
void showMateriiOrderedMenu()
{
	printf("1. Afiseaza stocul ordonat alfabetic\n");
	printf("2. Afiseaza stocul ordonat descrescator dupa cantitate\n");
	printf("3. Inapoi\n");
	printf("Alegeti optiunea: ");
}

/*
* Functie care ajuta utilizatorul sa afiseze stocul ordonat alfabetic sau descrescator dupa cantitate
* :param service: referinta catre service
*/
void showMateriiOrdered(Service* service)
{
	showMateriiOrderedMenu();
	int option, errorCode;
	intValid(&option);
	MateriePrima ordonat[10];
	switch (option)
	{
	case 1:
		errorCode = getMateriiFromServiceOrderedByNume(service, ordonat);
		break;
	case 2:
		errorCode = getMateriiFromServiceOrderedByCantitate(service, ordonat);
		break;
	case 3:
		return;
	default:
		printf("Optiune invalida!\n");
		return;
	}
	if (errorCode == 0)
	{
		for (int i = 0; i < getServiceDim(service); i++)
		{
			printf("%s, %s | Cantitate: %d", ordonat[i].nume, ordonat[i].producator, ordonat[i].cantitate);
			printf("\n");
		}
	}
	else
		printf("Nu exista materii prime in stoc!\n");
}

/*
* Functie principala care face legatura dintre utilizator si functionalitatile aplicatiei
* :param service: referinta catre service
*/
void runApp(Service* service)
{
	bool ok = true;
	while (ok)
	{
		MainMenu();
		int option;

		if (!intValid(&option))
		{
			printf("Optiune invalida!\n");
			continue;
		}

		switch (option)
		{
		case 1:
			addMaterie(service);
			break;
		case 2:
			updateMaterie(service);
			break;
		case 3:
			deleteMaterie(service);
			break;
		case 4:
			showStocMinim(service);
			break;
		case 5:
			showMateriiOrdered(service);
			break;
		case 6:
			ok = false;
			break;
		default:
			printf("Optiune invalida!\n");
		}
	}
}