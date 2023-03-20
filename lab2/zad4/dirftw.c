#include "dirent.h"
#include <sys/stat.h>
#include "stdio.h"
#include <ftw.h>

static off_t total_size =0;
int getFileSize(const char* filepath, const struct stat* buf,int flag){
    if(!S_ISDIR(buf->st_mode)){
        printf("%s: %ld\n",filepath,buf->st_size);
        total_size+=buf->st_size;
    }

    return 0;
}



int main(){
    if(ftw(".",getFileSize,1)==-1){
        printf("error\n");
    }
    printf("Total: %ld\n",total_size);
    return 0;
}