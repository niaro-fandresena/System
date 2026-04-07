#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
struct Thread_config {
    int taille;
};
void *genererTableau(void *arg) {
    struct Thread_config *config = (struct Thread_config *)arg;
    
    int *tableau = malloc(config->taille * sizeof(int));
    
    printf("Thread : Initialisation du tableau...\n");
    for (int i = 0; i < config->taille; i++) {
        tableau[i] = rand() % 100;
    }
    pthread_exit((void *)tableau);
}

int main() {
    pthread_t thread;
    struct Thread_config config;
    int *tableau_recu;
    void *retour_thread;

    srand(time(NULL));
    config.taille = 10;

    if (pthread_create(&thread, NULL, genererTableau, &config) != 0) {
        perror("Erreur pthread_create");
        return 1;
    }

    pthread_join(thread, &retour_thread);
    tableau_recu = (int *)retour_thread;

    printf("Main : Tableau reçu du thread :\n");
    for (int i = 0; i < config.taille; i++) {
        printf("[%d] : %d\n", i, tableau_recu[i]);
    }

    free(tableau_recu);

    return 0;
}
