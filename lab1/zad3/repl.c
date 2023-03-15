#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "string.h"
#include <stdbool.h>
#include <sys/times.h>
#include <time.h>
#include "lib_wc.h"
#include "dlopen.h"
#define MAX_COMMAND_SIZE 1024

bool active = true;
bool isInitialized=false;

void parseCommand(char* commandLine,char** output){

    int command_start=0;
    int lineLength=strlen(commandLine);
    int command_end=strlen(commandLine)-1;
    int arg_start=-1;
    int arg_end= strlen(commandLine)-1;
    for(int i=0;i<strlen(commandLine);i++){
        if(commandLine[i]==' '){continue;}
        else{command_start=i;break;}
    }
    for(int i=command_start;i<lineLength;i++){
        if(commandLine[i]!=' '){continue;}
        else{command_end=i;break;}
    }
    for(int i=command_end;i<lineLength;i++){
        if(commandLine[i]==' '){continue;}
        else{arg_start=i;break;}
    }

//    printf("indexes: %d %d %d %ld\n", command_start,command_end,arg_start, strlen(commandLine));

    output[0]= calloc(command_end-command_start+1,sizeof(char));
    strncpy(output[0],commandLine+command_start,command_end-command_start);
    if(arg_start!=-1){
        output[1]= calloc(arg_end-arg_start+1,sizeof(char));
        strncpy(output[1],commandLine+arg_start,arg_end-arg_start);
    }



}
void init(LibMemory* lib_memory,size_t size){
    if(!isInitialized){
        LibMemory_init(lib_memory,size);
        isInitialized=true;
    } else{
        fprintf(stderr, "Run destroy before another initialization.\n");
        return;
    }

}
void count(LibMemory* lib_memory,char* filepath){
    if(!isInitialized){
        fprintf(stderr, "Memory not yet initialized.\n");
        return;
    }
    if(lib_memory == NULL){
        fprintf(stderr, "Memory not yet initialized.\n");
        return;
    }
    LibMemory_addBlock(lib_memory,filepath);

}
void show(LibMemory* lib_memory,int index){
    if(!isInitialized){
        fprintf(stderr, "Memory not yet initialized.\n");
        return;
    }
    char* wc_output=LibMemory_getBlock(lib_memory,index);
    if(wc_output!=NULL){
        printf("wc: %s\n",wc_output);

    }


}
void delete(LibMemory* lib_memory,int index){
    if(!isInitialized){
        fprintf(stderr, "Memory not yet initialized.\n");
        return;
    }
    LibMemory_removeBlock(lib_memory,index);
}
void destroy(LibMemory* lib_memory){
    if(!isInitialized){
        fprintf(stderr, "Memory not yet initialized.\n");
        return;
    }
    LibMemory_destroy(lib_memory);
    isInitialized=false;
}

bool checkIntArgs(char* args){

    if(strlen(args)==0){
        return false;
    }
    for(int i=0;i< strlen(args);i++){
        if(!isdigit(args[i])){
            return false;
        }
    }
    return true;

}

void runCommand(LibMemory* lib_memory,char** commandAndArgs){
        if(commandAndArgs!=NULL) {
            int arg;
            if (strcmp(commandAndArgs[0],"init")==0) {
                if (!checkIntArgs(commandAndArgs[1])) {
                    fprintf(stderr, "init: Invalid argument.\n");
                    return;
                }
                arg = atoi(commandAndArgs[1]);
                init(lib_memory, arg);

            }
            else if (strcmp(commandAndArgs[0],"count")==0) {
                count(lib_memory, commandAndArgs[1]);

            }
            else if (strcmp(commandAndArgs[0],"show")==0) {
                if (!checkIntArgs(commandAndArgs[1])) {
                    fprintf(stderr, "show: Invalid argument.\n");
                    return;
                }
                arg = atoi(commandAndArgs[1]);
                show(lib_memory, arg);
            }
            else if (strcmp(commandAndArgs[0],"delete")==0) {
                if (!checkIntArgs(commandAndArgs[1])) {
                    fprintf(stderr, "delete: Invalid argument.\n");
                    return;
                }
                arg = atoi(commandAndArgs[1]);
                delete(lib_memory, arg);

            }
            else if (strcmp(commandAndArgs[0],"destroy")==0) {
                destroy(lib_memory);

            }
            else if(strcmp(commandAndArgs[0],"exit")==0){
                active = false;

            }
            else{
                fprintf(stderr, "Invalid command.\n");

            }
        }

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


int main() {
    loadSymbol("lib_wc.so");
    LibMemory *lib_memory = malloc(sizeof(LibMemory));

    char commandLine[MAX_COMMAND_SIZE];
    while (active) {
        printf("[REPL]>> ");
        if (fgets(commandLine, MAX_COMMAND_SIZE, stdin) != NULL) {
            TimeStruct start = measureTime();
            char *commandAndArgs[2];
            parseCommand(commandLine, commandAndArgs);
            fflush(NULL);
//            printf(" output0: %s\n", commandAndArgs[0]);
//            if (commandAndArgs[1] != NULL) { printf(" output1: %s\n", commandAndArgs[1]); }//free na koncu
            runCommand(lib_memory,commandAndArgs);
            fflush(NULL);
//            sleep(1);
            free(commandAndArgs[0]);
            free(commandAndArgs[1]);
            TimeStruct end = measureTime();
            printTimes(&start,&end);


        }
    }
    closeHandle();
}