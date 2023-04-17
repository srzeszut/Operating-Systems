#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include "signal.h"

#define MAX_MSG_SIZE 256
#define MAX_NO_CLIENTS 5
#define SERVER_KEY 1
#define HOME_PATH getenv("HOME")

typedef struct{
    long msg_type;         /* typ komunikatu   */
    char message[MAX_MSG_SIZE];
    int client_id;
    int client_to;
}msgBuff;

typedef enum {
    INIT=1,
    LIST=2,
    ALL=3,
    ONE=4,
    STOP=5

}jobs;

typedef struct{
    int client_id;
    int client_queue;
    key_t client_key;
} client;

const int MSG_SIZE = sizeof(msgBuff);