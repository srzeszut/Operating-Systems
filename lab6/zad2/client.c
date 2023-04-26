#include "server.h"
#include <time.h>
#include <sys/select.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int client_id;
char client_name[MAX_NAME] ;
mqd_t server_queue;
mqd_t client_queue;

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

void get_client_name(){
    int len=6;
    client_name[0]='/';
    srand(time(NULL));
    for (int i = 1; i < len; i++) {
        client_name[i] = rand() % 26 + 'A';
    }
    client_name[len] = '\0';
}


int main(){

    printf("CLIENT\n");

    server_queue = mq_open(SERVER_QUEUE_NAME,O_RDWR);
    if (server_queue == -1)
    {
        perror("Cannot create server queue.");
        exit(EXIT_FAILURE);
    }
    get_client_name();
    mq_unlink(client_name);
    client_queue = create_queue(client_name);
//    free(client_name);
    if (client_queue == -1)
    {
        perror("Cannot create client queue.");
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
        if (strcmp(words[0], "LIST\n") == 0) {
            send_message("",LIST);
            list();

        }
        else if(strcmp(words[0], "2ALL") == 0){
            send_message(words[1],ALL);

        }
        else if(strcmp(words[0], "2ONE") == 0){
            if(atoi(words[1])==0 && strcmp(words[1],"0")!=0){
                fprintf(stderr,"You must enter ID\n");
            }
            else
            {
                printf("%s\n",words[1]);
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
    mq_send(server_queue, (char*) &message, MSG_SIZE, 0);
//    printf("message sent.\n");
}
void send_message_to_client(char* text,jobs type,int client_to){
    msgBuff message;
    strcpy(message.message,text);
    message.client_id=client_id;
    message.client_to=client_to;
    message.msg_type=type;
    mq_send(server_queue, (char*) &message, MSG_SIZE, 0);
//    printf("message sent.\n");
}
void init(){
    msgBuff init_msg;
    init_msg.msg_type = INIT;
    strcpy(init_msg.message, client_name);
//    printf("%d\n",MSG_SIZE);
//    printf("%ld\n",sizeof((char*) &init_msg));

    msgBuff confirmation;
//    printf("%s\n",confirmation.message);
    int wait=0;
    if (mq_send(server_queue, (char*) &init_msg, MSG_SIZE, 0) == -1)
    {
        perror("Cannot send innit message.");
        exit(0);
    }
    int ret;
    while((ret=mq_receive(client_queue, (char*) &confirmation,MSG_SIZE,NULL))<0){
        if(wait>3){
            fprintf(stderr,"Recieved no confirmation from a server\n");
            exit(EXIT_FAILURE);
        }
        printf("waiting for confirmation\n");
        sleep(1);
        wait++;

    }
//    printf("r:%d\n",ret);
    client_id= atoi(confirmation.message);
//    printf("%s\n",confirmation.message);
//    printf("%s\n",(char*) &confirmation.message);
    printf("Client id: %d\n",client_id);
}
void list(){
    msgBuff message;
    mq_receive(client_queue,(char*)&message,MSG_SIZE,NULL);
    printf("%s\n",message.message);
}
void server_message(){
    msgBuff message;
    struct timespec my_time;

    clock_gettime(CLOCK_REALTIME, &my_time);
    my_time.tv_sec += 0.1;
    while (mq_timedreceive(client_queue, (char *) &message,MSG_SIZE, NULL, &my_time) != -1){//time
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
    mq_close(client_queue);
    mq_unlink(client_name);
    printf("ending.\n");

    exit(0);
}
