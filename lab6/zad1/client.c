#include "server.h"
#include <time.h>
#include <sys/select.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int client_id;
key_t server_key;
key_t client_key;
int server_queue;
int client_queue;

void init();
void list();
void to_all(char* message){

}
void to_one(char* message,int client_id){

}
void stop();


void send_message(char* text,jobs type);
void send_message_to_client(char* text,jobs type,int client_to);
void server_message();


int main(){
    srand(time(NULL));
    server_key = ftok(HOME_PATH, SERVER_KEY);
    server_queue = msgget(server_key,  0666);
    if (server_queue == -1)
    {
        perror("Cannot create server queue.");
        exit(EXIT_FAILURE);
    }

    client_key = ftok(HOME_PATH, rand() % (100)+1);
    client_queue = msgget(client_key,  IPC_CREAT |0666);
    if (client_queue == -1)
    {
        perror("Cannot create server queue.");
        exit(EXIT_FAILURE);
    }

    signal(SIGINT,stop);
    init();

    char *token;
    char *words[3];
    char buff[MAX_MSG_SIZE];
    int i;
    int ret, maxfd;
    fd_set readfds;
    struct timeval tv;
    tv.tv_sec = 1;
    tv.tv_usec = 0;

    while(1){
        token=NULL;
        server_message();

        FD_ZERO(&readfds);
        FD_SET(STDIN_FILENO, &readfds);
        maxfd = STDIN_FILENO;

        ret = select(maxfd + 1, &readfds, NULL, NULL, &tv);
        if (ret < 0) {
            perror("select");
            exit(EXIT_FAILURE);
        }
        if (FD_ISSET(STDIN_FILENO, &readfds)) {
            fgets(buff,sizeof(buff),stdin);
            token = strtok(buff, " ");
        }

        i=0;
        if(token==NULL){
            continue;
        }
        for(int j=0;j<3;j++){
            words[j]="";
        }
        while (token != NULL && i < 3) {
            words[i++] = token;
            token = strtok(NULL, " ");
        }
//        printf("commsnd: %s",words[0]);
//        printf("%d",strcmp(words[0], "LIST"));
        if (strcmp(words[0], "LIST\n") == 0) {
            send_message("",LIST);
            list();

        }
        else if(strcmp(words[0], "2ALL") == 0){
            send_message(words[1],ALL);

        }
        else if(strcmp(words[0], "2ONE") == 0){
            if(strlen(words[1])==0){
                fprintf(stderr,"You must enter ID");
            }
            else
            {
                send_message_to_client(words[2],ONE,atoi(words[1]));
            }
        }
        else if(strcmp(words[0], "STOP\n") == 0){
            stop();

        }
        else{
            printf("Unknown command.\n");
        }

    }



    return 0;
}

void send_message(char* text,jobs type){
    msgBuff message;
    strcpy(message.message,text);
    message.client_id=client_id;
    message.msg_type=type;
    msgsnd(server_queue, &message, MSG_SIZE, 0);
}
void send_message_to_client(char* text,jobs type,int client_to){
    msgBuff message;
    strcpy(message.message,text);
    message.client_id=client_id;
    message.client_to=client_to;
    message.msg_type=type;
    msgsnd(server_queue, &message, MSG_SIZE, 0);
}
void init(){
    msgBuff init_msg;
    init_msg.msg_type = 1;
    sprintf(init_msg.message, "%d", client_key);

    if (msgsnd(server_queue, &init_msg, MSG_SIZE, 0) == -1)
    {
        perror("Cannot send innit message.");
        exit(0);
    }

    msgBuff confirmation;
    int wait=0;
    while(msgrcv(client_queue,&confirmation,MSG_SIZE,6,IPC_NOWAIT)<0){
        if(wait>3){
            fprintf(stderr,"Recieved no confirmation from a server\n");
            exit(EXIT_FAILURE);
        }
        printf("waiting for confirmation\n");
        sleep(1);
        wait++;

    }
    client_id= atoi(confirmation.message);
    printf("client id: %d\n",client_id);
}
void list(){
    msgBuff message;
    msgrcv(client_queue,&message,MSG_SIZE,LIST,0);
    printf("%s\n",message.message);
}
void server_message(){
    msgBuff message;
    while(msgrcv(client_queue,&message,MSG_SIZE,0,IPC_NOWAIT)>=0){
    if(message.msg_type==STOP){
        stop();
    }
    if(message.msg_type==ALL ||message.msg_type==ONE){
        printf("Message from: %d\n %s",message.client_id,message.message);
    }
    }

}
void stop(){
    send_message("",STOP);
    msgctl(client_queue, IPC_RMID, NULL);
    printf("ending.\n");
    exit(0);
}
