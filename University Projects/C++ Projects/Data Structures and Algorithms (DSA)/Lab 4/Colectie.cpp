#include "Colectie.h"
#include "IteratorColectie.h"
#include <iostream>

using namespace std;

// Best Case: -
// Worst Case: -
// Total Case: Theta(n)
void Colectie::ensureCapacity()
{
	if (primLiber == -1)
	{
		int newCp = cp * 2;
		Pereche* newE = new Pereche[newCp];
		int* newUrm = new int[newCp];
		int* newPrec = new int[newCp];

		for (int i = 0; i < cp; i++)
		{
			newE[i] = e[i];
			newUrm[i] = urm[i];
			newPrec[i] = prec[i];
		}

		for (int i = cp; i < newCp - 1; i++)
			newUrm[i] = i + 1;
		newUrm[newCp - 1] = -1;

		delete[] e;
		delete[] urm;
		delete[] prec;

		e = newE;
		urm = newUrm;
		prec = newPrec;
		primLiber = cp;
		cp = newCp;
	}
}

// Best Case: Theta(1)
// Worst Case: Theta(n)
// Total Case: O(n)
int Colectie::aloca()
{
	ensureCapacity();
	int i = primLiber;
	primLiber = urm[primLiber];
	return i;
}

// Best Case: -
// Worst Case: -
// Total Case: Theta(1)
void Colectie::dealoca(int i)
{
	urm[i] = primLiber;
	primLiber = i;
}

// Best Case: -
// Worst Case: -
// Total Case: Theta(n)
Colectie::Colectie() {
	cp = 10;
	e = new Pereche[cp];
	urm = new int[cp];
	prec = new int[cp];
	prim = -1;
	ultim = -1;
	primLiber = 0;
	dimensiune = 0;

	for (int i = 0; i < cp - 1; i++)
		urm[i] = i + 1;
	urm[cp - 1] = -1;
}

// Best Case: Theta(1) (elementul se afla deja in colectie si e pe prima pozitie)
// Worst Case: Theta(n) (elementul nu se afla in colectie sau e pe ultima pozitie)
// Total Case: O(n)
void Colectie::adauga(TElem elem) {
	int curent = prim;
	while (curent != -1)
	{
		if (e[curent].first == elem)
		{
			e[curent].second++;
			dimensiune++;
			return;
		}
		curent = urm[curent];
	}

	int poz = aloca();
	e[poz] = make_pair(elem, 1);
	urm[poz] = -1;
	prec[poz] = ultim;

	if (ultim != -1)
		urm[ultim] = poz;
	ultim = poz;

	if (prim == -1)
		prim = poz;

	dimensiune++;
}

// Best Case: Theta(1) (elementul se afla pe prima pozitie)
// Worst Case: Theta(n) (elementul nu se afla in colectie sau se afla pe ultima pozitie)
// Total Case: O(n)
bool Colectie::sterge(TElem elem) {
	int curent = prim;
	while (curent != -1)
	{
		if (e[curent].first == elem)
		{
			if (e[curent].second > 1)
			{
				e[curent].second--;
				dimensiune--;
				return true;
			}
			else
			{
				int anterior = prec[curent];
				int urmator = urm[curent];

				if (anterior != -1)
					urm[anterior] = urmator;
				else
					prim = urmator;

				if (urmator != -1)
					prec[urmator] = anterior;
				else
					ultim = anterior;

				dealoca(curent);
				dimensiune--;
				return true;
			}
		}
		curent = urm[curent];
	}
	return false;
}

// Best Case: Theta(1) (elementul se afla pe prima pozitie)
// Worst Case: Theta(n) (elementul nu se afla in colectie sau se afla pe ultima pozitie)
// Total Case: O(n)
bool Colectie::cauta(TElem elem) const {
	int curent = prim;
	while (curent != -1)
	{
		if (e[curent].first == elem)
			return true;
		curent = urm[curent];
	}
	return false;
}

// Best Case: Theta(1) (elementul se afla pe prima pozitie)
// Worst Case: Theta(n) (elementul nu se afla in colectie sau se afla pe ultima pozitie)
// Total Case: O(n)
int Colectie::nrAparitii(TElem elem) const {
	int curent = prim;
	while (curent != -1)
	{
		if (e[curent].first == elem)
			return e[curent].second;
		curent = urm[curent];
	}
	return 0;
}

// Best Case: 
// Worst Case: O(dimB * dimCur)
// Total Case: Theta(n)

/* subalgoritm adaugaToateElementele(Colectie b)
      curent <- prim
	  cat timp (curent != -1) executa
		frecventa <- b.nrAparitii(e[curent].first)
		cat timp (frecventa > 0) executa
			adauga(e[curent].first)
			frecventa <- frecventa - 1
		sfarsit cat timp
		curent <- curent[urm]
	  sfarit cat timp
   sfarsit subalgoritm
*/
void Colectie::adaugaToateElementele(const Colectie& b) 
{
	int curent = b.prim;
	while (curent != -1)
	{
		int frecventa = b.nrAparitii(e[curent].first);
		while (frecventa > 0)
		{
			adauga(e[curent].first);
			frecventa--;
		}
		curent = curent[urm];
	}
}

int Colectie::dim() const {
	return dimensiune;
}


bool Colectie::vida() const {
	return dimensiune == 0;
}

IteratorColectie Colectie::iterator() const {
	return  IteratorColectie(*this);
}


Colectie::~Colectie() {
	delete[] e;
	delete[] urm;
	delete[] prec;
}


