#include"lib_wc.h"

int indexCheck (LibMemory* lib_memory,int index);

LibMemory LibMemory_create (size_t size ){
    return (LibMemory){
            .memory= calloc(size, sizeof(char*)),
            .curr_size = 0,
            .size=size,
    };
}

void LibMemory_init (LibMemory* lib_memory,size_t size ){
    lib_memory->memory = calloc(size, sizeof(char *));
    lib_memory->size = size;
    lib_memory->curr_size = 0;
}

char* LibMemory_getBlock (LibMemory* lib_memory,int index){
    if (indexCheck(lib_memory,index)){
        return lib_memory->memory[index];
    }
    return "";

}
void LibMemory_removeBlock(LibMemory* lib_memory,int index){
    if (indexCheck(lib_memory,index)){
        free(lib_memory->memory[index]);
        for (size_t i = index; i < lib_memory->curr_size - 1; i++) {
            lib_memory->memory[i] = lib_memory->memory[i + 1];
        }
        lib_memory->curr_size--;
    }
}
void LibMemory_emptyArray(LibMemory* lib_memory){
    for(size_t i = 0; i<lib_memory->curr_size;i++){
        free(lib_memory->memory[i]);

    }
    lib_memory->curr_size=0;
}

void LibMemory_destruct (LibMemory* lib_memory){
    LibMemory_emptyArray(lib_memory);
    free(lib_memory->memory);
}


int indexCheck (LibMemory* lib_memory,int index){
    if (index>=lib_memory->curr_size){
        fprintf( stderr, "Index out of range");
        return 0;
    }
    return 1;
}
void LibMemory_count (LibMemory* lib_memory, char* filename);