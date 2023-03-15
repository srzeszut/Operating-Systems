#include <stdio.h>
#include<string.h>
#include <stdbool.h>
#include <sys/times.h>
#include <time.h>

bool findInFile(char sign, char* filepath){
    char buff;
    FILE* file = fopen(filepath,"r");
    while(fread(&buff,1,1,file)==1){
        if(buff==sign){
            printf("Found character %c in file %s.\n", sign,filepath);
            return true;
        }
    }
    fclose(file);
    printf("Character not found %c in file %s.\n", sign,filepath);
    return false;
}

void changeInFile(char old_sign,char new_sign,char* filepath_from,char* filepath_to){
    char buff;
    FILE* file_from = fopen(filepath_from,"r");
    FILE* file_to = fopen(filepath_to,"w+");
    while(fread(&buff,1,1,file_from)==1){
        if(buff==old_sign){
            fwrite(&new_sign,1,1,file_to);
            continue;
        }
        fwrite(&buff,1,1,file_to);

    }
    fclose(file_to);
    fclose(file_from);
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
//    printf("ARGS: %s %s %s %s\n",to_find,to_change,file_to_find,file_to_change);
    TimeStruct stop=measureTime();
    printf("change_lib\n");
    printTimes(&start,&stop);
    printf("\n");
}