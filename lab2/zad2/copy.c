#include <stdio.h>
#include<string.h>
#include <stdbool.h>
#include <sys/times.h>
#include <time.h>
#include <stdlib.h>


size_t block_size=BLOCK_SIZE;

void swap(char*left, char* right){
    char tmp =*left;
    *left=*right;
    *right=tmp;
}
void reverse(char*buff,size_t size){
    for(int i=0;i<size/2;i++){
        swap(&buff[i],&buff[size-i-1]);
    }
}

void changeOneByte(char* filepath_from, char* filepath_to){//obsluga bledów
    char buff;
    FILE* file_from = fopen(filepath_from,"rb");
    FILE* file_to = fopen(filepath_to,"w+b");
    if(file_from==NULL){
        printf("File not found %s.\n",filepath_from);
        return;
    }
    fseek(file_from, 0, SEEK_END);

    if(fseek(file_from, -1, SEEK_CUR)==0){
    if(fread(&buff,1,1,file_from)==1){
        fwrite(&buff,1,1,file_to);
//        printf("buff: %c\n",buff);
        }
    }

    while(fseek(file_from, -2, SEEK_CUR)==0){
        if(fread(&buff,1,1,file_from)==1){
            fwrite(&buff,1,1,file_to);
//            printf("buff: %c\n",buff);
        }

    }
    fclose(file_from);
    fclose(file_to);


}
void changeBlocks(char* filepath_from, char* filepath_to){
    char buff[block_size];
    FILE* file_from = fopen(filepath_from,"rb");
    FILE* file_to = fopen(filepath_to,"w+b");
    if(file_from==NULL){
        printf("File not found %s.\n",filepath_from);
        return;
    }
    fseek(file_from, 0, SEEK_END);
    long file_size = ftell(file_from);
    long rest =file_size%block_size;
//    printf("rest: %ld \n",rest);
    if(fseek(file_from, -block_size, SEEK_CUR)==0){
        if(fread(buff,1,block_size,file_from)==block_size){
            reverse(buff,block_size);
            fwrite(buff,1,block_size,file_to);
//            printf("buff: %s\n",buff);
        }
        while(fseek(file_from, -2*block_size, SEEK_CUR)==0){
            if(fread(buff,1,block_size,file_from)==block_size){
                reverse(buff,block_size);
                fwrite(buff,1,block_size,file_to);
//                printf("buff: %s\n",buff);
            }
        }
    }
    fseek(file_from, 0, SEEK_SET);
    if(fread(buff,1,rest,file_from)==rest){
        reverse(buff,rest);
        fwrite(buff,1,rest,file_to);
//        printf("buff: %s\n",buff[1023]);
    }


    fclose(file_from);
    fclose(file_to);



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
int main(int argc, char *argv[]){
    if(argc!=3){
        fprintf(stderr, "Function needs 2 arguments.\n");
        return 0;
    }

    char* file_from = argv[1];
    char* file_to = argv[2];


//    printf("argc: %d\n",argc);
    printf("FILES: %s %s \n",file_from,file_to);
    clock_t start_time = clock();
    if(block_size ==1){
        changeOneByte(file_from,file_to);
    }
    else{
        changeBlocks(file_from, file_to);
    }

    clock_t end_time = clock();
    double execution_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    printf("Time: %f\n",execution_time);
    printf("Block size: %ld\n" ,block_size);

    printf("\n");


}