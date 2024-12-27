#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../proto/base.h"
#include "samples.h"

int test_get_buffer(){
    buff ptr = get_buffer();
    return 1;
}

int test_get_methods(){
    method* methods = get_methods();
    return 1;
}

int test_get_protos(){
    proto* samples = get_protos();
    printf("printing protos:\n\n");
    for(int i = 0; i < protos_sample_size; i++) {
        proto_printf(samples[i]);
        printf("\n");
    }
    return 1;
}

int test_get_lvi_samples(){
    lvi_samples samples = get_lvi_samples();
    for(int i = 0; i < lvi_sample_size; i++) {
        proto_printf(samples[i].output);
        printf("\n");
    }
    return 1;
}

int test_get_lbsize_samples(){
    lbsize_samples samples = get_lbsize_samples();
    for(int i = 0; i < lbsize_sample_size; i++) {
        proto_printf(samples[i].output);
        printf("\n");
    }
    return 1;
}
int main(void) {
    printf("+------------------------------------+\n");
    int result1 = test_get_buffer();
    printf("+------------------------------------+\n");
    int result2 = test_get_methods();
    printf("+------------------------------------+\n");
    int result3 = test_get_protos();
    printf("+------------------------------------+\n");
    int result4 = test_get_lvi_samples();
    printf("+------------------------------------+\n");
    int result5 = test_get_lbsize_samples();
    printf("+------------------------------------+\n");

    printf("test get_buffer:                     %s\n", result1 ? "PASS" : "FAIL");
    printf("test get_methods:                    %s\n", result2 ? "PASS" : "FAIL");
    printf("test get_protos:                     %s\n", result3 ? "PASS" : "FAIL");
    printf("test_get_lvi_samples                 %s\n", result4 ? "PASS" : "FAIL");
    printf("test_get_lbsize_samples              %s\n", result5 ? "PASS" : "FAIL");

    return 0;
}