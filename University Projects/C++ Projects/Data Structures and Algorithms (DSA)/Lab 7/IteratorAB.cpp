#include "AB.h"
#include "IteratorAB.h"

IteratorInordine::IteratorInordine(const AB& _ab):ab(_ab) 
{
	prim();
}

void IteratorInordine::prim()
{
	// Eliberam stiva
	while (!stiva.empty()) 
		stiva.pop();

	// Pornim de la radacina arborelui
	int curent = ab.radacina;

	// Parcurgem arborele pana gasim prima frunza din stanga
	while (curent != -1) 
	{
		stiva.push(curent);
		curent = ab.elems[curent].getStang();
	}
}

bool IteratorInordine::valid()
{
	return !stiva.empty();
}

TElem IteratorInordine::element() 
{
	if(!valid())
		throw std::exception();
	return ab.elems[stiva.top()].getElem();
}

void IteratorInordine::urmator()
{
	if (!valid())
		throw std::exception();

	// Extragem nodul din stiva
	int nod = stiva.top(); stiva.pop();
	int curent = ab.elems[nod].getDrept();

	// Cautam urmatoarea frunza din subarborele drept
	while (curent != -1)
	{
		stiva.push(curent);
		curent = ab.elems[curent].getStang();
	}
}

IteratorPreordine::IteratorPreordine(const AB& _ab):ab(_ab)
{
	prim();
}

void IteratorPreordine::prim()
{
	// Eliberam stiva
	while (!stiva.empty())
		stiva.pop();

	// Adaugam radacina in stiva
	if (!ab.vid())
		stiva.push(ab.radacina);
}


bool IteratorPreordine::valid()
{
	return !stiva.empty();
}

TElem IteratorPreordine::element()
{
	if (!valid())
		throw std::exception();
	return ab.elems[stiva.top()].getElem();
}

void IteratorPreordine::urmator()
{
	if (!valid())
		throw std::exception();

	// Extragem nodul din stiva
	int nod = stiva.top(); stiva.pop();
	int dr = ab.elems[nod].getDrept();
	int st = ab.elems[nod].getStang();

	// Adaugam in stiva prima data dreapta, apoi stanga
	if (dr != -1) 
		stiva.push(dr);
	if (st != -1) 
		stiva.push(st);
}

IteratorPostordine::IteratorPostordine(const AB& _ab):ab(_ab)
{
	prim();
}

void IteratorPostordine::prim()
{
	while (!stiva.empty()) 
		stiva.pop();
	while (!ordine.empty()) 
		ordine.pop();

	if (ab.vid()) 
		return;
	stiva.push(ab.radacina);

	while (!stiva.empty()) 
	{
		// Extragem nodul din stiva
		int nod = stiva.top(); stiva.pop();
		ordine.push(nod); // Adaugam nodul in ordinea postordine
		int st = ab.elems[nod].getStang();
		int dr = ab.elems[nod].getDrept();

		// Adaugam in stiva prima data stanga, apoi dreapta (preordine modificata)
		if (st != -1) 
			stiva.push(st);
		if (dr != -1) 
			stiva.push(dr);
	}

	// Inversam ordinea pentru a obtine postordine
	std::stack<int> ordine_inversa;
	while (!ordine.empty()) 
	{
		ordine_inversa.push(ordine.top());
		ordine.pop();
	}
	while (!ordine_inversa.empty()) 
	{
		ordine.push(ordine_inversa.top());
		ordine_inversa.pop();
	}
}


bool IteratorPostordine::valid()
{
	return !ordine.empty();
}

TElem IteratorPostordine::element()
{
 	if(!valid())
		throw std::exception();
	return ab.elems[ordine.top()].getElem();
}

void IteratorPostordine::urmator()
{
	if (!valid())
		throw std::exception();
	ordine.pop();
}

IteratorLatime::IteratorLatime(const AB& _ab):ab(_ab)
{
	prim();
}

void IteratorLatime::prim()
{
	// Eliberam coada
	while (!coada.empty()) 
		coada.pop();

	// Adaugam radacina in coada
	if (!ab.vid()) 
		coada.push(ab.radacina);
}


bool IteratorLatime::valid()
{
	return !coada.empty();
}

TElem IteratorLatime::element()
{
	if (!valid())
		throw std::exception();
	return ab.elems[coada.front()].getElem();
}

void IteratorLatime::urmator()
{
	if (!valid()) 
		throw exception();

	// Extragem nodul din coada
	int nod = coada.front(); coada.pop();
	int st = ab.elems[nod].getStang();
	int dr = ab.elems[nod].getDrept();

	// Adaugam in coada prima data stanga, apoi dreapta
	if (st != -1) 
		coada.push(st);
	if (dr != -1) 
		coada.push(dr);
}
