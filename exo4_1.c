#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main ()
{
	int p[2];
	pid_t pid;
	char buffer[1024];
	char *message = "Message du pere au fils via le tube";

	if (pipe(p) == -1) {
		printf ("erreur pipe\n");
		exit(EXIT_FAILURE);
	}

	pid = fork();
	if (pid == -1) {
		printf ("erreur fork\n");
		exit(EXIT_FAILURE);
	}

	if (pid == 0) {
		close(p[1]);
		int n = read(p[0], buffer, sizeof(buffer));
		if (n > 0) {
			buffer[n] = '\0';
			printf ("Fils (PID%d) a lu: %s\n", getpid(), buffer);
		}
		close(p[0]);
		exit(EXIT_SUCCESS);
	}
	else {
		close(p[0]);
		write(p[1], message, strlen(message));
		close(p[1]);
		wait(NULL);
	}
	return 0;
}
