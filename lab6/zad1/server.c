#include "server.h"
#include "stdbool.h"
#include <time.h>
client clients[MAX_NO_CLIENTS];
int server_queue;
bool active[MAX_NO_CLIENTS];
FILE* log_file;

void init(char* message){
    int new_id=-1;
    for(int i=0;i<MAX_NO_CLIENTS;i++){
        if(!active[i]){
            new_id=i;
            break;
        }
    }
    if(new_id==-1){
        return;
    }
    int key = atoi(message);
    clients[new_id].client_id=new_id;
    clients[new_id].client_key= key;
    int client_queue=msgget(key, 0666);
    if (client_queue == -1){
        perror("Nie udało się otworzyć kolejki klienta");
        exit(EXIT_FAILURE);
    }
    clients[new_id].client_queue=client_queue;
    active[new_id]=true;

    msgBuff confirmation;
    confirmation.msg_type = 6;
    sprintf(confirmation.message, "%d", clients[new_id].client_id);

    if (msgsnd(client_queue, &confirmation, strlen(confirmation.message) + 1, 0) == -1)
    {
        perror("Cannot send confirmation message.");
        exit(EXIT_FAILURE);
    }
    printf("Client: %d %d %d\n",clients[new_id].client_id, clients[new_id].client_key, clients[new_id].client_queue);

}
void list(int client_id);

void to_all(char* message);
void to_one(char* message,int client_id);
void send_message(char* text,jobs type,int client_id);
void stop(int client_id);
void end();

int main(){
    printf("SERVER\n");


    key_t server_key = ftok(HOME_PATH, SERVER_KEY);
    server_queue = msgget(server_key, IPC_CREAT | 0666);
    if (server_queue == -1)
    {
        perror("Cannot create server queue.");
        exit(EXIT_FAILURE);
    }
    msgBuff message;
    time_t rawtime;
    struct tm * timeinfo;
    signal(SIGINT,end);


    log_file= fopen("out.txt","a");
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    fprintf(log_file,"\n\nServer turned on at: %s\n\n",asctime(timeinfo));


    while(1){
        if(msgrcv(server_queue,&message,MSG_SIZE,0,0)>0){

        if (message.msg_type != INIT) {
                time(&rawtime);
                timeinfo = localtime(&rawtime);
                fprintf(log_file,"\nCurrent local time and date: %s", asctime(timeinfo));
                fprintf(log_file,"ID: %d Message type: %ld Message: %s", message.client_id,message.msg_type ,message.message);
            }
//        printf("msg: %ld %s\n",message.msg_type,message.message);
            switch (message.msg_type) {
                case INIT: {
//                    printf("init\n");
                    init(message.message);
                }
                    break;
                case LIST: {
//                    printf("list\n");
                    list(message.client_id);
                }
                    break;
                case ALL: {
                    to_all(message.message);
                }
                    break;
                case ONE: {
                    to_one(message.message,message.client_to);
                }
                    break;
                case STOP: {
                    stop(message.client_id);

                }
                    break;

            }
        }

    }

    return 0;
}

void send_message(char* text,jobs type,int client_id){
    msgBuff message;
    strcpy(message.message,text);
    message.client_id=client_id;
    message.msg_type=type;
    msgsnd(clients[client_id].client_queue, &message, MSG_SIZE, 0);
}
void list(int client_id){
    char message[MAX_MSG_SIZE]="";
    printf("active: ");
    for(int i=0;i<MAX_NO_CLIENTS;i++){
        printf(" %d ",active[i]);
        if(active[i]){
            sprintf(message + strlen(message), "ID %d is running.\n", i);
        }
    }
    printf("\n");
    send_message(message,LIST,client_id);
}
void to_all(char* message){
    for(int i=0;i<MAX_NO_CLIENTS;i++){
        if(active[i]){
            printf("sending: %d %s",i,message);
            send_message(message,ALL,i);
        }
    }

}
void to_one(char* message,int client_id){
        if(active[client_id]){
            printf("sending: %d %s",client_id,message);
            send_message(message,ONE,client_id);
        }
    }
void stop(int client_id){

    active[client_id]=false;
    clients[client_id].client_id=-1;

    clients[client_id].client_key=-1;
}

void end(){
    msgBuff message;
    for(int i=0;i<MAX_NO_CLIENTS;i++) {
        if (active[i]) {
            send_message("", STOP, i);
            msgrcv(server_queue,&message,MSG_SIZE,STOP,0);
        }
    }
    fclose(log_file);

    msgctl(server_queue, IPC_RMID, NULL);
    printf("ending.\n");
    exit(0);

}

