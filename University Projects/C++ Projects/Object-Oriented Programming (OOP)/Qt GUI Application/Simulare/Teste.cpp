#include "Teste.h"
#include "Depozit.h"
#include <vector>
#include <assert.h>

void Teste::runFilterBrandTest()
{
	Depozit depozit{ "produse.txt" };
	auto lista = depozit.filterByBrand("Samsung");
	assert(lista.size() == 5);
}