#include <stdlib.h>
#include <stdio.h>
#include <sys/shm.h>
//do this after learning about ftok

char filename[] = "/Users/samuelzetumer/Desktop/Research/c_projects/levelup_clang/level0/shared_mem";

int main(int argc, char** argv){
    if(argc < 2){
        printf("you must provide the shared memory key id as a command-line argument.\n");
        exit(1);
    }
    int input_id = atoi(argv[1]);
    key_t key = ftok(filename, input_id);
    printf("the shared memory key with key id %d has value: %d.\n", input_id, key);
    //that requires that you understand shared memory keys.
    int shm_id = shmget(key, sizeof(int)*1, IPC_CREAT);
    if(shm_id < 0){
        printf("shmget failed.\n");
        exit(1);
    }
    printf("The shared memory id that you created is: %d.\n", shm_id);
    printf("Now we are going to try to delete the shared memory segment.\n");
    if(shmctl(shm_id, IPC_RMID, 0) < 0){
        printf("We couldn't uncreate your shared memory. Sorry.\n");
        exit(1);
    }
    printf("Successfully uncreated your shared memory.");

    return 0;
}