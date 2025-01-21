#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/shm.h>
#include <assert.h>
//please notice that you cannot successfully create 
//a ipc shared thing twice in a row when you use the IPC_EXCL
//flag.

char filename[] = "/Users/samuelzetumer/Desktop/Research/c_projects/levelup_clang/level0/shared_mem";
int main(int argc, char** argv){
    if(argc < 3){
        printf("please input key id and create or delete char.c = create memory. d = destroy memory.");
        exit(1);
    }
    int input_key_id = atoi(argv[1]);
    if(strlen(argv[2]) != 1){
        printf("please provide a 'c' or a 'd' for create or delete the memory. Thank you.\n");
        exit(1);
    }
    if((strcmp(argv[2], "c") != 0) && (strcmp(argv[2], "d") != 0)){
        printf("please make sure the second parameter is either a 'c' or a 'd'.\n");
        exit(1);
    }
    key_t key = ftok(filename, input_key_id);
    if(strcmp(argv[2], "c") == 0){
        int shm_id = shmget(key, sizeof(int)*1, IPC_CREAT | IPC_EXCL);
        if(shm_id < 0){
            printf("Couldn't create this memory for you. Likely already exists. Sorry.");
        }
        return 0;
    }
    if(strcmp(argv[2], "d") == 0){
        int shm_id = shmget(key, sizeof(int)*1, 0); //notice that we don't need to say IPC_CREAT
        if(shmctl(shm_id, IPC_RMID, 0) < 0){
            printf("We couldn't uncreate your shared memory. Maybe you already deleted it? Sorry.\n");
            exit(1);
        }
        return 0;
    }
}