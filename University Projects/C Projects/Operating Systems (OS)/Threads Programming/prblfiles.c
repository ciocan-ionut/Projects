#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <fcntl.h>

int bytes;
pthread_mutex_t m;

void* countBytes(void* a)
{
	bytes = 0;
	int n = 0, lg;
	char* file = (char*) a;
	int fd = open(file, O_RDONLY);
	char* buffer = malloc(4096);
	while((lg = read(fd, buffer, 4096)))
	{
		for(int i = 0; i < lg; i++)
			n += buffer[i];
	}
	bytes += n;
	free(buffer);
	return NULL;
}

int main(int argc, char** argv)
{
	pthread_mutex_init(&m, NULL);
	for(int i = 1; i < argc; i++)
		if(access(argv[i], F_OK) == 0)
		{
			if(access(argv[i], X_OK) == 0)
			{
				if(fork() == 0)
					execlp(argv[i], argv[i], NULL);
			}
			else
			{
				pthread_t thread;
				pthread_create(&thread, NULL, countBytes, argv[i]);
				pthread_join(thread, NULL);
				printf("Bytes: %d\n", bytes);
			}
		}
	pthread_mutex_destroy(&m);
	return 0;
}
