#include "IteratorMultime.h"
#include "Multime.h"


IteratorMultime::IteratorMultime(const Multime& m) : multime(m){
	crtIndex = 0;
}


void IteratorMultime::prim() {
	crtIndex = 0;
}


void IteratorMultime::urmator() {
	crtIndex++;
}


TElem IteratorMultime::element() const {
	return multime.vectorDinamic[crtIndex];
}

bool IteratorMultime::valid() const {
	return crtIndex < multime.dimVector;
}
