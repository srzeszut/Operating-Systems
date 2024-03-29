#ifndef WCLIB_H
#define WCLIB_H

#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include <stdbool.h>

typedef struct{
    char** memory;
    size_t size;
    size_t curr_size;
    bool* holes;
}LibMemory;

#ifdef USE_DLL


    void (*LibMemory_init ) (LibMemory* ,size_t  );
    void (*LibMemory_addBlock) (LibMemory* , char* );
    char* (*LibMemory_getBlock) (LibMemory* ,int );
    void (*LibMemory_removeBlock) (LibMemory* ,int );
    void (*LibMemory_destroy) (LibMemory* );

#else


    void LibMemory_init (LibMemory* lib_memory,size_t size );
    void LibMemory_addBlock (LibMemory* lib_memory, char* filename);
    char* LibMemory_getBlock (LibMemory* lib_memory,int index);
    void LibMemory_removeBlock(LibMemory* lib_memory,int index);
    void LibMemory_destroy (LibMemory* lib_memory);

#endif

#endif
