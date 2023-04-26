#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <string.h>


#include "common.h"
#include "queue.h"
#include "semph.h"

semaphore mutex;
semaphore barber;
semaphore chairs;
semaphore waiting_room;

void open_semaphores();

int main(){
//    printf("Client %d awake.\n", getpid());
    srand(time(NULL) + getpid());
    open_semaphores();
    shared_data * data = attach_shared_data(HOME_PATH);
    if(data == NULL) {
        fprintf(stderr, "Can't open queue.\n");
        exit(EXIT_FAILURE);
    }


//    acquire(mutex);
    if (data->waiting >= MAX_QUEUE_SIZE) {
        printf("The waiting room is full. Client %d is leaving.\n", getpid());
        fflush(stdout);
//        release(mutex);
    }


        acquire(waiting_room);
        acquire(mutex);
        int haircut=rand() % 19 + 2;
        printf("Client %d with haircut %d arrives, waiting: %d\n",getpid(),haircut, data->waiting);
        fflush(stdout);
        queue_push(data,haircut);
        release(mutex);

        release(barber);
        acquire(chairs);

        printf("Client %d has finished getting a haircut.\n", getpid());
        fflush(stdout);

    delete_shared_data(data);
    return 0;
}
void open_semaphores(){
    mutex=open_semaphore(MUTEX_SEM);
    barber=open_semaphore(BARBER_SEM);
    chairs=open_semaphore(CHAIR_SEM);
    waiting_room=open_semaphore(LOBBY_SEM);
}