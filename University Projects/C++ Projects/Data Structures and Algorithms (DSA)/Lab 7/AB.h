#pragma once
#include <string>

#define NIL INT_MIN
using namespace std;

typedef int TElem;

class AB;

class IteratorAB;

class Nod
{
private:
	TElem elem;
	int stang;
	int drept;

public:
	Nod() : elem(NIL), stang(-1), drept(-1) {}
	Nod(TElem e, int s, int d) : elem(e), stang(s), drept(d) {}
	TElem getElem() const { return elem; }
	int getStang() const { return stang; }
	int getDrept() const { return drept; }
	void setStang(int s) { stang = s; }
	void setDrept(int d) { drept = d; }
};

class AB {

private:
	int radacina;
	Nod* elems;
	int cp;
	int lg;
	int primLiber;

	void ensureCapacity(int newCp);
	int copyTree(const AB& sursa, int radacina);
	int copySubTree(const Nod* sursa, int index, Nod*& dest, int& pozDest) const;

public:
	friend class IteratorAB;
	friend class IteratorPreordine;
	friend class IteratorInordine;
	friend class IteratorPostordine;
	friend class IteratorLatime;

	//constructorul implicit
	AB();

	//contructor de copiere
	AB(const AB& ab);

	//creeaza un arbore binar care se reduce la o frunza
	AB(TElem elem);

	//constructor arbore binar
	AB(const AB& st, TElem elem, const AB& dr);

	//adauga unui arbore binar subarborele stang
	//arunca exceptie daca arborele este vid
	void adaugaSubSt(const AB& st);

	//adauga unui arbore binar subarborele drept
	//arunca exceptie daca arborele este vid
	void adaugaSubDr(const AB& dr);

	//verifica daca arborele este vid
   	bool vid() const;

	//accesare element din radacina
	//arunca exceptie daca arborele este vid
	TElem element() const;

	//accesare subarbore stang
	//arunca exceptie daca arborele este vid
	AB stang() const;

	//accesare subarbore drept
	//arunca exceptie daca arborele este vid
	AB drept() const;

	int minInTree(int index, int min) const;

	//gaseste si returneaza valoarea minima din arbore
	//daca arborele este vid, returneaza NULL_TVALOARE
	int valoareMinima() const;

	//iteratori pe arborele binar (ordine="preordine", "postordine", "inordine", "latime")
	IteratorAB* iterator(string ordine) const;

	// destructorul arborelui binar
	~AB();
};