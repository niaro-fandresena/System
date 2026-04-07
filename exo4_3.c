#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

int main ()
{
	int fd;
	char *nom_fifo = "/tmp/ma_fifo";
	char *message = "Données envoyées via FIFO";

	if (mkfifo(nom_fifo, 0666 == -1)) {
	
		printf("mkfifo\n");	
	}

	printf ("É: Ouverture de la FIFO...\n");
	fd = open(nom_fifo, O_WRONLY);
	if (fd == -1) {
		perror ("erreur\n");
		exit (EXIT_FAILURE);
	}

	write (fd, message, strlen(message) + 1);
	printf ("É: Message envoyé.\n");
	return 0;
}
