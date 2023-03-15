#ifndef DLL_H
#define DLL_H

#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include "lib_wc.h"
void *handle;

#ifdef USE_DLL

void loadSymbol(const char* filepath){
    handle=dlopen(filepath,RTLD_LAZY);
    if(!handle){
        fprintf(stderr, "DLL not found\n %s\n",filepath);
        return;
    }
    *(void**) (&LibMemory_create)= dlsym(handle,"LibMemory_create");
    *(void**) (&LibMemory_init)= dlsym(handle,"LibMemory_init");
    *(void**) (&LibMemory_addBlock)= dlsym(handle,"LibMemory_addBlock");
    *(void**) (&LibMemory_getBlock)= dlsym(handle,"LibMemory_getBlock");
    *(void**) (&LibMemory_removeBlock)= dlsym(handle,"LibMemory_removeBlock");
    *(void**) (&LibMemory_destroy)= dlsym(handle,"LibMemory_destroy");
}
void closeHandle(){
    dlclose(handle);
}
#else

void loadSymbol(const char* filepath){}
void closeHandle(){}
#endif

#endif