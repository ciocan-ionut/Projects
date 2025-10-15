#include "TestScurt.h"
#include <assert.h>
#include <vector>
#include "Colectie.h"
#include "IteratorColectie.h"





void testAll() { //apelam fiecare functie sa vedem daca exista
	Colectie c;
	assert(c.vida() == true);
	assert(c.dim() == 0); //adaug niste elemente
	c.adauga(5);
	c.adauga(1);
	c.adauga(10);
	c.adauga(7);
	c.adauga(1);
	c.adauga(11);
	c.adauga(-3);
	assert(c.dim() == 7);
	assert(c.cauta(10) == true);
	assert(c.cauta(16) == false);
	assert(c.nrAparitii(1) == 2);
	assert(c.nrAparitii(7) == 1);
	assert(c.sterge(1) == true);
	assert(c.sterge(6) == false);
	assert(c.dim() == 6);
	assert(c.nrAparitii(1) == 1);
	IteratorColectie ic = c.iterator();
	ic.prim();
	while (ic.valid()) {
		TElem e = ic.element();
		ic.urmator();
	}

	Colectie c2;
	c2.adaugaToateElementele(c);
	std::vector<int> v = { 5, 1, 10, 7, 11, -3 };
	IteratorColectie ic2 = c2.iterator();
	ic2.prim();
	int i = 0;
	while (ic2.valid()) 
	{
		TElem e = ic2.element();
		assert(e == v[i]);
		i++;
		ic2.urmator();
	}

	Colectie c3;
	c2.adaugaToateElementele(c3);
}