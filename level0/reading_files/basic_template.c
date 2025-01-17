#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAXCHARS 1000
char filename[] = "/Users/samuelzetumer/Desktop/Research/c_projects/levelup_clang/level0/reading_files/textfile.txt";
char buffer[MAXCHARS];
FILE* f;

int main(void) {
    f = fopen(filename, "r");
    if(f == NULL){
        printf("can't get file.");
        exit(1);
    }
    while(fgets(buffer, MAXCHARS, f)){
        printf("%s", buffer);
    }
    return 0;
}