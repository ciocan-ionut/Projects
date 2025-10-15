#include "IteratorMD.h"
#include "MD.h"

using namespace std;

IteratorMD::IteratorMD(const MD& _md): md(_md) {
	poz = 0;
	for (int i = 0; i < md.cp; i++)
		if (md.elems[i].first != NIL && md.elems[i] != DELETED)
			pozitiiValide.push_back(i);
}

TElem IteratorMD::element() const{
	if (valid())
		return md.elems[pozitiiValide[poz]];
	else
		throw exception();
}

bool IteratorMD::valid() const {
	return poz < pozitiiValide.size();
}

void IteratorMD::urmator() {
	if (valid())
		poz++;
	else
		throw exception();
}

void IteratorMD::prim() {
	poz = 0;
}

