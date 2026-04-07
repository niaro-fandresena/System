#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

#define N 100

double tableau[N];

struct Context {
    pthread_mutex_t *mutex;
};

void *thread_lissage(void *arg) {
    struct Context *ctx = (struct Context *)arg;
    
    while (1) {
        pthread_mutex_lock(ctx->mutex);
        
        printf("[Thread 1] Calcul des moyennes en cours...\n");
        for (int i = 1; i <= 98; i++) {
            tableau[i] = (tableau[i-1] + tableau[i] + tableau[i+1]) / 3.0;
        }
        
        pthread_mutex_unlock(ctx->mutex);
        sleep(rand() % 3 + 1);
    }
    return NULL;
}

void *thread_afficheur(void *arg) {
    struct Context *ctx = (struct Context *)arg;

    while (1) {
        sleep(4);

        pthread_mutex_lock(ctx->mutex);
        printf("\n--- Affichage du Tbleau  ---\n");
        for (int i = 0; i < N; i++) {
         
            if (i % 10 == 0 || i == 1 || i == 98) {
                printf("T[%d] = %.2f | ", i, tableau[i]);
            }
        }
        printf("\n--------------------------------------------------\n");
        pthread_mutex_unlock(ctx->mutex);
    }
    return NULL;
}

int main() {
    pthread_t t1, t2;
    pthread_mutex_t verrou;
    pthread_mutex_init(&verrou, NULL);

    srand(time(NULL));

    for (int i = 0; i < N; i++) {
        if (i == 0 || i == 99) {
            tableau[i] = 0.0;
        } else {
            tableau[i] = (double)(rand() % 101);
        }
    }

    struct Context *ctx = malloc(sizeof(struct Context));
    ctx->mutex = &verrou;

    printf("Lancement des threads...\n");
    pthread_create(&t1, NULL, thread_lissage, ctx);
    pthread_create(&t2, NULL, thread_afficheur, ctx);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_mutex_destroy(&verrou);
    free(ctx);
    return 0;
}
