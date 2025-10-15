#include "MD.h"
#include "IteratorMD.h"
#include <exception>
#include <iostream>

using namespace std;

// Best Case: -
// Worst Case: -
// Total Case: Theta(n)
void MD::ensureCapacity()
{
	if (lg > cp / 2)
	{
		int oldCp = cp;
		cp *= 2;
		TElem* oldElems = elems;
		elems = new TElem[cp];
		for (int i = 0; i < cp; i++)
			elems[i] = TElem(NIL, NIL);

		lg = 0;
		for (int i = 0; i < oldCp; i++)
			if (oldElems[i] != DELETED && oldElems[i].first != NIL)
				adauga(oldElems[i].first, oldElems[i].second);

		delete[] oldElems;
	}
}

// Best Case: -
// Worst Case: -
// Total Case: Theta(n)
MD::MD() {
	cp = 13;
	lg = 0;
	elems = new TElem[cp];
	for (int i = 0; i < cp; i++)
		elems[i] = TElem(NIL, NIL);
}

// Best Case: Theta(1) (elementul se adauga pe prima pozitie gasita, fara coliziune)
// Worst Case: Theta(n) (toate pozitiile sunt ocupate)
// Total Case: O(n)
void MD::adauga(TCheie c, TValoare v) {
	ensureCapacity();

	int i = 0;
	int poz = 0;
	do
	{
		poz = verificare(c, i);
		if (elems[poz].first == NIL || elems[poz] == DELETED)
		{
			elems[poz] = TElem(c, v);
			lg++;
			return;
		}
		i++;
	} while (i < cp);
}

// Best Case: Theta(1) (elementul se gaseste pe prima pozitie sau nu se afla in MD)
// Worst Case: Theta(n) (toate pozitiile sunt ocupate)
// Total Case: O(n)
bool MD::sterge(TCheie c, TValoare v) {
	for (int i = 0; i < cp; i++)
	{
		int poz = verificare(c, i);
		if (elems[poz].first == NIL)
			return false;
		if (elems[poz].first == c && elems[poz].second == v)
		{
			elems[poz] = DELETED;
			lg--;
			return true;
		}
	}
	return false;
}

// Best Case: Theta(1) (cheia nu se afla in MD)
// Worst Case: Theta(n) (toate pozitiile sunt ocupate)
// Total Case: O(n)
vector<TValoare> MD::cauta(TCheie c) const {
	vector<TValoare> vectorValori;
	for (int i = 0; i < cp; i++)
	{
		int poz = verificare(c, i);
		if (elems[poz].first == NIL)
			break;
		if (elems[poz].first == c)
			vectorValori.push_back(elems[poz].second);
	}
	return vectorValori;
}


int MD::dim() const {
	return lg;
}


bool MD::vid() const {
	return lg == 0;
}

/*
subalgoritm diferentaCheieMaxMin
	Daca MD-ul este vid executa
		returneaza -1
	Sf. daca
	i <- 0
	Cat timp i < cp si (elems[i].first == NIL sau elems[i] == DELETED) executa
		i <- i + 1
	Sf. cat timp
	min <- elems[i].first
	max <- elems[i].first
	Pentru i <- i + 1, cp executa
		Daca elems[i].first != NIL si elems[i] != DELETED executa
			Daca elems[i].first < min executa
				min <- elems[i].first
			Sf. daca
			Daca elems[i].first > max executa
				max <- elems[i].first
			Sf. daca
		Sf. daca
	Sf. pentru
	returneaza max - min
Sf. subalgoritm
*/

// Best Case: -
// Worst Case: -
// Total Case: Theta(n) n = cp
int MD::diferentaCheieMaxMin() const
{
	if (vid())
		return -1;
	int i = 0;
	while (i < cp && (elems[i].first == NIL || elems[i] == DELETED))
		i++;
	int min = elems[i].first;
	int max = elems[i].first;
	for (i = i + 1; i < cp; i++)
	{
		if (elems[i].first != NIL && elems[i] != DELETED)
		{
			if (elems[i].first < min)
				min = elems[i].first;
			if (elems[i].first > max)
				max = elems[i].first;
		}
	}
	return max - min;
}

IteratorMD MD::iterator() const {
	return IteratorMD(*this);
}


MD::~MD() {
	delete[] elems;
}

