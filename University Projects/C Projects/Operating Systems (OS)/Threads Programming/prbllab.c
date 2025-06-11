#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <stdio.h>
#include <stdbool.h>

int v[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

pthread_mutex_t* m;

void* swap(void* a)
{
	while(true)
	{
		int firstIndex = rand() % 10;
		int secondIndex = rand() % 10;

		if (firstIndex == secondIndex)
			continue;

		if (firstIndex > secondIndex)
		{
			int aux = firstIndex;
			firstIndex = secondIndex;
			secondIndex = aux;
		}
		pthread_mutex_lock(&m[firstIndex]);
		pthread_mutex_lock(&m[secondIndex]);
		int aux = v[firstIndex];
		v[firstIndex] = v[secondIndex];
		v[secondIndex] = aux;
		pthread_mutex_unlock(&m[firstIndex]);
		pthread_mutex_unlock(&m[secondIndex]);
	}
	(void) a;
	return NULL;
}

int main()
{
	srand(time(NULL));
	pthread_t threads[30];
	m = malloc(10 * sizeof(pthread_mutex_t));
	for(int i = 0; i < 10; i++)
		pthread_mutex_init(&m[i], NULL);
	for(int i = 0; i < 30; i++)
		pthread_create(&threads[i], NULL, swap, NULL);
	for(int i = 0; i < 30; i++)
		pthread_join(threads[i], NULL);
	for(int i = 0; i < 10; i++)
		pthread_mutex_destroy(&m[i]);
	free(m);
	return 0;
}
