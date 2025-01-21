#include <stdlib.h>
#include <stdio.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <string.h>
#include <assert.h>
//Notice now that you have flags that accompany your shmget command.
//These are necessary if you want to actually read or write to the system.
//Play around with the flags to figure out what you need to do to be able to
//Read and write by whichever process.

char filename[] = "/Users/samuelzetumer/Desktop/Research/c_projects/levelup_clang/level0/shared_mem";
#define SHM_OWNER_R (SHM_R)
#define SHM_OWNER_W (SHM_W)
#define SHM_GROUP_R (SHM_R >> 3)
#define SHM_WORLD_R (SHM_R >> 6)
#define SHM_GROUP_W (SHM_W >> 3)
#define SHM_WORLD_W (SHM_W >> 6)

int main(int argc, char** argv){
    if(
        (argc < 3) || (strlen(argv[2]) != 1) || 
        ((strcmp(argv[2], "c") != 0) && (strcmp(argv[2], "d") != 0) && (strcmp(argv[2], "w") != 0) && (strcmp(argv[2], "r") != 0))
    ){
        printf("number and then string = 'c', 'd', 'w', 'r'.\n");
        exit(1);
    }
    int input_key_id = atoi(argv[1]);
    key_t key = ftok(filename, input_key_id);
    if(strcmp(argv[2], "c") == 0){
        int shm_id = shmget(key, sizeof(int)*1, IPC_CREAT | IPC_EXCL | SHM_OWNER_R | SHM_OWNER_W | SHM_WORLD_R | SHM_WORLD_W);
        assert(shm_id != -1);
        return 0;
    }
    if(strcmp(argv[2], "d") == 0){
        int shm_id = shmget(key, sizeof(int)*1, IPC_CREAT);
        if(shmctl(shm_id, IPC_RMID, 0) < 0){
            printf("We couldn't uncreate your shared memory. Sorry.\n");
            exit(1);
        }
        return 0;
    }
    if(strcmp(argv[2], "w") == 0){
        int shm_id = shmget(key, sizeof(int)*1, IPC_CREAT);
        int* int_addrs = (int*)shmat(shm_id, NULL, 0);
        assert((long)int_addrs != -1);
        printf("your shared int has been mapped to address: %p.\n", int_addrs);
        *int_addrs = 13;
        return 0;
    }
    if(strcmp(argv[2], "r") == 0){
        int shm_id = shmget(key, sizeof(int)*1, IPC_CREAT);
        int* int_addrs = (int*)shmat(shm_id, NULL, 0);
        assert((long)int_addrs != -1);
        printf("Mapped address is: %p. Value at that address is: %d.\n", int_addrs, *int_addrs);
        return 0;
    }
    return 0;
}