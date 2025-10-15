#include "IteratorColectie.h"
#include "Colectie.h"


IteratorColectie::IteratorColectie(const Colectie& c): col(c) {
	prim();
}

void IteratorColectie::prim() {
	curent = col.prim;
	frecvCurent = 1;
}


void IteratorColectie::urmator() {
	if (!valid())
		throw std::exception();
	if (frecvCurent < col.e[curent].second)
		frecvCurent++;
	else
	{
		curent = col.urm[curent];
		frecvCurent = 1;
	}
}


bool IteratorColectie::valid() const {
	return curent != -1;
}



TElem IteratorColectie::element() const {
	if (!valid())
		throw std::exception();
	return col.e[curent].first;
}
