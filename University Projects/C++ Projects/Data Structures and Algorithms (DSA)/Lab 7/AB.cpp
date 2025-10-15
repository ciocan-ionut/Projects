#include "AB.h"
#include "IteratorAB.h"
#include <exception>
#include <string>

// Best Case: -
// Worst Case: -
// Total Case: Theta(n) | n = numarul de noduri din arbore
void AB::ensureCapacity(int newCp)
{
	if (newCp <= cp)
		return;
	Nod* newElems = new Nod[newCp];
	for (int i = 0; i < lg; i++)
		newElems[i] = elems[i];
	delete[] elems;
	elems = newElems;
	cp = newCp;
}

// Best Case: -
// Worst Case: -
// Total Case: Theta(1)
AB::AB() 
{
	radacina = -1;
	cp = 10;
	lg = 0;
	elems = new Nod[cp];
	primLiber = 0;
}

// Best Case: -
// Worst Case: -
// Total Case: Theta(n) | n = n = numarul de noduri din arborele ab
AB::AB(const AB& ab) 
{
	radacina = ab.radacina;
	cp = ab.cp;
	lg = ab.lg;
	elems = new Nod[cp];
	primLiber = ab.primLiber;
	if (lg < cp)
		for (int i = 0; i < lg; i++)
			elems[i] = ab.elems[i];
}

// Best Case: -
// Worst Case: -
// Total Case: Theta(1)
AB::AB(TElem e)
{
	radacina = 0;
	cp = 10;
	lg = 1;
	elems = new Nod[cp];
	elems[radacina] = Nod(e, -1, -1);
	primLiber = 1;
}

// Best Case: -
// Worst Case: -
// Total Case: Theta(n) | n = n = numarul de noduri din arborele sursa
int AB::copyTree(const AB& sursa, int radacina)
{
	if (radacina == -1) 
		return -1;

	int nodNou = primLiber++;
	elems[nodNou] = Nod(sursa.elems[radacina].getElem(), -1, -1);

	int stangNou = copyTree(sursa, sursa.elems[radacina].getStang());
	int dreptNou = copyTree(sursa, sursa.elems[radacina].getDrept());

	elems[nodNou].setStang(stangNou);
	elems[nodNou].setDrept(dreptNou);

	return nodNou;
}

// Best Case: -
// Worst Case: -
// Total Case: Theta(n) | n = n = maximul dintre numarul de noduri din arborele stang si drept
AB::AB(const AB& st, TElem e, const AB& dr)
{
	cp = st.cp + dr.cp + 10;
	elems = new Nod[cp];
	primLiber = 0;

	radacina = primLiber++;
	elems[radacina] = Nod(e, -1, -1);

	int radSt = copyTree(st, st.radacina);
	elems[radacina].setStang(radSt);

	int radDr = copyTree(dr, dr.radacina);
	elems[radacina].setDrept(radDr);

	lg = 1 + st.lg + dr.lg;
}

// Best Case: -
// Worst Case: -
// Total Case: Theta(n) | n = n = numarul de noduri din arborele stang
void AB::adaugaSubSt(const AB& st)
{
	if (vid())
		throw std::exception();

	int radSt = copyTree(st, st.radacina);
	elems[radacina].setStang(radSt);
	lg += st.lg;
}

// Best Case: -
// Worst Case: -
// Total Case: Theta(n) | n = n = numarul de noduri din arborele drept
void AB::adaugaSubDr(const AB& dr)
{
	if (vid())
		throw std::exception();

	int radDr = copyTree(dr, dr.radacina);
	elems[radacina].setDrept(radDr);
	lg += dr.lg;
}

// Best Case: -
// Worst Case: -
// Total Case: Theta(1)
TElem AB::element() const
{
	if (vid())
		throw std::exception();
	return elems[radacina].getElem();
}

// Best Case: -
// Worst Case: -
// Total Case: Theta(n) | n = n = numarul de noduri din sursa
int AB::copySubTree(const Nod* sursa, int index, Nod* &dest, int &pozDest) const
{
	if (index == -1)
		return -1;

	int pozCurenta = pozDest;
	dest[pozDest++] = Nod(sursa[index].getElem(), -1, -1);

	int st = copySubTree(sursa, sursa[index].getStang(), dest, pozDest);
	int dr = copySubTree(sursa, sursa[index].getDrept(), dest, pozDest);

	dest[pozCurenta].setStang(st);
	dest[pozCurenta].setDrept(dr);

	return pozCurenta;
}

// Best Case: -
// Worst Case: -
// Total Case: Theta(n) | n = numarul de noduri din subarborele stang
AB AB::stang() const
{
	if (vid())
		throw std::exception();

	int indexSt = elems[radacina].getStang();
	if(indexSt == -1)
		return AB();

	AB rezultat;

	rezultat.radacina = copySubTree(this->elems, indexSt, rezultat.elems, rezultat.primLiber);
	rezultat.lg = rezultat.primLiber;

	return rezultat;
}

// Best Case: -
// Worst Case: -
// Total Case: Theta(n) | n = numarul de noduri din subarborele drept
AB AB::drept() const
{
	if (vid())
		throw std::exception();

	int indexDr = elems[radacina].getDrept();
	if (indexDr == -1)
		return AB();

	AB rezultat;

	rezultat.radacina = copySubTree(this->elems, indexDr, rezultat.elems, rezultat.primLiber);
	rezultat.lg = rezultat.primLiber;

	return rezultat;
}

AB::~AB() 
{
	delete[] elems;
}

// Best Case: -
// Worst Case: -
// Total Case: Theta(1)
bool AB::vid() const
{
	return lg == 0;
}

/*
* subalgoritm minInTree(index: Intreg, min: Intreg)
*	daca index = -1 atunci
*		returneaza min
*	sf. daca
*	daca min > elems[index].getElem() atunci
*		min <- elems[index].getElem()
*	sf. daca
*	minSt <- minInTree(elems[index].getStang(), min)
*	minDr <- minInTree(elems[index].getDrept(), min)
*	returneaza min(minSt, minDr)
* sf. subalg.
*/

// Best Case: -
// Worst Case: -
// Total Case: Theta(n) | n = numarul de noduri din arbore
int AB::minInTree(int index, int min) const
{
	if (index == -1)
		return min;
	if (min > elems[index].getElem())
		min = elems[index].getElem();
	int minSt = minInTree(elems[index].getStang(), min);
	int minDr = minInTree(elems[index].getDrept(), min);
	return std::min(minSt, minDr);
}

int AB::valoareMinima() const
{
	if (vid())
		return NULL;

	return minInTree(radacina, INT_MAX);
}

IteratorAB* AB::iterator(string s) const {
	if (s=="preordine")
		return new IteratorPreordine(*this);
	if (s=="inordine")
		return new IteratorInordine(*this);
	if (s=="postordine")
		return new IteratorPostordine(*this);
	if (s=="latime")
		return new IteratorLatime(*this);
	return nullptr;
};
