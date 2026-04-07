#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>

typedef struct {
    int *tab;
    int taille;
} Arg_Gen;

typedef struct {
    int *T1;
    int n1;
    int *T2;
    int n2;
} Arg_Inclusion;

void *generer_tableau(void *arg) {
    Arg_Gen *data = (Arg_Gen *)arg;
    for (int i = 0; i < data->taille; i++) {
        data->tab[i] = rand() % 100;
    }
    pthread_exit(NULL);
}

void *tester_inclusion(void *arg) {
    Arg_Inclusion *data = (Arg_Inclusion *)arg;
    int *resultat = malloc(sizeof(int));
    *resultat = 1; //

    for (int i = 0; i < data->n1; i++) {
        int trouve = 0;
        for (int j = 0; j < data->n2; j++) {
            if (data->T1[i] == data->T2[j]) {
                trouve = 1;
                break;
            }
        }
        if (!trouve) {
            *resultat = 0;
            break;
        }
    }
    pthread_exit((void *)resultat);
}

void *thread_annulation(void *arg) {
    char c;
    while (1) {
        c = getchar();
        if (c == 'A' || c == 'a') {
            printf("\nTouche 'A' pressée. Arrêt du programme.\n");
            exit(0); 
        }
    }
    return NULL;
}

int main() {
    pthread_t t_gen1, t_gen2, t_inc, t_stop;
    int n1 = 5, n2 = 10;
    srand(time(NULL));

   //(Question c)
    pthread_create(&t_stop, NULL, thread_annulation, NULL);

    Arg_Gen *a1 = malloc(sizeof(Arg_Gen));
    Arg_Gen *a2 = malloc(sizeof(Arg_Gen));
    
    a1->taille = n1; a1->tab = malloc(n1 * sizeof(int));
    a2->taille = n2; a2->tab = malloc(n2 * sizeof(int));

    pthread_create(&t_gen1, NULL, generer_tableau, a1);
    pthread_create(&t_gen2, NULL, generer_tableau, a2);

    pthread_join(t_gen1, NULL);
    pthread_join(t_gen2, NULL);
    printf("Main : Tableaux T1 et T2 générés.\n");

    //(Question b)
    Arg_Inclusion *ai = malloc(sizeof(Arg_Inclusion));
    ai->T1 = a1->tab; ai->n1 = n1;
    ai->T2 = a2->tab; ai->n2 = n2;

    void *ret;
    pthread_create(&t_inc, NULL, tester_inclusion, ai);
    pthread_join(t_inc, &ret);

    int est_inclus = *((int *)ret);
    printf("Résultat : T1 est-il inclus dans T2 ? %s\n", est_inclus ? "OUI" : "NON");

    free(ret); free(a1->tab); free(a2->tab);
    free(a1); free(a2); free(ai);

    return 0;
}
