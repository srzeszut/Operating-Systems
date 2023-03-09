#include <stdio.h>
#include <stdlib.h>

typedef struct{
    char** memory;
    size_t size;
    size_t curr_size;
}LibMemory;

LibMemory LibMemory_create (size_t size );
void LibMemory_init (LibMemory* lib_memory,size_t size );
void LibMemory_count (LibMemory* lib_memory, char* filename);
char* LibMemory_getBlock (LibMemory* lib_memory,int index);
void LibMemory_removeBlock(LibMemory* lib_memory,int index);
void LibMemory_destruct (LibMemory* lib_memory);
