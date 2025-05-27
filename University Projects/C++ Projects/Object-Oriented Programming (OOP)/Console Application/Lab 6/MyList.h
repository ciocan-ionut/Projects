#pragma once

#include "IteratorMyList.h"

template <typename TElement>
class IteratorMyList;

template <typename TElement>
class MyList
{
private:
	int lg, cp;
	TElement* elems;

	/// Functie care mareste capacitatea vectorului in caz de overflow
	void ensureCapacity();

public:
	MyList() : lg{ 0 }, cp{ 1 }, elems{ new TElement[cp] } {}

	/// Functie care adauga o activitate in lista de elemente
	/// @param elem este activitatea care urmeaza sa fie adaugata
	void push_back(const TElement& elem);

	/// Functie care returneaza lungimea listei de elemente
	/// @returns lungimea listei
	int size() const
	{
		return lg;
	}

	/// Functie care sterge de pe pozitia 'index' o activitate din lista de elemente 
	/// @param index este pozitia activitatii care urmeaza sa fie stearsa
	void erase(const int& index);

	/// Functie care adauga pe pozitia 'index' o activitate in lista de elemente
	/// @param index este pozitia pe care urmeaza sa fie adaugata activitatea
	/// @param activity este activitatea care urmeaza sa fie adaugata
	void insert(const int& index, const TElement& activity);

	/// Functie care suprascrie operatorul pentru a accesa direct elementele
	/// @param index este pozitia activitatii din lista
	/// @returns activitatea de pe pozitia 'index'
	TElement& operator[](const int& index)
	{
		return elems[index];
	}

	/// Functie care suprascrie operatorul pentru a accesa direct elementele
	/// @param index este pozitia activitatii din lista
	/// @returns activitatea de pe pozitia 'index'
	const TElement& operator[](const int& index) const
	{
		return elems[index];
	}

	// Rule of 3

	// Operatorul de asignment
	MyList& operator=(const MyList& ot) 
	{
		if (this == &ot) return *this;
		delete[] elems;
		cp = ot.cp;
		lg = ot.lg;
		elems = new TElement[lg];
		for (int i = 0; i < lg; i++)
			elems[i] = ot.elems[i];
		return *this;
	}

	// Functia de copiere
	MyList(const MyList& ot);

	// Destructorul
	~MyList()
	{
		delete[] elems;
	}

	friend class IteratorMyList<TElement>;
	IteratorMyList<TElement> begin();
	IteratorMyList<TElement> end();
	IteratorMyList<TElement> begin() const;
	IteratorMyList<TElement> end() const;
};

template <typename TElement>
void MyList<TElement>::ensureCapacity()
{
	if (lg == cp)
	{
		TElement* temp = new TElement[cp * 2];
		for (int i = 0; i < lg; i++)
			temp[i] = elems[i];
		delete[] elems;
		elems = temp;
		cp *= 2;
	}
}

template <typename TElement>
void MyList<TElement>::push_back(const TElement& elem)
{
	ensureCapacity();
	elems[lg++] = elem;
}

template <typename TElement>
void MyList<TElement>::erase(const int& index)
{
	for (int i = index; i < lg - 1; i++)
		elems[i] = elems[i + 1];
	lg--;
}

template <typename TElement>
void MyList<TElement>::insert(const int& index, const TElement& activity)
{
	ensureCapacity();
	for (int i = lg; i > index; --i)
		elems[i] = elems[i - 1];
	elems[index] = activity;
	lg++;
}

template <typename TElement>
MyList<TElement>::MyList(const MyList& ot) : lg{ ot.lg }, cp{ ot.cp }, elems{ new TElement[ot.lg] }
{
	for (int i = 0; i < lg; i++)
		elems[i] = ot.elems[i];
}

template <typename TElement>
IteratorMyList<TElement> MyList<TElement>::begin()
{
	return IteratorMyList<TElement>(*this);
}

template <typename TElement>
IteratorMyList<TElement> MyList<TElement>::end()
{
	return IteratorMyList<TElement>(*this, lg);
}

template <typename TElement>
IteratorMyList<TElement> MyList<TElement>::begin() const
{
	return IteratorMyList<TElement>(*this);
}

template <typename TElement>
IteratorMyList<TElement> MyList<TElement>::end() const
{
	return IteratorMyList<TElement>(*this, lg);
}