#include <stdio.h>
#include <stdlib.h>

int main () {
	printf ("Affichage des 5 premières lignes de /etc/passwd :\n");
	system("head -n 5 /etc/passwd");
	printf ("\nCommande terminée.\n");
	return 0;
}
