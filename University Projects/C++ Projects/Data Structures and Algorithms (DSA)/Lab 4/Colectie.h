#pragma once
#include <utility>
#include <exception>

#define NULL_TELEM -1
typedef int TElem;
typedef std::pair<TElem, int> Pereche;

class IteratorColectie;

class Colectie
{
	friend class IteratorColectie;

private:
	int cp, prim, ultim, primLiber, dimensiune;
	Pereche* e;
	int* urm;
	int* prec;

	// Asigura ca exista loc in tablouri
	void ensureCapacity();

	int aloca();

	void dealoca(int i);
public:
		//constructorul implicit
		Colectie();

		//adauga un element in colectie
		void adauga(TElem e);

		//sterge o aparitie a unui element din colectie
		//returneaza adevarat daca s-a putut sterge
		bool sterge(TElem e);

		//verifica daca un element se afla in colectie
		bool cauta(TElem elem) const;

		//returneaza numar de aparitii ale unui element in colectie
		int nrAparitii(TElem elem) const;

		//adauga toate elementele colectiei b in colectia curenta
		void adaugaToateElementele(const Colectie& b);

		//intoarce numarul de elemente din colectie;
		int dim() const;

		//verifica daca colectia e vida;
		bool vida() const;

		//returneaza un iterator pe colectie
		IteratorColectie iterator() const;

		// destructorul colectiei
		~Colectie();

};

