#include "UI.h"
#include <iostream>
#include <limits>
#include <regex>

using namespace std;

bool UI::citesteInt(int& value)
{
	string line; 
	getline(cin, line);
	if (line == "")
	{
		cout << "Nu ati introdus nimic!\n";
		return false;
	}
	for (char c : line)
		if ((!isdigit(c) && c != '-') || (line.size() == 1 && line[0] == '-'))
		{
			cout << "Introduceti un numar!\n";
			return false;
		}
	value = stoi(line);
	return true;
}

void UI::addUI(Service& serv)
{
	string titlu, descriere, tip, durata_string; int durata;
	cout << "Introduceti detaliile activitatii:" << endl;
	cout << "Titlul: "; getline(cin, titlu);
	cout << "Descriere: "; getline(cin, descriere);
	cout << "Tipul: "; getline(cin, tip);

	while (true)
	{
		cout << "Durata: ";
		if (citesteInt(durata))
			break;
	}

	try
	{
		serv.addService(titlu, descriere, tip, durata);
		cout << "Activitatea a fost adaugata cu succes!" << endl;
	}
	catch (BaseException& error)
	{
		cout << error.what();
	}
}

void UI::deleteUI(Service& serv)
{
	if (showActivitati(serv))
	{
		int index;
		while (true)
		{
			cout << "Introduceti numarul activitatii: ";
			if (citesteInt(index))
				break;
		}

		try
		{
			serv.deleteService(index);
			cout << "Activitatea a fost stearsa cu succes!" << endl;
		}
		catch (ServiceException& error)
		{
			cout << error.what();
		}
	}
}

void UI::modifyUI(Service& serv)
{
	if (showActivitati(serv))
	{
		string titlu, descriere, tip, line;
		int durata, index;
		while (true)
		{
			cout << "Introduceti numarul activitatii: ";
			if (citesteInt(index))
				break;
		}

		cout << "Introduceti detaliile noii activitati: " << endl;
		cout << "* Lasati goale campurile pe care nu doriti sa le modificati!" << endl;
		cout << "Titlul: "; getline(cin, titlu);
		cout << "Descriere: "; getline(cin, descriere);
		cout << "Tipul: "; getline(cin, tip);

		while (true)
		{
			cout << "Durata: "; getline(cin, line);
			if (line == "")
			{
				durata = -1;
				break;
			}
			else
			{
				bool valid = true;
				for (char c : line)
					if ((!isdigit(c) && c != '-') || (line.size() == 1 && line[0] == '-'))
					{
						cout << "Introduceti un numar!\n";
						valid = false;
						break;
					}
				if (!valid)
					continue;
				durata = stoi(line);
				if (durata <= 0)
				{
					cout << "Introduceti un numar pozitiv!\n";
					continue;
				}
				break;
			}
		}

		try
		{
			serv.modifyService(index, titlu, descriere, tip, durata);
			cout << "Activitatea a fost modificata cu succes!" << endl;
		}
		catch (BaseException& err)
		{
			cout << err.what();
		}
	}
}

bool UI::showActivitati(const Service& serv)
{
	try
	{
		const auto& activitati = serv.getActivitatiService();
		int i = 0;
		for (const auto& a : activitati)
			cout << i++ << ". " << a << endl;
		return true;
	}
	catch (ServiceException& error)
	{
		cout << error.what();
		return false;
	}
}

void UI::filterMenu()
{
	cout << "Filtrati dupa:" << endl;
	cout << "1. Descriere" << endl;
	cout << "2. Tip" << endl;
	cout << "0. Inapoi" << endl;
}

void UI::showActivitatiFiltered(const Service& serv)
{
	try
	{
		serv.getActivitatiService();
		while (true)
		{
			filterMenu();
			int option = 0;
			string descriere, tip;
			vector<Activitate> listaFiltrata;
			
			while (true)
			{
				cout << "Alegeti optiunea: ";
				if (citesteInt(option))
					break;
			}

			switch (option)
			{
			case 0:
				return;
			case 1:
				cout << "Introduceti descrierea: "; getline(cin, descriere);
				listaFiltrata = serv.filterService(&Activitate::getDescriere, descriere);
				break;
			case 2:
				cout << "Introduceti tipul: "; getline(cin, tip);
				listaFiltrata = serv.filterService(&Activitate::getTip, tip);
				break;
			default:
				cout << "Optiune invalida!" << endl;
				break;
			}
			int i = 0;
			for (const auto& a : listaFiltrata)
				cout << i++ << ". " << a << endl;
			break;
		}
	}
	catch (BaseException& err)
	{
		cout << err.what();
	}
}

void UI::sortMenu()
{
	cout << "Sortati dupa:" << endl;
	cout << "1. Titlu" << endl;
	cout << "2. Descriere" << endl;
	cout << "3. Tip + Durata" << endl;
	cout << "0. Inapoi" << endl;
}

void UI::ascendingMenu()
{
	cout << "Sortati:" << endl;
	cout << "1. Crescator" << endl;
	cout << "2. Descrescator" << endl;
	cout << "0. Inapoi" << endl;
}

void UI::showActivitatiSorted(const Service& serv)
{
	try
	{
		serv.getActivitatiService();
		while (true)
		{
			int choice, option = 0;
			bool ascending = false;

			ascendingMenu();
			while (true)
			{
				cout << "Alegeti optiunea: ";
				if (citesteInt(choice))
					break;
			}
			
			switch(choice)
			{
			case 0:
				return;
			case 1:
				ascending = true;
				break;
			case 2:
				ascending = false;
				break;
			default:
				cout << "Optiune invalida!" << endl;
				return;
			}

			vector<Activitate> listaSortata;

			sortMenu();
			while (true)
			{
				cout << "Alegeti optiunea: ";
				if (citesteInt(option))
					break;
			}

			switch (option)
			{
			case 0:
				continue;
			case 1:
				listaSortata = serv.sortedService(&Activitate::compareTitlu, ascending);
				break;
			case 2:
				listaSortata = serv.sortedService(&Activitate::compareDescriere, ascending);
				break;
			case 3:
				listaSortata = serv.sortedService(&Activitate::compareTipSiDurata, ascending);
				break;
			default:
				cout << "Optiune invalida!" << endl;
				return;;
			}
			int i = 0;
			for (const auto& a : listaSortata)
				cout << i++ << ". " << a << endl;
			break;
		}
	}
	catch (ServiceException& err)
	{
		cout << err.what();
	}
}

void UI::showRaport(Service& serv)
{
	try
	{
		auto raport = serv.createMap();
		for (const auto& r : raport)
			cout << "Tip: " << r.second.getTip() << " apare de " << r.second.getCantitate() << " ori" << endl;
	}
	catch (ServiceException& error)
	{
		cout << error.what();
	}
}

void UI::adminMenu()
{
	cout << "~~~Activitati~~~" << endl;
	cout << "1. Adauga o activitate" << endl;
	cout << "2. Sterge o activitate" << endl;
	cout << "3. Modifica o activitate" << endl;
	cout << "4. Afiseaza activitatile" << endl;
	cout << "5. Filtreaza activitatile" << endl;
	cout << "6. Sorteaza activitatile" << endl;
	cout << "7. Afiseaza raport*" << endl;
	cout << "8. Undo" << endl;
	cout << "0. Iesire" << endl;
}

void UI::runAdmin(Service& serv)
{
	while (true)
	{
		adminMenu();
		int option = 0;

		while (true)
		{
			cout << "Alegeti optiunea: ";
			if (citesteInt(option))
				break;
		}

		switch (option)
		{
		case 0:
			
			return;
		case 1:
			addUI(serv);
			break;
		case 2:
			deleteUI(serv);
			break;
		case 3:
			modifyUI(serv);
			break;
		case 4:
			showActivitati(serv);
			break;
		case 5:
			showActivitatiFiltered(serv);
			break;
		case 6:
			showActivitatiSorted(serv);
			break;
		case 7:
			showRaport(serv);
			break;
		case 8:
			try
			{
				serv.undo();
			}
			catch (ServiceException& error)
			{
				cout << error.what();
			}
			break;
		default:
			cout << "Optiune invalida!" << endl;
			break;
		}
	}
}

void UI::runApp(Service& serv)
{
	serv.loadFromFile();
	while (true)
	{
		cout << "Admin / User: ";
		string option;
		getline(cin, option);
		if (option == "admin" || option == "Admin")
			runAdmin(serv);
		else if (option == "user" || option == "User")
			runUser(serv);
		else
		{
			cout << "Bye bye!" << endl;
			break;
		}
	}
	serv.saveToFile();
}

bool UI::addCosUI(Service& serv)
{
	if (showActivitati(serv))
	{
		string titlu;
		cout << "Introduceti titlul activitatii: "; getline(cin, titlu);
		try
		{
			serv.addInCos(titlu);
			cout << "Activitatea a fost adaugata cu succes!" << endl;
			return true;
		}
		catch (BaseException& error)
		{
			cout << error.what();
			return false;
		}
	}
	else
		return false;
}

bool UI::deleteCosUI(Service& serv)
{
	try
	{
		serv.emptyCos();
		return true;
	}
	catch (BaseException& error)
	{
		cout << error.what();
		return false;
	}
}

void UI::generateActivitatiUI(Service& serv)
{
	string choice;
	cout << "Generati un numar aleatoriu de activitati? ATENTIE! Veti pierde activitatile curente din lista! (Y/N) ";
	while (true)
	{
		getline(cin, choice);
		if (choice == "N" || choice == "n" || choice == "No" || choice == "no")
			return;
		else if (choice == "Y" || choice == "y" || choice == "Yes" || choice == "yes")
		{
			int nr;
			while (true)
			{
				cout << "Introduceti numarul de activitati pe care il doriti: ";
				if (citesteInt(nr))
					break;
			}
			try
			{
				serv.generateActivitati(nr);
				cout << "Au fost generate " << nr << " activitati!\n";
			}
			catch (BaseException& error)
			{
				cout << error.what();
			}
			break;
		}
		else
		{
			cout << "Optiune invalida!\n";
			continue;
		}
	}
}

void UI::exportCosUI(Service& serv)
{
	string fisier;
	cout << "Introduceti numele fisierului unde vreti sa fie salvat: ";
	while (true)
	{
		getline(cin, fisier);
		if (fisier == "")
		{
			cout << "Va rog introduceti un nume de fisier!\n";
			continue;
		}
		regex fisier_valid(R"(.*\.csv$)");
		if (!regex_match(fisier, fisier_valid))
		{
			cout << "Va rog introduceti un nume de fisier cu extensia .csv\n";
			continue;
		}
		break;
	}
	try
	{
		serv.exportCosCSV(fisier);
		cout << "Operatia a avut loc cu succes! Verificati folder-ul proiectului!\n";
	}
	catch(BaseException& error)
	{
		cout << error.what();
	}
}

void UI::showActivitatiCos(const Service& serv)
{
	try
	{
		const auto& activitati = serv.getActivitatiCosService();
		int i = 0;
		for (const auto& a : activitati)
		{
			(void)a;
			i++;
		}
		cout << "Sunt " << i << " activitati in cos!\n";
	}
	catch (ServiceException& error)
	{
		cout << error.what();
	}
}

void UI::userMenu()
{
	cout << "~~~Welcome to Activitati~~~" << endl;
	cout << "1. Adauga o activitate in cosul tau" << endl;
	cout << "2. Goleste cosul" << endl;
	cout << "3. Genereaza activitati" << endl;
	cout << "4. Afiseaza activitatile" << endl;
	cout << "5. Exporta cosul (CSV)" << endl;
	cout << "0. Iesire" << endl;
}

void UI::runUser(Service& serv)
{
	while (true)
	{
		userMenu();
		int option = 0;

		while (true)
		{
			cout << "Alegeti optiunea: ";
			if (citesteInt(option))
				break;
		}

		switch (option)
		{
		case 0:
			return;
		case 1:
			if(addCosUI(serv))
				showActivitatiCos(serv);
			break;
		case 2:
			if(deleteCosUI(serv))
				showActivitatiCos(serv);
			break;
		case 3:
			generateActivitatiUI(serv);
			break;
		case 4:
			showActivitati(serv);
			break;
		case 5:
			exportCosUI(serv);
			break;
		default:
			cout << "Optiune invalida!" << endl;
			break;
		}
	}
	return;
}