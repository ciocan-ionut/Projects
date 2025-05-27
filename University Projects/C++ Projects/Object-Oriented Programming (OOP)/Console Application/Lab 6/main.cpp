#define _CRTDBG_MAP_MALLOC
#include <crtdbg.h>
#include <iostream>
#include "Teste.h"
#include "UI.h"

using namespace std;

void start()
{
	Teste::runTests();

	RepositoryRandom repositoryRandom;
	Repository repository;
	CosActivitati cos;

	Service service{ repository, cos };
	//Service service{ repositoryRandom, cos };
	
	UI::runApp(service);
}

int main()
{	
	start();
	//if (_CrtDumpMemoryLeaks())
	//	cout << "Am gasit!";
}