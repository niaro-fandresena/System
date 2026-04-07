#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int main() {
    pid_t fils = fork();

    if (fils == 0) {
        while (1) {
            printf("Fils en cours...\n"); 
            sleep(1); 
        }
    } else {
        char choix;
        while (1) {
            printf("\nMenu : (s)top, (r)estart, (q)uit : ");
            scanf(" %c", &choix);

            switch (choix) {
                case 's':
                    kill(fils, SIGSTOP);
                    printf("Fils endormi.\n");
                    break;
                case 'r':
                    kill(fils, SIGCONT);
                    printf("Fils redémarré.\n");
                    break;
                case 'q':
                    kill(fils, SIGKILL);
                    printf("Fils tué. Fin du programme.\n");
                    exit(0);
                default:
                    printf("Commande inconnue.\n");
            }
        }
    }
    return 0;
}
