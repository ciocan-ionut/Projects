#include <sys/time.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>

// Write a C program that runs a bash command (potentially with arguments) received as a command line argument
// and times its execution.

int main(int argc, char** argv)
{
	(void)argc;
	struct timeval t0, t1;
	gettimeofday(&t0, NULL);
	if(fork() == 0)
		execvp(argv[1], argv+1);
	wait(0);
	gettimeofday(&t1, NULL);
	int time = t1.tv_sec - t0.tv_sec;
	printf("Procesul a durat %d secunde\n", time);
	return 0;
}
