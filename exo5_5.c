#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

struct context_t {
    int *compt;
    int limite;
    pthread_mutex_t *mutex;
};

void *thread_incrementateur(void *arg) {
    struct context_t *ctx = (struct context_t *)arg;
    
    while (1) {
        pthread_mutex_lock(ctx->mutex);
        if (*(ctx->compt) >= ctx->limite) {
            pthread_mutex_unlock(ctx->mutex);
            break;
        }
        (*(ctx->compt))++;
        printf("[Thread 1] Incrémentation : %d\n", *(ctx->compt));
        pthread_mutex_unlock(ctx->mutex);

        sleep(rand() % 5 + 1);
    }
    pthread_exit(NULL);
}

void *thread_afficheur(void *arg) {
    struct context_t *ctx = (struct context_t *)arg;
    
    while (1) {
        sleep(2);
        
        pthread_mutex_lock(ctx->mutex);
        printf("[Thread 2] Valeur actuelle du compteur : %d\n", *(ctx->compt));
        
        if (*(ctx->compt) >= ctx->limite) {
            pthread_mutex_unlock(ctx->mutex);
            break;
        }
        pthread_mutex_unlock(ctx->mutex);
    }
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <valeur_limite>\n", argv[0]);
        return 1;
    }

    srand(time(NULL));
    int limite = atoi(argv[1]);
    int compteur_global = 0;
    pthread_t t1, t2;
    pthread_mutex_t mon_mutex;
    pthread_mutex_init(&mon_mutex, NULL);
    struct context_t *ctx = malloc(sizeof(struct context_t));
    ctx->compt = &compteur_global;
    ctx->limite = limite;
    ctx->mutex = &mon_mutex;
    pthread_create(&t1, NULL, thread_incrementateur, ctx);
    pthread_create(&t2, NULL, thread_afficheur, ctx);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("Fin du programme. Compteur final : %d\n", compteur_global);

    pthread_mutex_destroy(&mon_mutex);
    free(ctx);

    return 0;
}


