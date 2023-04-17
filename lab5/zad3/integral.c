#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "sys/wait.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <fcntl.h>

#define PIPE_PATH "/tmp/int_pipe"
#define MAX_LENGTH 255

int temp;

char buffer_a[MAX_LENGTH];
char buffer_b[MAX_LENGTH];


int main(int argc, char* argv[]){
    if(argc!=3){
        fprintf(stderr,"Program needs 2 arguments.\n");
        return 1;
    }
    double precision = strtod(argv[1],NULL);
    if(precision==0.0){
        fprintf(stderr,"Invalid argument.\n");
        return 1;
    }

    int no_processes=atoi(argv[2]);
    if(no_processes==0){
        fprintf(stderr,"Invalid argument.\n");
        return 1;
    }
    printf("Precision: %.10f No_processes:%d\n",precision,no_processes);


    if(no_processes*precision>1){
        no_processes=1/precision;
    }

    double interval=1.0/no_processes;
    double current=0.0;
    double answer=0.0;

    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);
    mkfifo(PIPE_PATH, 0666);

    for( int i=0;i<no_processes;i++){
        if (fork() == 0) {
            snprintf(buffer_a,MAX_LENGTH, "%lf", current);
            snprintf(buffer_b, MAX_LENGTH,"%lf", current+interval);
            execl("./count","count",argv[1],buffer_a,buffer_b,NULL);//precision a b
            return 0;
        }
        current+=interval;
    }
    fflush(stdout);
    FILE* fd= fopen(PIPE_PATH, "r");
    char buffer[MAX_LENGTH];
    int lines_read=0;
    while(wait(NULL)>0);
    while (lines_read<no_processes){
        while(fgets(buffer, MAX_LENGTH, fd)) {
            answer += strtod(buffer, NULL);
            lines_read++;
//            printf("buff: %s Ans: %lf lines: %d\n",buffer,answer,lines_read);
        }
    }
    fclose(fd);


    printf("Sum: %f No_proceesses: %d Precision: %.10f Interval: %lf\n", answer,no_processes,precision,interval);
    remove(PIPE_PATH);
    clock_gettime(CLOCK_MONOTONIC, &end);
    double execution_time = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
    printf("Time: %fs\n",execution_time);
    printf("\n");

    return 0;
}