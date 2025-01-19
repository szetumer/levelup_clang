#include <stdlib.h>
#include <stdio.h>
#include <time.h>
// going over the clock operation and the difftime operation. Former makes an unsigned long int and latter
//makes a double. difftime doesn't seem to be doing much other than subtracting the two.
time_t start_t, emptyloop_t;

int main(){
    printf("clocks per second: %lu.\n", CLOCKS_PER_SEC);
    start_t = clock();
    for(int i = 0; i < 100000; i++){}
    emptyloop_t = clock();
    time_t callingclock_t = clock();
    printf("100k empty loop cycles: %lu.\n", emptyloop_t - start_t);
    unsigned long int emptyloopcycles = emptyloop_t - start_t;
    printf("calling clock itself: %lu.\n", callingclock_t - emptyloop_t);
    int k = 0;
    time_t pre_iter = clock();
    for(int j = 0; j < 100000; j++){
        k++;
    }
    time_t post_iter = clock();
    unsigned long int incrementloopcycles = post_iter - pre_iter;
    printf("100k increment operations: %lu.\n", post_iter - pre_iter);
    printf("does using difftime change things?: %lf. (No it is the same as subtraction).\n", difftime(post_iter, pre_iter));
    printf("does it take absolute value?: %lf. (No it takes negatives).\n", difftime(pre_iter, post_iter));
    float proportion = ((float)(incrementloopcycles) - (float)(emptyloopcycles))/((float)emptyloopcycles);
    printf("proportional diff btwn empty loop and increment loop: %f.\n", proportion);
    printf("post-increment sum, for completeness sake: %d.\n", k);

    return 0;
}