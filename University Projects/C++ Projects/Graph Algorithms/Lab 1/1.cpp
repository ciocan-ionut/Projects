#include <iostream>
#include <fstream>

using namespace std;

ifstream fin("in.txt");

struct lista
{
	int nod;
	int vecini[10];
	int l;
};

int main1()
{
	int mat_ad[10][10] = { 0 }, mat_inc[10][10] = { 0 }, n, m = 0, i, j;
	//citim nr. de noduri
	fin >> n;

	//cream matricea de adiacenta
	while(fin >> i >> j)
	{
		//calculam nr. de muchii
		m++;
		mat_ad[i][j] = 1;
		mat_ad[j][i] = 1;
		mat_inc[i][m] = 1;
		mat_inc[j][m] = 1;
	}

	//afisam pe ecran matricea de adiacenta
	cout << "Matricea de adiacenta: " << endl;
	for (i = 1; i <= n; i++)
	{
		for (j = 1; j <= n; j++)
			cout << mat_ad[i][j] << ' ';
		cout << endl;
	}

	//cream lista de adiacenta
	lista lista_ad[10];
	for (i = 1; i <= n; i++)
	{
		lista_ad[i].nod = i;
		int ind = 1;
		for (j = 1; j <= n; j++)
			if (mat_ad[i][j] == 1)
			{
				lista_ad[i].vecini[ind] = j;
				ind++;
			}
		lista_ad[i].l = ind-1;
	}

	//afisam pe ecran lista de adiacenta
	cout << endl << "Lista de adiacenta: " << endl;
	for (i = 1; i <= n; i++)
	{
		cout << lista_ad[i].nod << ": ";
		for (j = 1; j <= lista_ad[i].l; j++)
			cout << lista_ad[i].vecini[j] << ' ';
		cout << endl;
	}

	//afisam pe ecran matricea de incidenta
	cout << endl << "Matricea de incidenta: " << endl;
	for (i = 1; i <= n; i++)
	{
		for (j = 1; j <= m; j++)
			cout << mat_inc[i][j] << ' ';
		cout << endl;
	}

	//cream lista de adiacenta dupa matricea de incidenta
	lista lista_ad_inc[10];
	for (i = 1; i <= n; i++)
	{
		int ind = 1;
		lista_ad_inc[i].nod = i;
		for (int muchie = 1; muchie <= m; muchie++)
			if (mat_inc[i][muchie] == 1)
				for (j = 1; j <= n; j++)
					if (i != j && mat_inc[j][muchie] == 1)
					{
						lista_ad_inc[i].vecini[ind] = j;
						ind++;
					}
		lista_ad_inc[i].l = ind - 1;
	}

	//afisam pe ecran lista de adiacenta dupa matricea de incidenta
	cout << endl << "Lista de adiacenta (incidenta): " << endl;
	for (i = 1; i <= n; i++)
	{
		cout << lista_ad_inc[i].nod << ": ";
		for (j = 1; j <= lista_ad_inc[i].l; j++)
			cout << lista_ad_inc[i].vecini[j] << ' ';
		cout << endl;
	}

	//cream matricea de adiacenta dupa lista de adiacenta
	int mat_ad_lista[10][10] = { 0 };
	for (i = 1; i <= n; i++)
	{
		for (j = 1; j <= lista_ad_inc[i].l; j++)
		{
			mat_ad_lista[i][lista_ad_inc[i].vecini[j]] = 1;
			mat_ad_lista[lista_ad_inc[i].vecini[j]][i] = 1;
		}
	}

	//afisam pe ecran matricea de adiacenta dupa lista de adiacenta
	cout << endl << "Matricea de adiacenta (lista): " << endl;
	for (i = 1; i <= n; i++)
	{
		for (j = 1; j <= n; j++)
			cout << mat_ad_lista[i][j] << ' ';
		cout << endl;
	}

	//afisam pe ecran lista initiala
	cout << endl << "Lista de muchii: " << endl;
	for (i = 1; i <= n; i++)
	{
		for (j = 1; j < i; j++)
			if (mat_ad_lista[i][j] == 1)
				cout << i << ' ' << j << endl;
	}

	return 0;
}