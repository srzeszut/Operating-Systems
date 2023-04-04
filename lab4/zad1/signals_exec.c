#include "stdio.h"
#include "string.h"
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

int parent=1;

typedef enum{
    IGNORE,
    MASK,
    PENDING
}signal_type;


void signal_handler(int signal){
    printf("EXEC: Received signal %d. PID: %d\n", signal,getpid());

}
void raise_signal(){
    printf("EXEC: Raising signal PID: %d\n",getpid());
    raise(SIGUSR1);
}

void signal_pending(){
    sigset_t sigset;
    sigpending(&sigset);
    if(sigismember(&sigset,SIGUSR1)){
        printf("EXEC: Signal is pending PID: %d\n",getpid());
    }
    else {
        printf("EXEC: Signal is not pending PID: %d\n",getpid());
    }

}
void signal_mask(){
    struct sigaction act;
    sigemptyset(&act.sa_mask);
    sigaddset(&act.sa_mask, SIGUSR1);
    sigprocmask(SIG_BLOCK, &act.sa_mask, NULL);
    printf("EXEC: Signal blocked PID: %d\n",getpid());
}


signal_type strToSignal(char* str){
    if (strcmp(str, "ignore") == 0) {
        return IGNORE;
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
            fprintf(stderr,"EXEC: Unknown signal.\n");
            return;
    }
}


int main(int argc, char* argv[]){

    if(argc==3){
        parent = atoi(argv[2]);
        if(strcmp("0",argv[2])!=0){
            fprintf(stderr, "EXEC: Function needs 1 argument second is setting automaticly.\n");
            return 0;
        }
    }
    if(argc<2 || argc>3){
        fprintf(stderr, "EXEC: Function needs 1 argument second is setting automaticly.\n");
        return 0;
    }

    signal_type user_signal = strToSignal(argv[1]);
    handle_signal(user_signal);
    fflush(NULL);

    if(parent){
        execl(argv[0],argv[0],argv[1],"0",NULL);
        perror("execl");
    }



    return 0;
}