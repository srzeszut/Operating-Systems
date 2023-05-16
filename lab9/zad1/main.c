#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

pthread_mutex_t santa_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t reindeer_cv = PTHREAD_COND_INITIALIZER;
pthread_cond_t elf_cv = PTHREAD_COND_INITIALIZER;
pthread_cond_t santa_cv = PTHREAD_COND_INITIALIZER;

int waiting_reindeer = 0;
int waiting_elves = 0;

const int NUM_REINDEER = 9;
const int NUM_ELVES = 10;
int waiting_elves_ids[3];

void* santa_claus() {
    while (1) {
        pthread_mutex_lock(&santa_mutex);

        while (waiting_reindeer < NUM_REINDEER && waiting_elves < 3) {
            printf("Mikołaj: śpię.\n");
            pthread_cond_wait(&santa_cv, &santa_mutex);
        }

        if (waiting_reindeer == NUM_REINDEER) {
            printf("Mikołaj: wybudzam się.\n");
            printf("Mikołaj: dostarczam zabawki.\n");
            sleep(rand() % 3 + 2);
            waiting_reindeer = 0;
            pthread_cond_broadcast(&reindeer_cv);
        } else if (waiting_elves == 3) {
            printf("Mikołaj: wybudzam się.\n");
            printf("Mikołaj: rozwiązuję problemy elfów. %d %d %d\n",waiting_elves_ids[0],waiting_elves_ids[1],waiting_elves_ids[2]);
            sleep(rand() % 2 + 1);
            waiting_elves = 0;
            pthread_cond_broadcast(&elf_cv);
        }

        printf("Mikołaj: zasypiam.\n");
        pthread_mutex_unlock(&santa_mutex);
    }

    return NULL;
}

void* reindeer(void* arg) {
    int id = *((int*) arg);

    while (1) {
        sleep(rand() % 6 + 5);
        pthread_mutex_lock(&santa_mutex);
        printf("Renifer %d: czekam %d reniferów na Mikołaja.\n", id, waiting_reindeer);
        waiting_reindeer++;

        if (waiting_reindeer == NUM_REINDEER) {
            printf("Renifer %d: wybudzam Mikołaja.\n", id);
            pthread_cond_signal(&santa_cv);
        } else {
            pthread_cond_wait(&reindeer_cv, &santa_mutex);
        }

        pthread_mutex_unlock(&santa_mutex);
        printf("Renifer %d: dostarczam zabawki.\n", id);
        sleep(rand() % 3 + 2);
    }

    return NULL;
}

void* elf(void* arg) {
    int id = *((int*) arg);

    while (1) {
        int work_duration = rand() % 4 + 2;
        sleep(work_duration);

        pthread_mutex_lock(&santa_mutex);
        printf("Elf %d: czekam %d elfów na Mikołaja.\n", id, waiting_elves);

        if (waiting_elves < 3) {
            waiting_elves_ids[waiting_elves] = id;
            waiting_elves++;

            if (waiting_elves == 3) {
                printf("Elf %d: wybudzam Mikołaja.\n", id);
                pthread_cond_signal(&santa_cv);
            } else {
                pthread_cond_wait(&elf_cv, &santa_mutex);
            }

            printf("Elf %d: Mikołaj rozwiązuje problem.\n", id);
            sleep(rand() % 2 + 1); // Spotkanie z Mikołajem (1-2s)
        } else {
            printf("Elf %d: samodzielnie rozwiązuję swój problem.\n", id);
        }

        pthread_mutex_unlock(&santa_mutex);
    }

    return NULL;
}

int main() {
    srand(time(NULL));
    pthread_t santa_thread, reindeer_threads[NUM_REINDEER], elf_threads[NUM_ELVES];
    int reindeer_ids[NUM_REINDEER], elf_ids[NUM_ELVES];

    pthread_create(&santa_thread, NULL, santa_claus, NULL);

    for (int i = 0; i < NUM_REINDEER; i++) {
        reindeer_ids[i] = i + 1;
        pthread_create(&reindeer_threads[i], NULL, reindeer, (void*) &reindeer_ids[i]);
    }

    for (int i = 0; i < NUM_ELVES; i++) {
        elf_ids[i] = i + 1;
        pthread_create(&elf_threads[i], NULL, elf, (void*) &elf_ids[i]);
    }

    pthread_join(santa_thread, NULL);

    return 0;
}