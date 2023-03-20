#include "dirent.h"
#include <sys/stat.h>
#include "stdio.h"

off_t getFileSize(char* filepath){
    struct stat buf;
    off_t filesize;
    if(stat(filepath,&buf)==0){
        if(!S_ISDIR(buf.st_mode)){
            filesize = buf.st_size;
        }
        else{
            return -1;
        }
    }
    else{
        fprintf(stderr, "Problem with file: %s .\n",filepath);
        return -1;
    }
    return filesize;
}

void searchDir(char* path){
    DIR* directory = opendir(path);
    off_t curr_size=0;
    long long dir_size=0;
    struct dirent* curr_file;
    curr_file = readdir(directory);
    while(curr_file!=NULL){
        curr_size= getFileSize(curr_file->d_name);
        if(curr_size!=-1){
            printf("%s: %ld\n",curr_file->d_name,curr_size);
            dir_size+=curr_size;
        }
        curr_file=readdir(directory);
        
    }
    printf("Wszystkie pliki: %lld\n ",dir_size);
    closedir(directory);
}

int main(){
    searchDir(".");
    return 0;
}