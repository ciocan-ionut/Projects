#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int* v;

struct temp
{
	int pozitie;
	int pas;
};

void* add(void* a)
{
	int* index = (int*) a;
	int* pas = (int*) (a + sizeof(int));
	v[*index] = v[*index] + v[*index + *pas];
	return NULL;
}

int main()
{
	int n;
	printf("Introduceti nr. de numere: ");
	scanf("%d", &n);
	v = malloc(n * sizeof(int));
	for(int i = 0; i < n; i++)
		v[i] = i + 1;

	pthread_t* threads = malloc(n/2 * sizeof(pthread_t));
	struct temp* pozitii = malloc(n * sizeof(int));

	int maxIterations = n/2, pow2 = 2, pas = 1;
	while(maxIterations != 0)
	{
		for(int i = 0; i < maxIterations; i++)
		{
			pozitii[i].pozitie = i * pow2;
			pozitii[i].pas = pas;
			pthread_create(&threads[i], NULL, add, &pozitii[i]);
		}
		for(int i = 0; i < maxIterations; i++)
			pthread_join(threads[i], NULL);
		maxIterations = maxIterations/2;
		pow2 = pow2 * 2;
		pas = pas * 2;
	}
	printf("%d\n", v[0]);

	free(v);
	free(threads);
	free(pozitii);
	return 0;
}
