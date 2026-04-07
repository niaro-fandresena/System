#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main ()
{
	pid_t pid = fork();
	if (pid == 0) {
		execlp ("ps", "ps", "-f", NULL);
		exit(1);
	}
	else {
		wait(NULL);
		printf ("Processus fils terminé\n");
	}
	return 0;
}
