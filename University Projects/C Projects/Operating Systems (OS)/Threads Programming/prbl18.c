#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Create a C program that converts all lowercase letters from the command line arguments to uppercase letters
// and prints the result. Use a thread for each given argument.

void* toUpper(void* arg)
{
	char* text = (char*) arg;
	int i = 0;
	while (text[i] != '\0')
	{
		if (text[i] >= 'a' && text[i] <= 'z')
			text[i] = text[i] - 'a' + 'A';
		i++;
	}
	return NULL;
}

int main(int argc, char* argv[])
{
	pthread_t* threads = malloc((argc - 1) * sizeof(pthread_t));
	for (int i = 1; i < argc; i++)
		pthread_create(&threads[i - 1], NULL, toUpper, argv[i]);
	for(int i = 0; i < argc - 1; i++)
		pthread_join(threads[i], NULL);
	for(int i = 1; i < argc; i++)
		printf("%s ", argv[i]);
	printf("\n");
	free(threads);
	return 0;
}
