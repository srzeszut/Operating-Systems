#include "queue.h"


void init_shared_data(shared_data *data, int num_chairs) {
    data->chairs = num_chairs;
    data->waiting = 0;
    for (int i = 0; i < MAX_QUEUE_SIZE; i++) {
        data->queue[i] = -1; // oznaczamy miejsca w kolejce jako wolne
    }
}
bool queue_empty(shared_data *data){
    return (data->waiting==0);
}
bool queue_full(shared_data *data){
    return (data->waiting==MAX_QUEUE_SIZE);
}
int queue_pop(shared_data *data){
    if(queue_empty(data)){
        fprintf(stderr,"Can't pop from empty queue.");
        return -1;
    }
    int to_return=data->queue[0];
    data->waiting--;
    for (int i = 0; i < data->waiting; i++) {
        data->queue[i] = data->queue[i + 1];
    }
    return to_return;
}

void queue_push(shared_data *data,int client_haircut){
    if(queue_full(data)){
        fprintf(stderr,"push: Queue full.");
        return;
    }
    data->queue[data->waiting]=client_haircut;
    data->waiting++;

}
int get_shared_data(const char *key) {
    key_t shm_key = ftok(key, 0);
    if (shm_key == -1) {
        return -1;
    }
    return shmget(shm_key, sizeof(shared_data), IPC_CREAT | 0666);
}
shared_data* attach_shared_data(const char* key) {
    int shm_id= get_shared_data(key);
    shared_data* data = shmat(shm_id, NULL, 0);
    if (data == (void*) -1) {
        perror("shmat");
        return NULL;
    }

    return data;
}
void delete_shared_data(shared_data* data) {
    if (shmdt(data) == -1) {
        perror("shmdt");
        return;
    }
}
void destroy_shared_data(const char *key) {
    int shared_memory_id = get_shared_data(key);
    if(shared_memory_id == -1) {
        fprintf(stderr,"Shared memory id not found.");
        return;
    }
    if(shmctl(shared_memory_id, IPC_RMID, NULL) == -1){
        perror("shmctl");
        return;
    }
}