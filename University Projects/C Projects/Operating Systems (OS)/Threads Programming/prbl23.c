#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <sys/wait.h>

// Write a C program that receives any number of strings as command line arguments.
// The program creates two child processes, which inherit the parent's command line arguments
// (ie. no need to send the arguments via pipe/fifo to the children for this problem).
// Each child process creates a thread for each of the command line arguments.
// Each thread created by the first child will extract the vowels from its argument and will append them
// to a string shared among the threads. Each thread created by the second child process will extract the digits
// from its argument and will add them to a sum shared among the threads.
// Both child processes wait for their respective threads to finish and send the result to the parent via pipe.
// The parent displays the results.

pthread_mutex_t mV;
pthread_mutex_t mC;

typedef struct
{
	char* text;
	int* poz;
	char* string;
} Vocale;

typedef struct
{
	char* text;
	int* suma;
} Cifre;

void* extractV(void* arg)
{
	Vocale* data = (Vocale*) arg;
	for(unsigned int i = 0; i < strlen(data->text); i++)
	{
		char c = data->text[i];
		if (c == 'a' || c == 'A' || c == 'e' || c == 'E' || c == 'i' || c == 'I' || c == 'o'
			|| c == 'O' || c == 'u' || c == 'U')
		{
			pthread_mutex_lock(&mV);
			data->string[*(data->poz)] = c;
			(*(data->poz))++;
			pthread_mutex_unlock(&mV);
		}
	}
	return NULL;
}

void* calculateSum(void* arg)
{
	Cifre* data = (Cifre*) arg;
	for(unsigned int i = 0; i < strlen(data->text); i++)
	{
		char c = data->text[i];
		if (c >= '0' && c <= '9')
		{
			int cif = c - '0';
			pthread_mutex_lock(&mC);
			(*(data->suma)) += cif;
			pthread_mutex_unlock(&mC);
		}
	}
	return NULL;
}

int main(int argc, char* argv[])
{
	int p[2];
	pipe(p);
	if (fork() == 0)
	{
		close(p[0]);
		pthread_t* threads = malloc((argc - 1) * sizeof(pthread_t));
		pthread_mutex_init(&mV, NULL);

		char* string = malloc(1024);
		int poz = 0;
		Vocale* voc = malloc((argc - 1) * sizeof(Vocale));
		for (int i = 0; i < argc - 1; i++)
		{
			voc[i].text = argv[i + 1];
			voc[i].poz = &poz;
			voc[i].string = string;
		}

		for (int i = 1; i < argc; i++)
			pthread_create(&threads[i - 1], NULL, extractV, &voc[i - 1]);
		for(int i = 1; i < argc; i++)
			pthread_join(threads[i - 1], NULL);
		string[poz] = '\0';

		pthread_mutex_destroy(&mV);
		free(threads);
		free(voc);
		write(p[1], &poz, sizeof(int));
		write(p[1], string, poz);
		free(string);
		close(p[1]);
		exit(0);
	}
	wait(0);
	int nrVocale;
	read(p[0], &nrVocale, sizeof(int));
	char* vocale = malloc(nrVocale + 1);
	read(p[0], vocale, nrVocale);
	vocale[nrVocale] = '\0';

	if (fork() == 0)
	{
		close(p[0]);
		pthread_t* threads = malloc((argc - 1) * sizeof(pthread_t));
		pthread_mutex_init(&mC, NULL);

		int suma = 0;
		Cifre* cif = malloc((argc - 1) * sizeof(Cifre));
		for(int i = 0; i < argc - 1; i++)
		{
			cif[i].text = argv[i + 1];
			cif[i].suma = &suma;
		}

		for(int i = 1; i < argc; i++)
			pthread_create(&threads[i - 1], NULL, calculateSum, &cif[i - 1]);
		for(int i = 1; i < argc; i++)
			pthread_join(threads[i - 1], NULL);

		pthread_mutex_destroy(&mC);
		free(threads);
		free(cif);
		write(p[1], &suma, sizeof(int));
		close(p[1]);
		exit(0);
	}
	wait(0);
	int sumaCifre;
	read(p[0], &sumaCifre, sizeof(int));
	close(p[0]);
	close(p[1]);

	printf("Suma cifrelor este %d, iar vocalele sunt %s\n", sumaCifre, vocale);
	free(vocale);
	return 0;
}
