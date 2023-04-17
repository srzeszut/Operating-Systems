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
#define MAX_NAME 6
#define SERVER_QUEUE_NAME "/SERVER"


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
    char client_name[MAX_NAME];
    mqd_t client_queue;
} client;

const int MSG_SIZE = sizeof(msgBuff);
mqd_t create_queue(const char* name) {
    struct mq_attr attr;
    attr.mq_flags = O_NONBLOCK;
    attr.mq_maxmsg = MAX_NO_CLIENTS;
    attr.mq_msgsize = MSG_SIZE;
    return mq_open(name, O_RDWR | O_CREAT, 0666, &attr);
}
