#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/wait.h>
#include "common.h"
typedef int semaphore;

semaphore create_semaphore(const char* key,int init_val);

semaphore open_semaphore(const char* key);
void unlink_semaphore(const char* key);

void acquire(semaphore sem_num);

void release(semaphore sem_num);
