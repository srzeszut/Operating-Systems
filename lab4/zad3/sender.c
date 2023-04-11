#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>


int confirmations=0;
void handler(int signum, siginfo_t *info, void *context) {
    printf("Recieved confirmation\n");
    confirmations++;

}
void send_signal_to(int pid,int value){
    union sigval sv;
    sv.sival_int = value;
    sigqueue(pid, SIGUSR1, sv);
    printf("SENDER: sending value %d to PID: %d\n",value, pid);

}


int main(int argc , char* argv[]){

    if(argc<2){
        fprintf(stderr,"SENDER: Function needs at least 2 arguments\n");
        return 1;
    }
//    sigset_t mask;
//    sigemptyset(&mask);
//    sigaddset(&mask, SIGUSR1);

    struct sigaction act;
    act.sa_sigaction=handler;
    sigemptyset(&act.sa_mask);
    act.sa_flags= SA_SIGINFO;
    sigaction(SIGUSR1,&act,NULL);
    int pause;


    for(int i=2;i<argc;i++){
        send_signal_to(atoi(argv[1]), atoi(argv[i]));
        pause=0;
        while(confirmations<=i-2){
            if(pause==10){
                printf("SENDER: Ending. Problem with getting confirmation.\n");
                return 1;
            }
            printf("SENDER: Waiting for confirmation\n");
            sleep(1);
            pause++;
        }


    }


    return 0;
}