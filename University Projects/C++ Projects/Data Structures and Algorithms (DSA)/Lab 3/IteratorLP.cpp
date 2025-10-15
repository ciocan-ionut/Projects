#include "IteratorLP.h"
#include "Lista.h"
#include <exception>

IteratorLP::IteratorLP(const Lista& l):lista(l), curent(l.cap) {
	/* de adaugat */
}

IteratorLP::IteratorLP(const Lista& l, Lista::Nod* nod) : lista(l), curent(nod) {}

void IteratorLP::prim(){
	/* de adaugat */
	curent = lista.cap;
}

void IteratorLP::urmator(){
	/* de adaugat */
	if (valid())
		curent = curent->urmator;
	else
		throw std::exception("Iterator invalid!");
}

bool IteratorLP::valid() const{
	/* de adaugat */
	return curent != nullptr;
}

TElem IteratorLP::element() const{
	/* de adaugat */
	if (!valid())
		throw std::exception("Iterator invalid!");
	return curent->element;
}


