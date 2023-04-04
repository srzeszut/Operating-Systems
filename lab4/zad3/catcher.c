#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include "stdbool.h"

typedef enum{
    PRINTNUMBERS = 1,
    CURRTIME = 2,
    REQUESTS = 3,
    CURRTIMELOOP = 4,
    END = 5
}CatcherModes;


int requests=0;
CatcherModes catcher_mode=0;
bool mode_ended = false;

void handler(int signum, siginfo_t *info, void *context) {
    int sender_PID=info->si_pid;

    int mode = info->si_value.sival_int;
    if(mode<1 ||mode>5){
        fprintf(stderr,"CATCHER: Mode doesn't exists %d\n",mode);
    } else{
        catcher_mode=mode;
        requests++;
        mode_ended = false;

    }
    kill(sender_PID, SIGUSR1);
}

void print_numbers(){
    for( int i=1;i<=100;i++){
        printf("CATCHER: %d\n",i);
    }
    mode_ended=true;

}
void curr_time(){
    time_t raw_time;
    struct tm * time_info;
    time ( &raw_time );
    time_info = localtime ( &raw_time );
    printf ( "CATCHER: Current local time and date: %s", asctime (time_info) );
    mode_ended=true;

}

void no_requests(){
    printf("CATCHER: number of requests: %d\n",requests);
    mode_ended=true;

}
void end_program(){
    printf("CATCHER: ending\n");
    exit(0);

}


int main(){

    printf("CATCHER: starting with PID:%d\n ", getpid());


    struct sigaction act;
    act.sa_sigaction=handler;
    sigemptyset(&act.sa_mask);
    act.sa_flags= SA_SIGINFO;
    sigaction(SIGUSR1,&act,NULL);

    while(1){
        if(mode_ended) continue;

            switch(catcher_mode){
                case PRINTNUMBERS: {
                    print_numbers();
                    break;
                }
                case CURRTIME:{
                    curr_time();
                    break;
                }
                case CURRTIMELOOP: {
                    curr_time();
                    sleep(1);
                    mode_ended=false;
                    break;
                }
                case REQUESTS: {
                    no_requests();
                    break;
                }
                case END: {
                    end_program();
                    break;
                }
            }
        }
    return 0;
    }

