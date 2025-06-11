#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

// Write a C program that creates a linear hierarchy of n processes
// (a parent process creates a child process, which in turn creates a child process, and so on).

int main()
{
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
	{
		if(fork() == 0)
		{
			printf("%d. Parent PID: %d - Child PID: %d\n", i+1, getppid(), getpid());
			continue;
		}
		wait(0);
		exit(0);
	}
}
