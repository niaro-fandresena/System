#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

typedef struct {
    int *tableau;
    int nb_elements;
    int x;
} TypeTableau;

void *initialiserTableau(void *arg) {
    TypeTableau *tt = (TypeTableau *)arg;
    
    printf("[Thread 1] Génération de %d éléments...\n", tt->nb_elements);
    for (int i = 0; i < tt->nb_elements; i++) {
        tt->tableau[i] = rand() % 100;
    }
    
    pthread_exit(NULL);

void *rechercherElement(void *arg) {
    TypeTableau *tt = (TypeTableau *)arg;
    int *trouve = malloc(sizeof(int));
    *trouve = 0;

    printf("[Thread 2] Recherche de l'entier %d dans le tableau...\n", tt->x);
    for (int i = 0; i < tt->nb_elements; i++) {
        if (tt->tableau[i] == tt->x) {
            *trouve = 1;
            break;
        }
    }
    
    pthread_exit((void *)trouve);
}

int main() {
    pthread_t t1, t2;
    TypeTableau *mon_tableau = malloc(sizeof(TypeTableau));
    int n;
    void *ret_recherche;

    srand(time(NULL));

    // 1. Paramétrage
    printf("Entrez le nombre d'éléments du tableau : ");
    scanf("%d", &n);
    
    mon_tableau->nb_elements = n;
    mon_tableau->tableau = malloc(n * sizeof(int));
    pthread_create(&t1, NULL, initialiserTableau, mon_tableau);
    printf("entrez l'entier x à rechercher : ");
    scanf("%d", &mon_tableau->x);
    pthread_join(t1, NULL);
    printf("Main : Tableau généré avec succès.\n");
    pthread_create(&t2, NULL, rechercherElement, mon_tableau);
    pthread_join(t2, &ret_recherche);
    int resultat = *((int *)ret_recherche);

    if (resultat == 1) {
        printf("Résultat final : L'élément %d est PRÉSENT dans le tableau.\n", mon_tableau->x);
    } else {
        printf("Résultat final : L'élément %d est ABSENT du tableau.\n", mon_tableau->x);
    }

    free(ret_recherche);
    free(mon_tableau->tableau);
    free(mon_tableau);
    
    return 0;


