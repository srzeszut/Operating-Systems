#include "stdio.h"
#include "string.h"
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include "sys/wait.h"

int parent=1;

typedef enum{
    IGNORE,
    HANDLER,
    MASK,
    PENDING
}signal_type;


void signal_handler(int signal){
    printf("FORK: Received signal %d. PID: %d\n", signal,getpid());

}
void raise_signal(){
    printf("FORK: Raising signal PID: %d\n",getpid());
    raise(SIGUSR1);
}

void signal_pending(){
    sigset_t sigset;
    sigpending(&sigset);
    if(sigismember(&sigset,SIGUSR1)){
        printf("FORK: Signal is pending PID: %d\n",getpid());
    }
    else {
        printf("FORK: Signal is not pending PID: %d\n",getpid());
    }

}
void signal_mask(){
    struct sigaction act;
    sigemptyset(&act.sa_mask);
    sigaddset(&act.sa_mask, SIGUSR1);
    sigprocmask(SIG_BLOCK, &act.sa_mask, NULL);
    printf("FORK: Signal blocked PID: %d\n",getpid());
}


signal_type strToSignal(char* str){
    if (strcmp(str, "ignore") == 0) {
        return IGNORE;
    } else if (strcmp(str, "handler") == 0) {
        return HANDLER;
    } else if (strcmp(str, "mask") == 0) {
        return MASK;
    } else if (strcmp(str, "pending") == 0) {
        return PENDING;
    }
    return -1;
}

void handle_signal(signal_type user_signal){
    switch (user_signal) {
        case IGNORE:
            signal(SIGUSR1,SIG_IGN);
            raise_signal();
            break;
        case HANDLER:
            signal(SIGUSR1,signal_handler);
            raise_signal();
            break;
        case MASK:
            signal_mask();
            raise_signal();
            break;
        case PENDING:
            signal(SIGUSR1,signal_handler);
            if(parent){
                signal_mask();
                raise_signal();
            }
            signal_pending();
            break;
        default:
            fprintf(stderr,"FORK: Unknown signal.\n");
            return;
    }
}


int main(int argc, char* argv[]){
    if(argc!=2){
        fprintf(stderr, "FORK: Function needs 1 argument.\n");
        return 0;
    }
    signal_type user_signal = strToSignal(argv[1]);
    handle_signal(user_signal);
    fflush(NULL);

    parent=fork();
    if(!parent){
        handle_signal(user_signal);
    }wait(NULL);

    fflush(NULL);

    return 0;
}