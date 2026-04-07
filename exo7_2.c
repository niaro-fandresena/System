#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void handler_affiche(int sig) {
    FILE *f = fopen("/tmp/entier.txt", "r");
    if (f) {
        int valeur;
        fscanf(f, "%d", &valeur);
        printf("\n[Affiche] Signal reçu ! Valeur lue : %d\n", valeur);
        fclose(f);
        exit(0);
    }
}

int main() {
    printf("Mon PID est : %d\n", getpid());
    signal(SIGUSR1, handler_affiche);

    while(1) {
        pause();
    }
    return 0;
}
