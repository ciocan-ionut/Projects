#include <stdio.h>

/*
* Functie care afiseaza meniul de optiuni al programului
* :return: -
*/
void afisare()
{
	printf("Alegeti optiunea:\n");
	printf("1. Afisati triunghiul\n");
	printf("2. Iesire\n");
	printf("3. Afisati numerele (cerinta zilei)\n");
}

/*
* Functie care salveaza in vectorul l toate combinarile de n luate cate k, cu k de la 1 la n
* :param n: numar natural > 0
* :param l: vector de numere naturale
* :return: -
*/
void combinari(int n, int *l)
{
	int p = 1;
	l[0] = p;
	for (int k = 1; k <= n; k++)
	{
		p = p * (n - k + 1) / k;
		l[k] = p;
	}
}

/*
* Functie care verifica daca numerele a si b sunt prime intre ele
* :param a: numar natural > 0
* :param b: numar natural > 0
* :return: 1 daca numerele a si b sunt prime intre ele, 0 in caz contrar
*/
int relativ_prime(int a, int b)
{
	while (a != b)
	{
		if (a > b)
			a = a - b;
		else
			b = b - a;
	}
	if (a == 1)
		return 1;
	else
		return 0;
}

/*
* Functia principala a programului
* :return: 0 la finalizarea programului
*/
int main()
{
	printf("~~~Triunghiul lui Pascal~~~\n");
	int optiune, n, ok = 1;
	while (ok)
	{
		afisare();
		scanf_s("%d", &optiune);
		if (optiune == 2)
			ok = 0;
		else if (optiune == 1)
		{
			printf("Introduceti numarul de linii: ");
			scanf_s("%d", &n);
			if (n <= 0)
				printf("Numarul trebuie sa fie strict pozitiv!\n");
			else
			{
				for (int i = 0; i < n; i++)
				{
					int linie[31] = { 0 };
					combinari(i, linie);
					int j = 0;
					while (linie[j] != 0)
					{
						printf("%d ", linie[j]);
						j++;
					}
					printf("\n");
				}
			}
		}
		else if (optiune == 3)
		{
			printf("Introduceti numarul: ");
			scanf_s("%d", &n);
			if (n <= 0)
				printf("Numarul trebuie sa fie strict pozitiv!\n");
			else
			{
				printf("Numerele naturale care respecta conditiile sunt: ");
				for (int i = 1; i < n; i++)
					if (relativ_prime(n, i))
						printf("%d ", i);
			}
			printf("\n");
		}
		else
			printf("Optiune invalida!\n");
	}
	return 0;
}