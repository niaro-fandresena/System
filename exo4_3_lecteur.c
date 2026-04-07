#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main () {
	int fd;
	char *nom_fifo = "/tmp/ma_fifo";
	char buffer[1024];

	printf ("Lecteur: Ouverture de la FIFO...\n");
	fd = open(nom_fifo, O_RDONLY);
	if (fd == -1) {
		perror ("erreur");
		exit(EXIT_FAILURE);
	}

	int n = read(fd, buffer, sizeof (buffer));
	if (n > 0) {
		printf ("Lecteur: Recu: %s\n", buffer);
	}
	close(fd);
	unlik(nom_fifo);
	return 0;
}
