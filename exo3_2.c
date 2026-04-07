#include <stdio.h>
#include <unistd.h>
int main ()
{
	char *args[] = {"ls", "-a", "-h", NULL};

	printf ("Remplacement du processus pr ls -ah\n");

	execv ("/bin/ls", args);
	return 1;
}
