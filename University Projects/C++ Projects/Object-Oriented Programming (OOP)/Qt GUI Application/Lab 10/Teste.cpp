#include <assert.h>
#include "Teste.h"
#include "Activitate.h"
#include "Repository.h"
#include "Validator.h"
#include "Service.h"
#include "CosActivitati.h"

void Teste::runTests()
{
	testDomain();
	testRepository();
	testCos();
	testValidator();
	testService();
}

void Teste::testDomain()
{
	string titlu = "Alergat", descriere = "...", tip = "Sport";
	int durata = 20;
	Activitate a(titlu, descriere, tip, durata);
	assert(a.getTitlu() == titlu);
	assert(a.getDescriere() == descriere);
	assert(a.getTip() == tip);
	assert(a.getDurata() == durata);
	Activitate a1(titlu, descriere, tip, durata);
	string titlu2 = "Sprint", descriere2 = "...", tip2 = "Sport";
	Activitate a2(titlu2, descriere, tip, durata);
	assert(a == a1);
	assert((a == a2) == false);
}

void Teste::testRepository()
{
	Repository repo;
	string titlu = "Alergat", descriere = "...", tip = "Sport";
	int durata = 20;
	Activitate a(titlu, descriere, tip, durata);

	// Adaugare
	assert(repo.addActivitate(a) == true);
	const auto& testAddActivitati = repo.getActivitati();
	assert(testAddActivitati.size() == 1);
	try
	{
		repo.addActivitate(a);
		assert(false);
	}
	catch (RepoException& err)
	{
		assert(strcmp(err.what(), "Activitatea exista deja in lista ta!\n") == 0);
		assert(true);
	}

	// Stergere
	repo.deleteActivitateByIndex(0);
	const auto& testDeleteActivitati = repo.getActivitati();
	assert(testDeleteActivitati.size() == 0);

	// Modificare
	string titlu2 = "Sprint", descriere2 = "...", tip2 = "Atletism";
	Activitate a2(titlu2, descriere, tip2, durata);
	repo.addActivitate(a);
	assert(repo.getActivitateByIndex(0) == a);

	assert(repo.modifyActivitateByIndex(0, a2) == true);
	assert(repo.getActivitateByIndex(0) == a2);

	try
	{
		repo.modifyActivitateByIndex(0, a2);
		assert(false);
	}
	catch (RepoException)
	{
		assert(true);
	}

	repo.addActivitate(a);
	Activitate a3(titlu, descriere, tip2, durata);
	assert(repo.modifyActivitateByIndex(0, a3) == true);
	assert(repo.getActivitateByIndex(0) == a3);
}

void Teste::testCos()
{
	CosActivitati cos;
	string titlu = "Alergat", descriere = "...", tip = "Sport";
	int durata = 20;
	Activitate a(titlu, descriere, tip, durata);

	// Adaugare
	cos.addActivitateInCos(a);
	auto activitati = cos.getActivitatiCos();
	assert(activitati[0] == a);

	// Stergere
	cos.addActivitateInCos(a);
	cos.addActivitateInCos(a);
	cos.addActivitateInCos(a);
	activitati = cos.getActivitatiCos();
	assert(activitati.size() == 4);
	cos.deleteCos();
	activitati = cos.getActivitatiCos();
	assert(activitati.size() == 0);
}

void Teste::testValidator()
{
	string titlu = "Alergat", descriere = "...", tip = "Sport";
	int durata = 20;
	Activitate a(titlu, descriere, tip, durata);
	assert(Validator::validateActivitate(a) == true);

	string titlu_invalid = "", descriere_invalida = "", tip_invalid = "";
	int durata_invalida = -1;
	Activitate invalid(titlu_invalid, descriere_invalida, tip_invalid, durata_invalida);
	try
	{
		Validator::validateActivitate(invalid);
		assert(false);
	}
	catch(ValidatorException)
	{
		assert(true);
	}
}

void Teste::testService()
{
	Repository repo;
	CosActivitati cos;
	Service serv{ repo, cos };

	string titlu = "Alergat", descriere = "...", tip = "Sport";
	int durata = 20;
	
	// Raport
	try
	{
		auto raport = serv.createMap();
		assert(false);
	}
	catch (ServiceException)
	{
		assert(true);
	}

	// Undo
	try
	{
		serv.undo();
		assert(false);
	}
	catch (ServiceException)
	{
		assert(true);
	}

	// Adaugare
	assert(serv.addService(titlu, descriere, tip, durata) == true);
	const auto& activitati = serv.getActivitatiService();
	assert(activitati.size() == 1);

	// Stergere
	try
	{
		serv.deleteService(1);
		assert(false);
	}
	catch (ServiceException)
	{
		assert(true);
	}

	assert(serv.deleteService(0) == true);

	try
	{
		serv.getActivitatiService();
		assert(false);
	}
	catch (ServiceException)
	{
		assert(true);
	}

	// Modificare
	try
	{
		serv.modifyService(1, titlu, descriere, tip, durata);
		assert(false);
	}
	catch (ServiceException)
	{
		assert(true);
	}

	serv.addService(titlu, descriere, tip, durata);
	string titlu_invalid = "", descriere_invalida = "", tip_invalid = "";
	int durata_invalida = -1;
	try
	{
		serv.modifyService(0, titlu_invalid, descriere_invalida, tip_invalid, durata_invalida);
		assert(false);
	}
	catch (ServiceException)
	{
		assert(true);
	}

	string titlu2 = "Sprint", descriere2 = "....", tip2 = "Scoala";
	Activitate a2{ titlu2, descriere, tip, durata };
	assert(serv.modifyService(0, titlu2, descriere, tip, durata) == true);
	assert(serv.getActivitatiService()[0] == a2);
	serv.deleteService(0);

	// Filtrare
	serv.addService(titlu, descriere, tip, durata);
	serv.addService(titlu, descriere, tip2, durata);
	serv.addService(titlu, descriere2, tip2, durata);
	serv.addService(titlu, descriere2, tip, durata);
	assert(serv.getActivitatiService().size() == 4);

	auto listaFiltrata = serv.filterService(&Activitate::getTip, tip);
	assert(listaFiltrata.size() == 2);

	listaFiltrata = serv.filterService(&Activitate::getDescriere, descriere);
	assert(listaFiltrata.size() == 2);

	try
	{
		serv.filterService(&Activitate::getTip, tip_invalid);
		assert(false);
	}
	catch (ValidatorException)
	{
		assert(true);
	}

	string tip_negasit = "Aleluia";
	try
	{
		serv.filterService(&Activitate::getTip, tip_negasit);
		assert(false);
	}
	catch (ServiceException)
	{
		assert(true);
	}

	serv.deleteService(0);
	serv.deleteService(0);
	serv.deleteService(0);
	serv.deleteService(0);

	// Sortare
	string titlu_sort1 = "A", titlu_sort2 = "B", titlu_sort3 = "C";
	string descriere_sort1 = "C", descriere_sort2 = "B", descriere_sort3 = "A";
	string tip_sort1 = "B", tip_sort2 = "A";
	int durata_sort1 = 70, durata_sort2 = 20, durata_sort3 = 50;

	serv.addService(titlu_sort1, descriere_sort1, tip_sort1, durata_sort1);
	serv.addService(titlu_sort2, descriere_sort2, tip_sort2, durata_sort2);
	serv.addService(titlu_sort3, descriere_sort3, tip_sort2, durata_sort3);

	bool ascending = true;
	auto listaSortata = serv.sortedService(&Activitate::compareTitlu, ascending);
	assert(listaSortata[0] == serv.getActivitatiService()[0]);
	assert(listaSortata[1] == serv.getActivitatiService()[1]);
	assert(listaSortata[2] == serv.getActivitatiService()[2]);

	listaSortata = serv.sortedService(&Activitate::compareDescriere, ascending);
	assert(listaSortata[0] == serv.getActivitatiService()[2]);
	assert(listaSortata[1] == serv.getActivitatiService()[1]);
	assert(listaSortata[2] == serv.getActivitatiService()[0]);

	listaSortata = serv.sortedService(&Activitate::compareTipSiDurata, ascending);
	assert(listaSortata[0] == serv.getActivitatiService()[1]);
	assert(listaSortata[1] == serv.getActivitatiService()[2]);
	assert(listaSortata[2] == serv.getActivitatiService()[0]);

	ascending = false;
	listaSortata = serv.sortedService(&Activitate::compareTitlu, ascending);
	assert(listaSortata[0] == serv.getActivitatiService()[2]);
	assert(listaSortata[1] == serv.getActivitatiService()[1]);
	assert(listaSortata[2] == serv.getActivitatiService()[0]);

	listaSortata = serv.sortedService(&Activitate::compareDescriere, ascending);
	assert(listaSortata[0] == serv.getActivitatiService()[0]);
	assert(listaSortata[1] == serv.getActivitatiService()[1]);
	assert(listaSortata[2] == serv.getActivitatiService()[2]);

	listaSortata = serv.sortedService(&Activitate::compareTipSiDurata, ascending);
	assert(listaSortata[0] == serv.getActivitatiService()[0]);
	assert(listaSortata[1] == serv.getActivitatiService()[2]);
	assert(listaSortata[2] == serv.getActivitatiService()[1]);

	ascending = true;
	serv.deleteService(0);
	serv.deleteService(0);
	serv.deleteService(0);
	serv.addService(titlu_sort3, descriere_sort3, tip_sort2, durata_sort3);
	serv.addService(titlu_sort1, descriere_sort1, tip_sort1, durata_sort1);
	serv.addService(titlu_sort2, descriere_sort2, tip_sort2, durata_sort2);
	listaSortata = serv.sortedService(&Activitate::compareTitlu, ascending);
	listaSortata = serv.sortedService(&Activitate::compareDescriere, ascending);
	listaSortata = serv.sortedService(&Activitate::compareTipSiDurata, ascending);

	ascending = false;
	serv.deleteService(0);
	serv.deleteService(0);
	serv.deleteService(0);
	serv.addService(titlu_sort3, descriere_sort3, tip_sort2, durata_sort3);
	serv.addService(titlu_sort1, descriere_sort1, tip_sort1, durata_sort1);
	serv.addService(titlu_sort2, descriere_sort2, tip_sort2, durata_sort2);
	listaSortata = serv.sortedService(&Activitate::compareDescriere, ascending);
	listaSortata = serv.sortedService(&Activitate::compareTipSiDurata, ascending);

	// Adaugare in cos
	try
	{
		serv.addInCos(titlu_invalid);
		assert(false);
	}
	catch (ValidatorException)
	{
		assert(true);
	}

	try
	{
		serv.addInCos(titlu);
		assert(false);
	}
	catch (ServiceException)
	{
		assert(true);
	}

	serv.addInCos(titlu_sort1);
	auto activities = serv.getActivitatiCosService();
	assert(activities.size() == 1);

	// Generare
	try
	{
		serv.generateActivitati(-1);
		assert(false);
	}
	catch (ServiceException)
	{
		assert(true);
	}
	serv.generateActivitati(5);
	activities = serv.getActivitatiService();
	assert(activitati.size() == 5);
	serv.exportCosCSV("test.csv");

	// Stergere
	serv.emptyCos();
	try
	{
		serv.getActivitatiCosService();
		assert(false);
	}
	catch (ServiceException)
	{
		assert(true);
	}

	// Export
	try
	{
		serv.exportCosCSV("test.csv");
		assert(false);
	}
	catch (ServiceException)
	{
		assert(true);
	}

	// Raport
	auto raport = serv.createMap();
	for (const auto& r : raport)
	{
		r.second.getTip();
		r.second.getCantitate();
	}

	// Undo
	serv.undo();
	serv.deleteService(0);
	serv.undo();
	serv.modifyService(0, titlu, "", "", -1);
	serv.undo();
}