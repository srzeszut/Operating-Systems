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
    int shm_id = shm_open(key, O_CREAT | O_RDWR, 0666);
    if (shm_id == -1) {
        perror("shm_open");
        return -1;
    }
    if (ftruncate(shm_id, sizeof(shared_data)) == -1) {
        perror("ftruncate");
        return -1;
    }
    return shm_id;
}
shared_data* attach_shared_data(const char* key) {
    int shm_id= get_shared_data(key);
    if (shm_id == -1) {
        perror("shm_open");
        return NULL;
    }
    shared_data* data = mmap(NULL, sizeof(shared_data), PROT_READ | PROT_WRITE, MAP_SHARED, shm_id, 0);
    if (data == MAP_FAILED) {
        perror("mmap");
        return NULL;
    }

    return data;
}
void delete_shared_data(shared_data* data) {
    if (munmap(data, sizeof(shared_data)) == -1) {
        perror("munmap");
        return;
    }
}
void destroy_shared_data(const char *key) {
    if(shm_unlink(key) == -1){
        perror("shmctl");
        return;
    }
}