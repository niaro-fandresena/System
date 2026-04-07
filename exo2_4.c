#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main () {
	int i;
	for (i = 1; i <= 5; i++) {
		pid_t pid = fork();
		if (pid == 0) {
			printf ("je suis le fils %d\n", i);
			return 0;
		}
	}

	for (i = 0; i < 5; i++)
		wait (NULL);
	return 0;
		
	return 0;

}
