#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main () {
	pid_t pid = fork();

	if (pid < 0) {
		printf ("Erreur\n");
		return 1;
	}
	else if (pid == 0) {
		printf ("je suis le fils\n");
	}
	else {
		printf ("je suis le père\n");
	}
	return 0;
}
