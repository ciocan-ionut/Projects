#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>
#include <unistd.h>

// Write a C program that creates a child process. Both the parent and the child processes will run
// until they receive a SIGUSR1 signal. Implement signal handling such that if the parent receives
// the SIGUSR1 signal first, it sends it to the child process as well. If the child process receives
// a SIGUSR1 signal without the parent receiving the same signal, it will terminate and then the parent
// should correctly call wait for the child process.

int childPID;

void parentSignal(int sgn)
{
	if(sgn == SIGUSR1)
		kill(childPID, SIGUSR1);
}

void childSignal(int sgn)
{
	if(sgn == SIGUSR1)
		kill(getpid(), SIGKILL);
}

int main()
{
	signal(SIGUSR1, parentSignal);
	childPID = fork();
	if(childPID == 0)
	{
		signal(SIGUSR1, childSignal);
		while(1);
		exit(0);
	}
	wait(0);
	return 0;
}
