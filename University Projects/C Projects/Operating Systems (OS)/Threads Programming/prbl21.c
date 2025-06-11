#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <time.h>

// Write a C program that creates 2^N threads that race to the finish (N is a command line argument).
// The threads must pass through N checkpoint. The checkpoint with number X will allow half as many threads
// to pass simultaneously than checkpoint number X - 1 (N >= X >=1).
// Checkpoint 0 (the first one) will allow 2^(N-1) to pass simultaneously through it.

int n;
sem_t* sems;
pthread_barrier_t b;

void* race(void* nrThread)
{
	int* thread = (int*) nrThread;
	pthread_barrier_wait(&b);
	int index = 0;
	while(index < n)
	{
		sem_wait(&sems[index]);
		int time = rand() % 100001 + 100000;
		usleep(time);
		printf("Thread: %d, Checkpoint: %d\n", *thread, index);
		index++;
		sem_post(&sems[index - 1]);
	}
	return NULL;
}

int main(int argc, char* argv[])
{
	srand(time(NULL));
	(void) argc;
	n = atoi(argv[1]);

	int nrThreads = 1, Threads = 1;
	for(int i = 0; i < n; i++)
	{
		nrThreads *= 2;
		if (i < n - 1)
			Threads *= 2;
	}
	printf("%d %d", nrThreads, Threads);
	pthread_t* threads = malloc(nrThreads * sizeof(pthread_t));

	int* pozitii = malloc(nrThreads * sizeof(int));
	for(int i = 0; i < nrThreads; i++)
		pozitii[i] = i + 1;

	pthread_barrier_init(&b, NULL, nrThreads);
	sems = malloc(n * sizeof(sem_t));
	for(int i = 0; i < n; i++)
	{
		sem_init(&sems[i], 0, Threads);
		Threads = Threads / 2;
	}

	for(int i = 0; i < nrThreads; i++)
		pthread_create(&threads[i], NULL, race, &pozitii[i]);
	for(int i = 0; i < nrThreads; i++)
		pthread_join(threads[i], NULL);

	pthread_barrier_destroy(&b);
	for(int i = 0; i < n; i++)
		sem_destroy(&sems[i]);
	free(sems);
	free(threads);
	free(pozitii);
	return 0;
}
