#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/shm.h>




#include "common.h"
#include "stdio.h"
#include "stdbool.h"

typedef struct {
    int chairs; // liczba wolnych foteli w salonie fryzjerskim
    int waiting; // liczba klientów w poczekalni
    int queue[MAX_QUEUE_SIZE]; // kolejka klientów w poczekalni, trzyma fryzure
} shared_data;



void init_shared_data(shared_data *data, int num_chairs);
bool queue_empty(shared_data *data);
bool queue_full(shared_data *data);
int queue_pop(shared_data *data);
void queue_push(shared_data *data,int client_haircut);
int get_shared_data(const char *key);
shared_data* attach_shared_data(const char *key);
void delete_shared_data(shared_data* data);
void destroy_shared_data(const char *filename);
