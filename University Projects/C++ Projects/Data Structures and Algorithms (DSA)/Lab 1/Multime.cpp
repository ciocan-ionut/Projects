#include "Multime.h"
#include "IteratorMultime.h"

#include <iostream>

Multime::Multime() {
	cpVector = 1;
	vectorDinamic = new TElem[cpVector];
	dimVector = 0;
}


void Multime::ensureCapacity()
{
	if (cpVector <= dimVector)
	{
		TElem* newVector = new TElem[2 * cpVector];
		for (int i = 0; i < dimVector; i++)
			newVector[i] = vectorDinamic[i];
		cpVector *= 2;
		delete[] vectorDinamic;
		vectorDinamic = newVector;
	}
}


bool Multime::adauga(TElem elem) {
	//Best Case: Theta(1) (elementul exista deja pe prima pozitie)
	//Worst Case: Theta(n) (elementul nu se afla in multime)
	//Total: O(n)
	ensureCapacity();
	for (int i = 0; i < dimVector; i++)
		if (vectorDinamic[i] == elem)
			return false;
	vectorDinamic[dimVector++] = elem;
	return true;
}


void Multime::clearCapacity()
{
	if (cpVector > 2 * dimVector && cpVector > 1)
	{
		TElem* newVector = new TElem[cpVector / 2];
		for (int i = 0; i < dimVector; i++)
			newVector[i] = vectorDinamic[i];
		cpVector /= 2;
		delete[] vectorDinamic;
		vectorDinamic = newVector;
	}
}


bool Multime::sterge(TElem elem) {
	//Best Case: -
	//Worst Case: -
	//Total: Theta(n)
	for(int i = 0; i < dimVector; i++)
		if (vectorDinamic[i] == elem)
		{
			for (int j = i; j < dimVector - 1; j++)
				vectorDinamic[j] = vectorDinamic[j + 1];
			dimVector--;
			clearCapacity();
			return true;
		}
	return false;
}


bool Multime::cauta(TElem elem) const {
	//Best Case: Theta(1) (elementul cautat se afla pe prima pozitie)
	//Worst Case: Theta(n) (elementul se afla pe ultima pozitie sau nu exista)
	//Total: O(n)
	for (int i = 0; i < dimVector; i++)
		if (vectorDinamic[i] == elem)
			return true;
	return false;
}


int Multime::diferentaMaxMin() const
{
	//Best Case: -
	//Worst Case: -
	//Total: Theta(n)

	/*
	* Daca dimVector = 0 atunci
	*		returneaza -1
	* Sf. Daca
	* max <- vectorDinamic[0], min <- vectorDinamic[0]
	* Pentru i<-0, n executa
	*		Daca vectorDinamic[i] > max atunci
	*			max <- vectorDinamic[i]
	*		Sf. Daca
	*		Daca vectorDinamic[i] < min atunci
	*			min <- vectorDinamic[i]
	*		Sf. Daca
	* Sf. Pentru
	* returneaza max - min
	*/

	if (dimVector == 0)
		return -1;
	int max = vectorDinamic[0], min = vectorDinamic[0];
	for (int i = 0; i < dimVector; i++)
	{
		if (vectorDinamic[i] > max)
			max = vectorDinamic[i];
		if (vectorDinamic[i] < min)
			min = vectorDinamic[i];
	}
	return max - min;
}


int Multime::dim() const {
	return dimVector;
}

bool Multime::vida() const {
	return dimVector == 0;
}


Multime::~Multime() {
	delete[] vectorDinamic;
}



IteratorMultime Multime::iterator() const {
	return IteratorMultime(*this);
}

