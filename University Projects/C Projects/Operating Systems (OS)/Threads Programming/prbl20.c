#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

// Write a C program that takes as command line arguments 2 numbers: N and M.
// The program will simulate a thread race that have to pass through M checkpoints.
// Through each checkpoint the threads must pass one at a time (no 2 threads can be inside the same checkpoint).
// Each thread that enters a checkpoint will wait between 100 and 200 milliseconds
// (usleep(100000) makes a thread or process wait for 100 milliseconds) and will print a message indicating
// the thread number and the checkpoint number, then it will exit the checkpoint.
// Ensure that no thread will try to pass through a checkpoint until all threads have been created.

int m;
pthread_barrier_t b;
pthread_mutex_t* mtxs;

void* race(void* threadNumber)
{
	int* thread = (int*) threadNumber;
	pthread_barrier_wait(&b);
	int index = 0;
	while(index < m)
	{
		pthread_mutex_lock(&mtxs[index]);
		int time = rand() % 100001 + 100000;
		usleep(time);
		printf("Thread: %d, Checkpoint: %d\n", *thread, index);
		index++;
		pthread_mutex_unlock(&mtxs[index - 1]);
	}
	return NULL;
}

int main(int argc, char* argv[])
{
	srand(time(NULL));
	(void) argc;
	int n = atoi(argv[1]);
	m = atoi(argv[2]);

	pthread_barrier_init(&b, NULL, n);

	mtxs = malloc(m * sizeof(pthread_mutex_t));
	for(int i = 0; i < m; i++)
		pthread_mutex_init(&mtxs[i], NULL);

	int* pozitii = malloc(n * sizeof(int));
	for(int i = 0; i < n; i++)
		pozitii[i] = i + 1;

	pthread_t* threads = malloc(n * sizeof(pthread_t));
	for(int i = 0; i < n; i++)
		pthread_create(&threads[i], NULL, race, &pozitii[i]);
	for(int i = 0; i < n; i++)
		pthread_join(threads[i], NULL);

	for(int i = 0; i < m; i++)
		pthread_mutex_destroy(&mtxs[i]);
	pthread_barrier_destroy(&b);
	free(mtxs);
	free(pozitii);
	free(threads);
	return 0;
}
