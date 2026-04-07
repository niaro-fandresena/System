#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <unistd.h>

unsigned char BAL;
struct Ctx { sem_t *v, *p; };

void* emetteur(void* arg) {
    struct Ctx *c = (struct Ctx*)arg;
    for (char o = 'A'; o <= 'Z'; o++) {
        sem_wait(c->v); 
        BAL = o;
        sem_post(c->p); 
        sleep(rand() % 3 + 1);
    }
    return NULL;
}

void* recepteur(void* arg) {
    struct Ctx *c = (struct Ctx*)arg;
    for (int i = 0; i < 26; i++) {
        sem_wait(c->p); 
        char l = BAL;
        sem_post(c->v); 
        sleep(rand() % 3 + 1);
    }
    return NULL;
}

int main() {
    pthread_t t1, t2;
    sem_t sv, sp;
    sem_init(&sv, 0, 1); 
    sem_init(&sp, 0, 0);

    struct Ctx *ctx = malloc(sizeof(struct Ctx));
    ctx->v = &sv; ctx->p = &sp;

    pthread_create(&t1, NULL, emetteur, ctx);
    pthread_create(&t2, NULL, recepteur, ctx);

    pthread_join(t1, NULL); pthread_join(t2, NULL);

    sem_destroy(&sv); sem_destroy(&sp);
    free(ctx);
    return 0;
}
