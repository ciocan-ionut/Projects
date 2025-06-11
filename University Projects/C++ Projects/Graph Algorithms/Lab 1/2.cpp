#include <iostream>
#include <fstream>

using namespace std;

ifstream f("date.in");

void DFS(int nod, int mat_ad[10][10], int n, bool vizitat[10])
{
	vizitat[nod] = true;
	for (int i = 1; i <= n; i++)
		if (mat_ad[nod][i] == 1 && !vizitat[i])
			DFS(i, mat_ad, n, vizitat);
}

int main()
{
	int n, i, j, mat_ad[10][10];
	f >> n; //citim nr. de noduri

	//citim matricea de adiacenta
	for (i = 1; i <= n; i++)
		for (j = 1; j <= n; j++)
		{
			int x;
			f >> x;
			mat_ad[i][j] = x;
		}

	//1. determinam nodurile izolate
	bool ok = false;
	int noduri[10], l = 0;
	for (i = 1; i <= n; i++)
	{
		bool izolat = true;
		for (j = 1; j <= n; j++)
			if (mat_ad[i][j] == 1)
				izolat = false;
		if (izolat)
		{
			noduri[l] = i;
			l++;
			ok = true;
		}
	}
	if (ok)
	{
		cout << "1. Nodurile izolate sunt: ";
		for (i = 0; i < l; i++)
		{
			cout << noduri[i];
			if (i != l - 1)
				cout << ", ";
		}
	}
	else
		cout << "1. Graful nu are noduri izolate";

	//2. determinam daca graful este regulat
	ok = true;
	for (i = 2; i <= n; i++)
	{
		int gradp = 0, grad = 0;
		for (j = 1; j <= n; j++)
		{
			gradp += mat_ad[1][j];
			grad += mat_ad[i][j];
		}
		if (gradp != grad)
			ok = false;
	}
	cout << endl;
	if (ok)
		cout << "2. Graful este regulat" << endl;
	else
		cout << "2. Graful nu este regulat" << endl;

	//3. determinam matricea distantelor
	int copie[10][10];
	//copiem matricea de adiacenta
	for (int i = 1; i <= n; i++)
		for (j = 1; j <= n; j++)
			copie[i][j] = mat_ad[i][j];
	for (int k = 1; k <= n; ++k)
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= n; ++j)
				if (i != j && mat_ad[i][j] == 0 && mat_ad[i][k] == 1 && mat_ad[k][j] == 1)
					mat_ad[i][j] = 1;
	cout << "3." << endl;
	for (i = 1; i <= n; i++)
	{
		for (j = 1; j <= n; j++)
			cout << mat_ad[i][j] << ' ';
		cout << endl;
	}

	//4. determinam daca graful este conex
	bool conex = true;
	bool vizitat[10] = { false };
	DFS(1, copie, n, vizitat);
	for (i = 1; i <= n; i++)
		if (!vizitat[i])
			conex = false;
	if (conex)
		cout << "4. Graful este conex";
	else
		cout << "4. Graful nu este conex";
}