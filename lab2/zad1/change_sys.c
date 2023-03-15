#include <unistd.h>
#include <stdio.h>
#include<string.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <fcntl.h>

bool findInFile(char sign, char* filepath){
    char buff;
//    printf("character %c in file %s.\n", sign,filepath);
    int file = open(filepath,O_RDONLY);
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
            write(file_to,&new_sign,1);
            continue;
        }
        write(file_to,&buff,1);

    }
    close(file_to);
    close(file_from);
}




int main(int argc, char *argv[])
{
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

}