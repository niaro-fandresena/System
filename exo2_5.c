#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

int main ()
{
	time_t debut = time(NULL);
	srand(time(NULL));

	for (int i = 1; i < 2; i++) {
		if (fork() == 0) {
			int slip = (rand() % 10) + 1;
			printf ("Fils %d: dodo de %ds\n", i, slip);
			sleep(slip);
			exit(0);
		}
	}

	wait(NULL);
	wait(NULL);

	time_t fin = time(NULL);
	printf ("Durée total : %ld secondes\n", fin - debut);
	return 0;
}
