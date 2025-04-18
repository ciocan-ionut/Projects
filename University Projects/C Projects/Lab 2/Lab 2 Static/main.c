#include <stdio.h>
#include "tests.h"
#include "service.h"
#include "ui.h"

int main()
{
	runTests();

	Repository repository;
	createRepository(&repository);

	Service service;
	createService(&repository, &service);

	runApp(&service);
	return 0;
}