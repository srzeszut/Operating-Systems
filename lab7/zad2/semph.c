#include "semph.h"

semaphore create_semaphore(const char* key, int init_val) {
    semaphore sem_id = sem_open(key, O_CREAT | O_EXCL, 0666, init_val);
    if(sem_id == SEM_FAILED) {
        perror("sem_open");
        return NULL;
    }
    return sem_id;
}
semaphore open_semaphore(const char* key){
    semaphore sem_id = sem_open(key, 0);
    if(sem_id == SEM_FAILED) {
        perror("sem_open");
        return NULL;
    }
    return sem_id;

}
void unlink_semaphore(const char* key){
    sem_unlink(key);
}
void acquire(semaphore sem_num) {
    sem_wait(sem_num);
}

void release(semaphore sem_num) {
    sem_post(sem_num);
}
