#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>

// Create a C program that generates N random integers (N given at the command line).
// It then creates a child, sends the numbers via pipe. The child calculates the average and sends the result back.

int main(int argc, char** argv)
{
	(void)argc;
	int n = atoi(argv[1]), p[2], nr;
	double medie;

	srand(time(NULL));
	pipe(p);
	for(int i=0; i<n; i++)
	{
		nr = rand() % 50;
		printf("%d\n", nr);
		write(p[1], &nr, sizeof(int));
	}

	if(fork() == 0)
	{
		int s = 0;
		for (int i=0; i<n; i++)
		{
			read(p[0], &nr, sizeof(int));
			s+=nr;
		}
		close(p[0]);
		medie = s/n;
		write(p[1], &medie, sizeof(double));
		close(p[1]);
		exit(0);
	}
	wait(0);
	close(p[1]);
	read(p[0], &medie, sizeof(double));
	close(p[0]);
	printf("Media numerelor este %f\n", medie);
	return 0;
}
