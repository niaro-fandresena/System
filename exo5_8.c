#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

struct RDV_2 {
    sem_t *sem_t1; // Signalé par T1
    sem_t *sem_t2; // Signalé par T2
};

void* thread_T1(void* arg) {
    struct RDV_2 *ctx = (struct RDV_2*)arg;
    for(int i = 1; i <= 10; i++) {
        sleep(2); // Traitement fixe
        printf("[T1] Itération %d : Arrivé au rendez-vous.\n", i);
        
        sem_post(ctx->sem_t1);
        sem_wait(ctx->sem_t2);
        
        printf("[T1] Itération %d : Rendez-vous réussi, je continue.\n", i);
    }
    pthread_exit(NULL);
}

void* thread_T2(void* arg) {
    struct RDV_2 *ctx = (struct RDV_2*)arg;
    for(int i = 1; i <= 10; i++) {
        sleep(rand() % 6 + 4); 
        printf("[T2] Itération %d : Arrivé au rendez-vous.\n", i);
        
        sem_post(ctx->sem_t2);
        sem_wait(ctx->sem_t1); 
        
        printf("[T2] Itération %d : Rendez-vous réussi, je continue.\n", i);
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t t1, t2;
    sem_t s1, s2;
    sem_init(&s1, 0, 0);
    sem_init(&s2, 0, 0);

    struct RDV_2 *ctx = malloc(sizeof(struct RDV_2));
    ctx->sem_t1 = &s1; ctx->sem_t2 = &s2;

    pthread_create(&t1, NULL, thread_T1, ctx);
    pthread_create(&t2, NULL, thread_T2, ctx);

    pthread_join(t1, NULL); pthread_join(t2, NULL);

    sem_destroy(&s1); sem_destroy(&s2);
    free(ctx);
    return 0;
}
