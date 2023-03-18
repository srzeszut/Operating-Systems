#include <stdio.h>
#include<string.h>
#include <stdbool.h>
#include <sys/times.h>
#include <time.h>

void changeOneByte(char* filepath_from, char* filepath_to){
    char buff;
    FILE* file_from = fopen(file_from,"r");
    FILE* file_to = fopen(file_from,"w+");
    fseek(file_from, 0, SEEK_END);
    int fd =ftell(file_from)-1;
    while(fread(&buff,1,1,file_from)==1){

    }


}
void changeBlocks(char* file_from, char* file_to){

}
int main(){

}