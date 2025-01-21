#include <sys/shm.h>
#include <sys/ipc.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>

char filename[] = "/Users/samuelzetumer/Desktop/Research/c_projects/levelup_clang/level0/shared_mem/parallel_proc";
#define SHM_OWNER_R (SHM_R)
#define SHM_OWNER_W (SHM_W)
#define SHM_GROUP_R (SHM_R >> 3)
#define SHM_WORLD_R (SHM_R >> 6)
#define SHM_GROUP_W (SHM_W >> 3)
#define SHM_WORLD_W (SHM_W >> 6)

int main(int argc, char** argv){
    if((argc < 2) || (strlen(argv[1]) < 1)){
        printf("must provide a cli arg: number.\n");
        exit(1);
    }
    char* cli1 = argv[1];
    if((!isdigit(cli1[0]))){
        printf("cli arg 1 must be int.\n");
    }
    //get cli number and turn it into a shm key.
    int signature = atoi(argv[1]);
    key_t shm_key = ftok(filename, signature);

    //do we want to delete the shared memory?
    if((argc >= 3) && (strcmp(argv[2], "d") == 0)){
        int shm_id = shmget(shm_key, sizeof(int) * 1, 0);
        if(shm_id == -1){
            printf("couldn't access shared memory to delete it.\n");
            exit(1);
        }
        if(shmctl(shm_id, IPC_RMID, 0) < 0){
            printf("couldn't delete shared memory.\n");
        }
        printf("successfully deleted memory with key: %d.\n", shm_id);
        return 0;
    }

    //if not delete, then create the memory and do the cycling thing.
    int shm_id = shmget(shm_key, sizeof(int) * 1, IPC_CREAT | IPC_EXCL | SHM_OWNER_R | SHM_OWNER_W);
    if(shm_id == -1){
        printf("failed to get shm_id.");
        exit(1);
    }
    int* shm_int = (int*)shmat(shm_id, NULL, 0);
    if(shm_int == NULL){
        printf("couldn't attach memory address to shm_id: %d.\n", shm_id);
        exit(1);
    }
    *shm_int = 0;
    while(1){
        printf("%d ", *shm_int);
        (*shm_int)++;
        fflush(stdout);
        usleep(100000);
    }
    return 0;
}