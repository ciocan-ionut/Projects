#pragma once

//Interfata ce defineste ui-ul

//Functia afiseaza meniul principal al aplicatiei
void MainMenu();

/*
* Functie care citeste input-ul utilizatorului si verifica daca e numar natural
* :return: valoarea citita / -1 (daca nu respecta conditia)
*/
bool intValid(int* nr);

/*
* Functie care preia de la utilizator un nume, un producator si o cantitate
* :return: true (daca datele au fost introduse corect) / false (in caz contrar)
*/
bool input(char* nume, char* producator, int* cantitate);

/*
* Functie care ajuta utilizatorul sa adauge o materie prima prin service in repository
* :param service: referinta catre service
*/
void addMaterie(Service* service);

/*
* Functie care afiseaza materiile din repository prin service
* :param service: referinta catre service
*/
bool showMaterii(Service* service);

/*
* Functie care ajuta utilizatorul sa actualizeze o materie prima din repository prin service
* :param service: referinta catre service
*/
void updateMaterie(Service* service);

/*
* Functie care ajuta utilizatorul sa stearga o materie prima din repository prin service
* :param service: referinta catre service
*/
void deleteMaterie(Service* service);

/*
* Functie care ajuta utilizatorul sa afiseze stocul cu cantitatea mai mica decat cea aleasa prin service
* :param service: referinta catre service
*/
void showStocMinim(Service* service);

//Functia afiseaza meniul pentru ordonarea stocului
void showMateriiOrderedMenu();

/*
* Functie care ajuta utilizatorul sa afiseze stocul ordonat alfabetic sau descrescator dupa cantitate
* :param service: referinta catre service
*/
void showMateriiOrdered(Service* service);

/*
* Functie principala care face legatura dintre utilizator si functionalitatile aplicatiei
* :param service: referinta catre service
*/
void runApp(Service* service);