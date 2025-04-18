#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main()
{
	int n;
	double v, s = 0;
	printf("Introduceti numarul de elemente: ");
	scanf("%d", &n);
	if (n <= 0)
	{
		printf("Numarul trb sa fie pozitiv\n");
		return 1;
	}
	for (int i = 0; i < n; i++)
	{
		printf("Introduceti numarul %d: ", i + 1);
		scanf("%lf", &v);
		s += v;
	}
	printf("Suma totala este %.2lf\n", s);
	return 0;
}