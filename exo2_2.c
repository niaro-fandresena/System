#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main () {
	if (fork() == 0) {
		printf ("je suis le fils 1\n");
	}
	else {
		if (fork() == 0) {
			printf ("je suis le fils 2\n");
		}
		else {
			printf ("je suis le père\n");
			wait(NULL);
			wait(NULL);
		}
	}
	return 0;
}
