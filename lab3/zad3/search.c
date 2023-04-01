#include "stdio.h"
#include <unistd.h>
#include "string.h"
#include "dirent.h"
#include <limits.h>
#include "stdlib.h"
#include <sys/stat.h>
#include<sys/wait.h>

char path[PATH_MAX]= "";
char new_path[PATH_MAX]= "";
char program_path[PATH_MAX]= "";

void find(char* filepath,char* pattern,int block_size){

    FILE* file = fopen(filepath,"r");
    char* buff=calloc(block_size,sizeof(char));
    if(file==NULL){
        perror("Problem with opening a file");
        free(buff);
        return;
    }
    if(fread(buff,1,block_size,file)==block_size){
            if(strcmp(buff,pattern)==0){
                printf("PID: %d, Path: %s\n",(int)getpid(),filepath);
                fflush(NULL);
            }
        }
    fclose(file);
    free(buff);

}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Function needs 2 arguments.\n");
        return 0;
    }

    int block_size;
    block_size=strlen(argv[2]);

    if(block_size>255){
        fprintf(stderr, "Second argument too long .\n");
        return 0;
    }

    if(realpath(argv[1],path)==NULL){
        perror("Realpath error");
        return 1;
    }
    if(realpath(argv[0],program_path)==NULL){
        perror("Realpath error");
        return 1;
    }

    struct stat buf;
    DIR* directory =opendir(path);
     if(directory==NULL){
       perror("Failed to open directory");
          return 1;
     }

     struct dirent* curr_file;
     pid_t child_pid;

     while((curr_file = readdir(directory))){
         if(strcmp(curr_file->d_name,".")==0 || strcmp(curr_file->d_name,"..")==0) { continue; }
//         printf("%s\n",path);
         strcpy(new_path,path);
         strcat(new_path,"/");
         strcat(new_path,curr_file->d_name);
//         printf("%s\n",new_path);
         if(stat(new_path,&buf)==0) {
             if(S_ISDIR(buf.st_mode)){
                 child_pid=fork();
                 if(child_pid==0){
                    int err= execl(program_path,program_path,new_path,argv[2],NULL);
                    if(err==-1){
                        closedir(directory);
                        return 1;
                    }
                 }
             }
             else{
                 find(new_path,argv[2],block_size);
             }
         }
         else{
             perror("Failed to read information with stat() ");
             printf("%s\n",new_path);
             return 1;
         }
     }

     closedir(directory);
     while(wait(NULL)>0);

    return 0;
}