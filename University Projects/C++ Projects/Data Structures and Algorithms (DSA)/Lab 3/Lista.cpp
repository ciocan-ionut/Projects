
#include <exception>

#include "IteratorLP.h"
#include "Lista.h"

#include <iostream>

Lista::Lista() : cap(nullptr), coada(nullptr), dimensiune(0) {
	/* de adaugat */
}

bool Lista::ePar(const Nod& n)
{
	return n.element % 2;
}

/*
* filtreaza(Conditie cond)
*	Nod anterior<-nullptr
*	Nod curent<-cap
*	Cat timp curent != nullptr executa:
*		Daca nu respecta conditia atunci
*			Nod deSters<-curent
*			Daca anterior = nullptr atunci
*				cap<-[curent].urmator
*				curent<-cap
*			Altfel
*				[anterior].urmator<-[curent].urmator
*				curent<-[curent].urmator
*			Sf. Daca
*			elibereaza memoria pentru deSters
*			dimensiune<-dimensiune-1
*		Altfel
*			anterior<-curent
*			curent<-[curent].urmator
*		Sf. Daca
*	Sf. Cat timp
* Sf. filtreaza
*/
void Lista::filtreaza(std::function<bool(const TElem&)> cond) {
	// Best Case: -
	// Worst Case: -
	// Total: Theta(n)
	Nod* anterior = nullptr;
	Nod* curent = cap;

	while (curent != nullptr) {
		if (!cond(curent->element)) {
			Nod* deSters = curent;
			if (anterior == nullptr) {
				cap = curent->urmator;
				curent = cap;
			}
			else {
				anterior->urmator = curent->urmator;
				curent = curent->urmator;
			}
			delete deSters;
			dimensiune--;
		}
		else {
			anterior = curent;
			curent = curent->urmator;
		}
	}
}

int Lista::dim() const {
	return dimensiune;
}


bool Lista::vida() const {
	return cap == nullptr;
}

IteratorLP Lista::prim() const {
    return IteratorLP(*this);
}

TElem Lista::element(IteratorLP poz) const {
	if (!poz.valid())
		throw std::exception("Pozitie invalida!");
	return poz.element();
}

TElem Lista::sterge(IteratorLP& poz) {
	// Best Case: Theta(1) (cand elementul se afla pe prima pozitie)
	// Worst Case: Theta(n) (cand elementul se afla la final sau pozitia e invalida)
	// Total: O(n)
	if (!poz.valid()) 
		throw std::exception("Iterator invalid");

	Nod* anterior = nullptr;
	Nod* curent = cap;

	while (curent != nullptr && curent != poz.curent) 
	{
		anterior = curent;
		curent = curent->urmator;
	}

	if (curent == nullptr) 
		throw std::exception("Pozitie invalida");

	TElem toDelete = curent->element;

	if (anterior == nullptr) 
		cap = curent->urmator;
	else 
		anterior->urmator = curent->urmator;

	if (curent->urmator == nullptr)
		coada = anterior;

	poz.curent = curent->urmator;
	delete curent;
	dimensiune--;
	return toDelete;
}

IteratorLP Lista::cauta(TElem e) const{
	// Best Case: Theta(1) (cand elementul se afla pe prima pozitie)
	// Worst Case: Theta(n) (cand elementul se afla la final sau elementul nu exista)
	// Total: O(n)
	Nod* curent = cap;
	while (curent != nullptr)
	{
		if (curent->element == e)
			return IteratorLP(*this, curent);
		curent = curent->urmator;
	}
	return IteratorLP(*this, nullptr);
}

TElem Lista::modifica(IteratorLP poz, TElem e) {
	// Best Case: -
	// Worst Case: -
	// Total: Theta(1)
	if (!poz.valid())
		throw std::exception("Pozitie invalida");

	Nod* curent = poz.curent;
	TElem vechi = curent->element;
	curent->element = e;
	return vechi;
}

void Lista::adauga(IteratorLP& poz, TElem e) {
	// Best Case: Theta(1) (adaugam pe prima pozitie)
	// Worst Case: Theta(n) (adaugam pe ultima pozitie sau pozitia e invalida)
	// Total: O(n)
	if (!poz.valid()) 
		throw std::exception("Iterator invalid");

	Nod* nou = new Nod(e);
	Nod* anterior = nullptr;
	Nod* curent = cap;

	while (curent != nullptr && curent != poz.curent) 
	{
		anterior = curent;
		curent = curent->urmator;
	}

	if (curent == nullptr) 
		throw std::exception("Pozitie invalida");

	if (anterior == nullptr) 
	{
		nou->urmator = cap;
		cap = nou;
	}
	else 
	{
		anterior->urmator = nou;
		nou->urmator = curent;
	}

	if (nou->urmator == nullptr) 
	{
		coada = nou;
	}

	poz.curent = nou;
	dimensiune++;
}

void Lista::adaugaInceput(TElem e) {
	// Best Case: -
	// Worst Case: -
	// Total: Theta(1)
	Nod* nou = new Nod(e);
	if (vida())
		cap = coada = nou;
	else
	{
		nou->urmator = cap;
		cap = nou;
	}
	dimensiune++;
}

void Lista::adaugaSfarsit(TElem e) {
	// Best Case: -
	// Worst Case: -
	// Total: Theta(1)
	Nod* nou = new Nod(e);
	if (vida())
		cap = coada = nou;
	else
	{
		coada->urmator = nou;
		coada = nou;
	}
	dimensiune++;
}

Lista::~Lista() {
	// Best Case: -
	// Worst Case: -
	// Total: Theta(n)
	Nod* curent = cap;
	while (curent != nullptr)
	{
		Nod* toDelete = curent;
		curent = curent->urmator;
		delete toDelete;
	}
}
