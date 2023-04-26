#include "semph.h"

semaphore create_semaphore(const char* key,int init_val){
    key_t sem_key = ftok(HOME_PATH, key[0]);//działa dla SV i POSIX
    if(sem_key==-1){
        perror("ftok");
        return EXIT_FAILURE;
    }
    semaphore sem_id = semget(sem_key,1,IPC_CREAT|0666);
    if(sem_id==-1){
        perror("semget");
        return EXIT_FAILURE;
    }
    if(semctl(sem_id,0,SETVAL,init_val)==-1){
        perror("semctl");
        return EXIT_FAILURE;
    }
    return sem_id;
}
semaphore open_semaphore(const char* key){
    key_t sem_key = ftok(HOME_PATH, key[0]);
    if(sem_key==-1){
        perror("ftok");
        return EXIT_FAILURE;
    }
   return semget(sem_key,1,0);

}
void unlink_semaphore(const char* key){
    semaphore sem_id = open_semaphore(key);
    if( sem_id == -1) {
        fprintf(stderr, "open_semaphore.\n");
        return;
    }
    release(sem_id);
    if (semctl(sem_id, 0, IPC_RMID) == -1) {
        perror("semctl");
        return;
    }
}
void acquire(semaphore sem_num) {
//    struct sembuf op;
//    op.sem_num = sem_num;
//    op.sem_op = -1;
//    op.sem_flg = 0;
    struct sembuf op = { 0, -1, 0 };
    semop(sem_num, &op, 1);
}

void release(semaphore sem_num) {
    struct sembuf op;
    op.sem_num = 0;
    op.sem_op = 1;
    op.sem_flg = 0;
    semop(sem_num, &op, 1);
}
