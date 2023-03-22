#include <unistd.h>
#include <stdio.h>
#include<string.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/times.h>
#include <time.h>

int wr_ret;
bool findInFile(char sign, char* filepath){
    char buff;
//    printf("character %c in file %s.\n", sign,filepath);
    int file = open(filepath,O_RDONLY);
    if(file==-1){
        printf("File not found %s.\n",filepath);
        return false;
    }
    while(read(file,&buff,1)==1){
        if(buff==sign){
//            printf("BUFF %c char %c.\n", buff,sign);
            printf("Found character %c in file %s.\n", sign,filepath);
            return true;
        }
    }
    close(file);
    printf("Character not found %c in file %s.\n", sign,filepath);
    return false;
}

void changeInFile(char old_sign,char new_sign,char* filepath_from,char* filepath_to){
    char buff;
    int file_from = open(filepath_from,O_RDONLY);
    int file_to = open(filepath_to,O_WRONLY|O_CREAT,S_IRUSR|S_IWUSR);
    while(read(file_from,&buff,1)==1){
        if(buff==old_sign){
            wr_ret=write(file_to,&new_sign,1);
            continue;
        }
        wr_ret=write(file_to,&buff,1);

    }
    close(file_to);
    close(file_from);
}
//time functions
typedef struct{
    clock_t realtime;
    clock_t usertime;
    clock_t systemtime;
}TimeStruct;

TimeStruct measureTime(){
    TimeStruct ts;
    struct tms start_tms;
    ts.realtime=times(&start_tms);
    ts.usertime=start_tms.tms_utime;
    ts.systemtime=start_tms.tms_stime;
    return ts;

}
void printTimes (TimeStruct* start,TimeStruct* end){
    printf("Real time: %f s, ",10000*(double)(end->realtime-start->realtime)/CLOCKS_PER_SEC);
    printf("User time: %f s, ",10000*(double)(end->usertime-start->usertime)/CLOCKS_PER_SEC);
    printf("System time: %f s\n",10000*(double)(end->systemtime-start->systemtime)/CLOCKS_PER_SEC);
}



int main(int argc, char *argv[])
{
    if(argc!=5){
        fprintf(stderr, "Function needs 4 arguments.\n");
        return 0;
    }
    TimeStruct start=measureTime();
    char* to_find = argv[1];
    char* to_change = argv[2];
    char* file_to_find=argv[3];
    char* file_to_change=argv[4];

    if(strlen(to_find)!=1 || strlen(to_change)!=1){
        fprintf(stderr, "First and second argument must be a single character.\n");
        return 0;
    }

    if(findInFile(to_find[0],file_to_find)){
        changeInFile(to_find[0],to_change[0],file_to_find,file_to_change);
        printf("Characters changed.\n");
    }
    printf("change_sys\n");
    TimeStruct stop=measureTime();
    printTimes(&start,&stop);
    printf("\n");



}