#include "stdio.h"
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Function needs 1 argument.\n");
        return 0;
    }
    char* path=argv[1];
    printf("%s ",argv[0]);
    fflush(stdout);
    execl("/bin/ls","ls",path,NULL);
    printf("\n");
    return 0;
}
