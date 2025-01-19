#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/shm.h>
//apparently this will only work for non-Windows, Unix-like systems. Lame.
//ftok creates a key that will allow the system to create some shared memory.

/*
Questions: why does ftok need the name of a path?

*/

char filename[] = "/Users/samuelzetumer/Desktop/Research/c_projects/levelup_clang/level0/shared_mem";

int main(int argc,char** argv) {
    //takes in a decimal.
    if(argc < 2){
        printf("please provide an id for the shared memory key. Should be a whole number (int).");
        exit(1);
    }
    int input_id = atoi(argv[1]);
    key_t key = ftok(filename, 100);
    printf("In this file, input id %d created key %d.\n", input_id, key);

    return 0;
}