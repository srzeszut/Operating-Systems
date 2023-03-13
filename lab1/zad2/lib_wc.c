#include"lib_wc.h"


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
    printf("Initialized memory block with size: %ld\n",size);
}

int indexCheck (LibMemory* lib_memory,int index){
    if (index>=lib_memory->curr_size){
        fprintf( stderr, "Index out of range\n");
        return 0;
    }
    return 1;
}

char* LibMemory_getBlock (LibMemory* lib_memory,int index){

    if (indexCheck(lib_memory,index)){
        return lib_memory->memory[index];
    }
    return NULL;

}
void LibMemory_removeBlock(LibMemory* lib_memory,int index){
    if (indexCheck(lib_memory,index)){
        free(lib_memory->memory[index]);
        for (size_t i = index; i < lib_memory->curr_size - 1; i++) {
            lib_memory->memory[i] = lib_memory->memory[i + 1];
        }
        lib_memory->curr_size--;
        printf("Removed block at index: %d\n", index);
    }

}
void LibMemory_emptyArray(LibMemory* lib_memory){
    for(size_t i = 0; i<lib_memory->curr_size;i++){
        free(lib_memory->memory[i]);

    }
    lib_memory->curr_size=0;
}

void LibMemory_destroy(LibMemory* lib_memory){
    LibMemory_emptyArray(lib_memory);
    free(lib_memory->memory);
    printf("Destroyed block\n");
}

void runWC(char* filepath,char* tmp_file){
    // wc ... > ...
    int wc_length=8;
    int command_size = strlen(filepath)+ strlen(tmp_file)+ wc_length+1;
    char* command = calloc(command_size, sizeof(char ));
    snprintf(command,command_size,"wc %s > %s",filepath,tmp_file);
    system(command);//obsługa błedów
}
char* readFromFile(char* filepath){
    FILE* file= fopen(filepath,"r");
//    if(file == NULL) {
//        printf("Not able to open: %s.", filepath);
//        return
//    }
    fseek(file, 0, SEEK_END); // seek to end of file
    long file_size = ftell(file); // get current file pointer
    fseek(file, 0, SEEK_SET);
    char* buffer = calloc(file_size+1,sizeof(char));
    fread(buffer,sizeof(char),file_size,file);
    fclose(file);
    return buffer;
}

void LibMemory_addBlock (LibMemory* lib_memory, char* filepath){
    if(lib_memory->size<= lib_memory->curr_size){
        fprintf( stderr, "Not enough memory\n");
        return ;
    }
    char tmp_path[] = "/tmp/wc_XXXXXX";
    int fd = mkstemp(tmp_path);
    if(fd == -1){
        fprintf( stderr, "Failed to create tmp file\n");
        return;

    }
    else{
        runWC(filepath,tmp_path);
        char* wc_output= readFromFile(tmp_path);//obsluga bledów
        lib_memory->memory[lib_memory->curr_size]=wc_output;
        lib_memory->curr_size++;
        remove(tmp_path);



    }





}