#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "sys/wait.h"
#include <sys/times.h>
#include <time.h>
#include <fcntl.h>

#define PIPE_PATH "/tmp/int_pipe"
char buffer_write[1024]="";

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
int main(int argc, char* argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Program needs 3 arguments.\n");
        return 1;
    }
    double precision = strtod(argv[1], NULL);
    if (precision == 0.0) {
        fprintf(stderr, "Invalid argument.\n");
        return 1;
    }

    double a = strtod(argv[2], NULL);
    double b = strtod(argv[3], NULL);

    double answer = rectangle(precision,a,b);
//    printf("PID: %d Sum: %lf\n",getpid(),answer);
    int fd = open(PIPE_PATH, O_WRONLY);
    int size = sprintf(buffer_write, "%lf\n", answer);
    write(fd,buffer_write,size);
    close(fd);
    return 0;
}