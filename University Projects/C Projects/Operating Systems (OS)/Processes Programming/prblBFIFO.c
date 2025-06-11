#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>

// Write two C programs that communicate via fifo. The two processes will alternate sending random integers
// between 1 and 10 (inclusively) to one another until one of them sends the number 10.
// Print messages as the numbers are sent.

int main()
{
	srand(time(NULL));
	int fdr = open("A2B", O_RDONLY);
	int fdw = open("B2A", O_WRONLY);
	int n;
	read(fdr, &n, sizeof(int));
	printf("Am primit de la A: %d\n", n);
	do
	{
		n = rand() % 10 + 1;
		write(fdw, &n, sizeof(int));
		printf("Am trimis la A: %d\n", n);
		if (n != 10)
		{
			read(fdr, &n, sizeof(int));
			printf("Am primit de la A: %d\n", n);
		}
	} while (n != 10);
	close(fdr);
	close(fdw);
}
