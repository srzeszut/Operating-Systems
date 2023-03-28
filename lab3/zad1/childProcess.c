#include "stdio.h"
#include <stdlib.h>
#include <sys/types.h>
#include<sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]){
    if(argc!=2){
        fprintf(stderr, "Function needs 1 argument.\n");
        return 0;
    }
    int no_processes = atoi(argv[1]);
    pid_t child_pid;
    for(int i=0;i<no_processes;i++){
        child_pid=fork();
        if(child_pid==0){
            printf("Parent PID: %d,  Child PID: %d\n", (int)getppid(),(int)getpid());
            return 0;
        }

    }
    while(wait(NULL)>0);
    printf("Number of processes: %d\n", no_processes);
    return 0;
}