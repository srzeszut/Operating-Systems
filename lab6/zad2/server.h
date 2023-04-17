#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "mqueue.h"
#include "signal.h"

#define MAX_MSG_SIZE 256
#define MAX_NO_CLIENTS 5
#define SERVER_QUEUE_NAME "/server_queue"


typedef enum {
    INIT=1,
    LIST=2,
    ALL=3,
    ONE=4,
    STOP=5

}jobs;

typedef struct{
    long msg_type;         /* typ komunikatu   */
    char message[MAX_MSG_SIZE];
    int client_id;
    int client_to;
}msgBuff;

typedef struct{
    int client_id;
    int client_queue;
} client;
