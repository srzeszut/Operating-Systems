#include "stdio.h"
#include "semph.h"
#include "common.h"
#include "queue.h"

#define BARBER "./barber"
#define CLIENT "./client"


semaphore mutex;
semaphore barber;
semaphore chairs;
semaphore waiting_room;
int num_barbers;
int num_clients;
int num_chairs;

void create_semaphores();
void unlink_semaphores();

int main(int argc,char* argv[]){
    if (argc != 4) {
        printf("Usage: %s num_barbers num_clients num_chairs\n", argv[0]);
        return EXIT_FAILURE;
    }

     num_barbers = atoi(argv[1]);
     num_clients = atoi(argv[2]);
     num_chairs = atoi(argv[3]);



    // utworzenie segmentu pamięci współdzielonej
    shared_data * data = attach_shared_data(HOME_PATH);
    if(data == NULL) {
        exit(EXIT_FAILURE);
    }
    init_shared_data(data,num_chairs);
    unlink_semaphores();
    create_semaphores();

    // utworzenie procesu fryzjera
    for(int i=0;i<num_barbers;++i)
        if (fork() == 0)
            execl(BARBER, BARBER, NULL);
    printf("Created barbers.\n");
    fflush(stdout);

    // utworzenie procesów klientów
    for(int i=0;i<num_clients;++i)
        if (fork() == 0)
            execl(CLIENT, CLIENT, NULL);
    printf("Created clients.\n");
    fflush(stdout);

    // oczekiwanie na zakończenie procesów potomnych
    while (wait(NULL) > 0);

    // zwolnienie semaforów i pamięci współdzielonej
    sem_close(mutex);
    sem_close(barber);
    sem_close(chairs);
    sem_close(waiting_room);

    destroy_shared_data(HOME_PATH);
    printf("finished.\n");
    fflush(stdout);




    return 0;
}

void create_semaphores(){
    mutex=create_semaphore(MUTEX_SEM,1);
    barber=create_semaphore(BARBER_SEM,0);
    chairs=create_semaphore(CHAIR_SEM,0);
    waiting_room= create_semaphore(LOBBY_SEM,num_chairs);
}
void unlink_semaphores(){
    unlink_semaphore(MUTEX_SEM);
    unlink_semaphore(LOBBY_SEM);
    unlink_semaphore(BARBER_SEM);
    unlink_semaphore(CHAIR_SEM);
}