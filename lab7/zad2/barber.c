#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "semph.h"
#include "common.h"
#include "queue.h"

semaphore mutex;
semaphore barber;
semaphore chairs;
semaphore waiting_room;

void open_semaphores();

int main(){
//    printf("Barber %d awake.\n", getpid());
    open_semaphores();
    shared_data * data = attach_shared_data(HOME_PATH);
    if(data == NULL) {
        fprintf(stderr, "Can't open queue.\n");
        exit(EXIT_FAILURE);
    }
    while (1) {
//        printf("Barber %d is sleeping.\n", getpid());
        fflush(stdout);
        acquire(barber);
        acquire(mutex);
        if (data->waiting >0) {
            int haircut = queue_pop(data); // pobranie fryzury klienta z poczekalni
            release(mutex);
            printf("Barber %d is processing client with haircut no. %d\n",getpid(), haircut);
            fflush(stdout);
            // symulacja strzyżenia
            usleep(haircut*100000);
//            sleep(1);

            printf("Barber %d is done with haircut no. %d\n",getpid() ,haircut);
            fflush(stdout);

            release(chairs);
            release(waiting_room);

        } else{
            release(mutex);
        }

        if (queue_empty(data))
        {
            sleep(2);
            if (queue_empty(data))
                break;
        }

    }
    delete_shared_data(data);
    return 0;
}

void open_semaphores(){
    mutex=open_semaphore(MUTEX_SEM);
    barber=open_semaphore(BARBER_SEM);
    chairs=open_semaphore(CHAIR_SEM);
    waiting_room=open_semaphore(LOBBY_SEM);
}