#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Write a C program that receives integers as command line argument.
// The program will keep a frequency vector for all digits.
// The program will create a thread for each argument that counts the number of occurences of each digit
// and adds the result to the frequency vector. Use efficient synchronization.

int v[10] = { 0 };
pthread_mutex_t m[10];

void* calcFrecv(void* nr)
{
	char* numar = (char*) nr;
	int n = atoi(numar);
	while(n != 0)
	{
		int cif = n%10;
		pthread_mutex_lock(&m[cif]);
		v[cif]++;
		pthread_mutex_unlock(&m[cif]);
		n = n/10;
	}
	return NULL;
}

int main(int argc, char* argv[])
{
	for(int i = 0; i < 10; i++)
		pthread_mutex_init(&m[i], NULL);

	pthread_t* threads = malloc(argc * sizeof(pthread_t));
	for(int i = 1; i < argc; i++)
		pthread_create(&threads[i - 1], NULL, calcFrecv, argv[i]);
	for(int i = 0; i < argc - 1; i++)
		pthread_join(threads[i], NULL);
	free(threads);

	for(int i = 0; i < 10; i++)
		printf("Cifra: %d, Frecventa: %d\n", i, v[i]);
	return 0;
}
