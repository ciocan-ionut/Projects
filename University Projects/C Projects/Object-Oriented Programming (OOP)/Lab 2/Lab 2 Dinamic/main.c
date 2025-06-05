#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include <stdio.h>
#include "tests.h"
#include "service.h"
#include "ui.h"

int main()
{
	runTests();
	//_CrtDumpMemoryLeaks();

	Repository repository;
	createRepository(&repository);

	Service service;
	createService(&repository, &service);

	runApp(&service);
	_CrtDumpMemoryLeaks();
	return 0;
}