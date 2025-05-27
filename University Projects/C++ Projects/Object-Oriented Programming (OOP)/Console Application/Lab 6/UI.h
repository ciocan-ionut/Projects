#pragma once

#include "Service.h"

class UI
{
private:
	Service& serv;

public:
	UI(Service& serv) : serv{ serv } {}

	/// Functie care citeste o linie de la utilizator si verifica daca a fost introdus un numar
	/// @param value este posibilul numar
	/// @returns True (daca a fost citit un numar) / False (in caz contrar si afiseaza mesaje corespunzatoare)
	bool static citesteInt(int& value);

	/// Functie care ajuta utilizatorul sa adauge o activitate
	/// @param serv este referinta catre service-ul aplicatiei
	void static addUI(Service& serv);

	/// Functie care ajuta utilizatorul sa stearga o activitate
	/// @param serv este referinta catre service-ul aplicatiei
	void static deleteUI(Service& serv);

	/// Functie care ajuta utilizatorul sa modifice o activitate
	/// @param serv este referinta catre service-ul aplicatiei
	void static modifyUI(Service& serv);

	/// Functie care afiseaza utilizatorului lista de activitati
	/// @param serv este referinta catre service-ul aplicatiei
	bool static showActivitati(const Service& serv);

	/// Functie care afiseaza meniul pentru filtrarea activitatilor
	void static filterMenu();

	/// Functie care afiseaza activitatile filtrate dupa un anumit criteriu
	/// @param serv este referinta catre service-ul aplicatiei
	void static showActivitatiFiltered(const Service& serv);

	/// Functie care afiseaza meniul pentru sortarea activitatilor
	void static sortMenu();

	/// Functie care afiseaza meniul pentru tipul de sortare a activitatilor
	void static ascendingMenu();

	/// Functie care afiseaza activitatile sortate dupa un anumit criteriu
	/// @param serv este referinta catre service-ul aplicatiei
	void static showActivitatiSorted(const Service& serv);

	/// Functia principala a programului
	/// @param serv este referinta catre service-ul aplicatiei
	void static runApp(Service& serv);

	/// Functie care afiseaza meniul admin al aplicatiei
	void static adminMenu();

	/// Functie care ruleaza partea de admin a aplicatiei
	/// @param serv este referinta catre service-ul aplicatiei
	void static runAdmin(Service& serv);

	/// Functie care ajuta utilizatorul sa adauge o activitate in cosul aplicatiei
	/// @param serv este referinta catre service-ul aplicatiei
	bool static addCosUI(Service& serv);

	/// Functie care ajuta utilizatorul sa stearga ce are in cosul aplicatiei
	/// @param serv este referinta catre service-ul aplicatiei
	bool static deleteCosUI(Service& serv);

	/// Functie care ajuta utilizatorul sa genereze activitati aleatoriu dintr-o lista de atribute predefinite
	/// @param serv este referinta catre service-ul aplicatiei
	void static generateActivitatiUI(Service& serv);

	/// Functie care ajuta utilizatorul sa exporte cosul intr-un fisier CSV
	/// @param serv este referinta catre service-ul aplicatiei
	void static exportCosUI(Service& serv);

	/// Functie care afiseaza utilizatorului numarul de activitati din cos
	/// @param serv este referinta catre service-ul aplicatiei
	void static showActivitatiCos(const Service& serv);

	/// Functie care afiseaza raportul activitatilor
	void static showRaport(Service& serv);

	/// Functie care afiseaza meniul user al aplicatiei
	void static userMenu();

	/// Functie care ruleaza partea de user a aplicatiei
	/// @param serv este referinta catre service-ul aplicatiei
	void static runUser(Service& serv);
};

