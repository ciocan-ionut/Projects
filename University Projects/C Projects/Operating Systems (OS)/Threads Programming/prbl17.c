#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

// Write a C program that reads a number N and creates 2 threads.
// One of the threads will generate an even number and will append it to an array that is passed as a parameter
// to the thread. The other thread will do the same, but using odd numbers.
// Implement a synchronization between the two threads so that they alternate in appending numbers to the array,
// until they reach the maximum length N.

int n, poz = 0;
pthread_cond_t c1, c2;
pthread_mutex_t m;

void* addPar(void* sir)
{
	int* vector = (int*) sir;
	pthread_mutex_lock(&m);
	while(poz < n)
	{
		int nr = rand() % 100;
		while(nr % 2 != 0)
			nr = rand() % 100;
		vector[poz++] = nr;
		pthread_cond_signal(&c2);
		pthread_cond_wait(&c1, &m);
	}
	pthread_mutex_unlock(&m);
	pthread_cond_signal(&c2);
	return NULL;
}

void* addImpar(void* sir)
{
	int* vector = (int*) sir;
	pthread_mutex_lock(&m);
	while(poz < n)
	{
		int nr = rand() % 100;
		while(nr % 2 != 1)
			nr = rand() % 100;
		vector[poz++] = nr;
		pthread_cond_signal(&c1);
		pthread_cond_wait(&c2, &m);
	}
	pthread_mutex_unlock(&m);
	pthread_cond_signal(&c1);
	return NULL;
}

int main(int argc, char* argv[])
{
	(void) argc;
	srand(time(NULL));

	n = atoi(argv[1]);
	int* vector = malloc(n * sizeof(int));

	pthread_cond_init(&c1, NULL);
	pthread_cond_init(&c2, NULL);
	pthread_mutex_init(&m, NULL);

	pthread_t threads[2];
	pthread_create(&threads[0], NULL, addPar, vector);
	pthread_create(&threads[1], NULL, addImpar, vector);
	for(int i = 0; i < 2; i++)
		pthread_join(threads[i], NULL);

	for(int i = 0; i < n; i++)
		printf("%d ", vector[i]);
	printf("\n");
	free(vector);
	return 0;
}
