#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

// Write a C program that creates n child processes. Each child process will print its PID and its parent PID.
// The parent process will print its PID and the PID of each of the child processes.

int main()
{
	int n, nr;
	printf("Introduceti numarul de copii: ");
	scanf("%d", &n);
	nr = n + 1;
	while(n > 0)
	{
		int childPID = fork();
		if(childPID==0)
		{
			printf("PPID: %d\nPID: %d\n\n", getppid(), getpid());
			exit(0);
		}
		else
			printf("%d. Parent PID: %d - Child: %d\n", nr-n, getpid(), childPID);
		wait(0);
		n--;
	}
}
