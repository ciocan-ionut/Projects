#pragma once
#include<vector>
#include<utility>
#define NIL -999999
#define DELETED std::make_pair(NIL+1, NIL+1)

using namespace std;

typedef int TCheie;
typedef int TValoare;

typedef std::pair<TCheie, TValoare> TElem;

class IteratorMD;

class MD
{
	friend class IteratorMD;

private:
	TElem* elems;
	int cp;
	int lg;

	// functie de dispersie
	int hash(TCheie c) const
	{
		return abs(c) % cp;
	}

	// verificare patratica
	int verificare(TCheie c, int i) const
	{
		return (hash(c) + (i * (i + 1)) / 2) % cp;
	}

	// redimensionare
	void ensureCapacity();

public:
	// constructorul implicit al MultiDictionarului
	MD();

	// adauga o pereche (cheie, valoare) in MD	
	void adauga(TCheie c, TValoare v);

	//cauta o cheie si returneaza vectorul de valori asociate
	vector<TValoare> cauta(TCheie c) const;

	//sterge o cheie si o valoare 
	//returneaza adevarat daca s-a gasit cheia si valoarea de sters
	bool sterge(TCheie c, TValoare v);

	//returneaza numarul de perechi (cheie, valoare) din MD 
	int dim() const;

	//verifica daca MultiDictionarul e vid 
	bool vid() const;

	// returneaza diferenta dintre cheia maxima si cheia minima (presupunem valori intregi)
	// daca dictionarul este vid, se returneaza -1
	int diferentaCheieMaxMin() const;

	// se returneaza iterator pe MD
	IteratorMD iterator() const;

	// destructorul MultiDictionarului	
	~MD();



};

