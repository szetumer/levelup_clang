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
    if(argc != 3){
        printf("please provide shm key and bump value.\n");
        exit(1);
    }
    int signature = atoi(argv[1]);
    int bump_val = atoi(argv[2]);
    int pre_val, post_val;
    key_t shm_key = ftok(filename, signature);
    if(shm_key < 0){printf("couldn't get shm_key, sorry.\n");}
    int shm_id = shmget(shm_key, sizeof(int), 0);
    if(shm_id < 0){printf("couldn't get shm_id, sorry.\n");}
    int* shm_intaddrs = (int*)shmat(shm_id, NULL, 0);
    pre_val = *shm_intaddrs;
    *shm_intaddrs+= bump_val;
    post_val = *shm_intaddrs;
    shmdt((void*)shm_intaddrs);
    printf("pre-change value: %d; change value: %d; post-change value: %d", pre_val, bump_val, post_val);
    return 0;
}