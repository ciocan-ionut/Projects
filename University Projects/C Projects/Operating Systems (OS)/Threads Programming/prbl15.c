#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>

// Write a program that receives strings of characters as command line arguments.
// For each string the program creates a thread which calculates the number of digits,
// the number of leters and the number of special characters (anything other than a letter or digit).
// The main program waits for the threads to terminate and prints the total results
// (total number of digits, letters and special characters across all the received command line arguments)
// and terminates. Use efficient synchronization. Do not use global variables

typedef struct
{
	char* text;
	int litere;
	int cifre;
	int speciale;
} Sir;

void* determinaCaractere(void* arg)
{
	Sir* comanda = (Sir*) arg;
	for(unsigned int i = 0; i < strlen(comanda->text); i++)
	{
		if ((comanda->text[i] >= 'a' && comanda->text[i] <= 'z') ||
			(comanda->text[i] >= 'A' && comanda->text[i] <= 'Z'))
			comanda->litere++;
		else if (comanda->text[i] >= '0' && comanda->text[i] <= '9')
			comanda->cifre++;
		else
			comanda->speciale++;
	}
	return NULL;
}

int main(int argc, char* argv[])
{
	Sir* siruri = malloc(argc * sizeof(Sir));

	pthread_t* threads = malloc(argc * sizeof(pthread_t));

	for(int i = 0; i < argc - 1; i++)
	{
		siruri[i].litere = 0;
		siruri[i].cifre = 0;
		siruri[i].speciale = 0;
	}

	for(int i = 1; i < argc; i++)
	{
		siruri[i - 1].text = malloc(sizeof(argv[i]) + 1);
		strcpy(siruri[i - 1].text, argv[i]);
		pthread_create(&threads[i - 1], NULL, determinaCaractere, &siruri[i - 1]);
	}
	for(int i = 0; i < argc - 1; i++)
		pthread_join(threads[i], NULL);

	int litere = 0, cifre = 0, speciale = 0;
	for(int i = 0; i < argc - 1; i++)
	{
		free(siruri[i].text);
		litere += siruri[i].litere;
		cifre += siruri[i].cifre;
		speciale += siruri[i].speciale;
	}
	free(siruri);
	printf("Litere: %d, Cifre: %d, Caractere speciale: %d\n", litere, cifre, speciale);
	return 0;
}
