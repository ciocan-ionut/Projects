#pragma once

class Teste
{
public:
	// Functie care apeleaza toate testele aplicatiei
	void static runTests();

	// Functie care testeaza domain-ul aplicatiei
	void static testDomain();

	// Functie care testeaaza repository-ul aplicatiei
	void static testRepository();

	// Functie care testeaza cosul cu activitati
	void static testCos();

	// Functie care testeaza validatorul aplicatiei
	void static testValidator();

	// Functie care testeaza service-ul aplicatiei
	void static testService();
};

