#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main () {
	int i;
	for (i = 0; i < 5; i++)
	{
		if (fork() == 0) {
			printf ("Fils %d créé\n", i + 1);
			return 0;
		}
	}
	for (i = 0; i < 5; i++)
	{
		for (i = 0; i < 5; i++)
			wait(NULL);
	}
	return 0;
}
