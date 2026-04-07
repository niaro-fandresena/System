#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>

#define N 5

void handler_mort_fils(int sig) {
    printf("\n[Fils %d] : Mort \n", getpid());
    exit(0);
}

void handler_mort_pere(int sig) {
    printf("\n[Père] : Mort, fin du programme global.\n");
    exit(0);
}

int main() {
    pid_t t_fils[N];
    int i, choix, num_fils;

    signal(SIGTERM, handler_mort_pere);

    for (i = 0; i < N; i++) {
        t_fils[i] = fork();
        if (t_fils[i] == 0) {
            
            signal(SIGTERM, handler_mort_fils); 
            while (1) {
            }
        }
    }
    while (1) {
        printf("\n--- MENU PERE ---\n");
        printf("1. Endormir un fils\n2. Réveiller un fils\n3. Terminer un fils\nChoix : ");
        scanf("%d", &choix);
        printf("Numéro du fils (0 à %d) : ", N - 1);
        scanf("%d", &num_fils);

        if (num_fils < 0 || num_fils >= N) {
            printf("Fils inexistant.\n");
            continue;
        }

        switch (choix) {
            case 1:
                kill(t_fils[num_fils], SIGSTOP);
                printf("Fils %d endormi.\n", num_fils);
                break;
            case 2:
                kill(t_fils[num_fils], SIGCONT);
                printf("Fils %d réveillé.\n", num_fils);
                break;
            case 3:
                kill(t_fils[num_fils], SIGTERM);
                break;
            default:
                printf("Choix invalide.\n");
        }
    }

    return 0;
}
