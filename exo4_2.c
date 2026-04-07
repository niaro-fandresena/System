#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main () {
	int p[2];
	pipe(p);

	if (fork() == 0) {
		dup2(p[1], STDOUT_FILENO);
		close(p[0]);
		close(p[1]);

		execlp("ls", "ls", "-l", NULL);
		perror("erreur execlp");
		exit(1);
	}
	else {
		dup2(p[0], STDIN_FILENO);
		close(p[0]);
		close(p[1]);

		execlp ("wc", "wc", "-l", NULL);
		perror ("erreur execlp");
		exit(1);
	}
	return 0;
}
