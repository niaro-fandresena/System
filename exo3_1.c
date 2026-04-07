#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main ()
{
	printf ("ls -l \n");
	execlp ("ls", "ls", "-l", NULL);
	return 1;
}
