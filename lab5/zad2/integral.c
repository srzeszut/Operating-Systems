#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "sys/wait.h"
#include <time.h>

char buffer_write[1024]="";
char buffer_read[1024]="";

double f(double x){
    return 4.0/((x*x)+1.0);
}

double rectangle(double h,double a,double b){
    double sum=0.0;
    for (double i = a;i<b;i+=h) {
        sum += f(i)*h;
    }
    return sum;
}

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
//    printf("%lf %d\n",precision,no_processes);


    if(no_processes*precision>1){
        no_processes=1/precision;
    }


    double interval=1.0/no_processes;
    double current=0.0;

    int* sums = calloc(no_processes,sizeof(int));
    struct timespec start, end;
    clock_gettime(CLOCK_REALTIME, &start);

    for( int i=0;i<no_processes;i++){
        int fd[2];
        pipe(fd);
        pid_t pid = fork();
        if (pid == 0) { // dziecko

            close(fd[0]);
            double ans = rectangle(precision,current,current+interval);
//            printf("Process: %d PID: %d Sum: %lf\n",i,getpid(),ans);
            int size = sprintf(buffer_write, "%lf", ans);
            write(fd[1],buffer_write,size);
            return 0;

        } else { // rodzic
            close(fd[1]);
            sums[i]=fd[0];

        }
        current+=interval;

    }

    while(wait(NULL)>0);

    double answer=0.0;
    for( int i=0;i<no_processes;i++){
        int n= read(sums[i], buffer_read, sizeof(buffer_read));
        buffer_read[n]='0';
        answer+=strtod(buffer_read,NULL);

    }

    printf("Sum: %f No_proceesses: %d Precision: %.10f Interval: %lf\n", answer,no_processes,precision,interval);

    free(sums);
    clock_gettime(CLOCK_REALTIME, &end);
    double execution_time = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
    printf("Time: %fs\n",execution_time);
    printf("\n");

    return 0;
}