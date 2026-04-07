#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <setjmp.h>

//point de sauvegarde
sigjmp_buf point_retour;
void handler_segfault(int sig) {
    printf("\n[ERREUR] Erreur de segmentation détectée (indice hors limites) !\n");
    siglongjmp(point_retour, 1);
}

int main() {
    int n, i;
    int *tab;

    printf("Entrez la taille du tableau (n) : ");
    scanf("%d", &n);
    tab = malloc(n * sizeof(int));
    for (int j = 0; j < n; j++) {
        printf("tab[%d] = ", j);
        scanf("%d", &tab[j]);
    }
    signal(SIGSEGV, handler_segfault);
    sigsetjmp(point_retour, 1); 

    while (1) {
        printf("\nEntrez l'indice i à afficher : ");
        if (scanf("%d", &i) != 1) break;

        printf("Valeur de tab[%d] = %d\n", i, tab[i]);
        
        printf("Succès ! Voulez-vous un autre indice ? (Ctrl+C pour quitter)\n");
    }

    free(tab);
    return 0;
}
