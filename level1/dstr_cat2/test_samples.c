#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../proto/dstr.h"
#include "samples.h"

int test_get_dstr_inputs() {
    dstr* dstrs = get_dstr_inputs();
    for(int i = 0; i < cat2_sample_size; i++) {
        dstr* d = dstrs + i;
        char* data = dstr_data(d);
        printf("dstr: %p", d);
        dstr_printf(*d, 1);
    }
    return 1;
}

int test_get_samples(cat2_samples get_samples(), uint32 sample_size) {
    cat2_samples samples = get_samples();
    for(int i = 0; i < sample_size; i++) {
        if ((samples[i].input1 == NULL) || (samples[i].output == NULL) || (samples[i].input2 == NULL)) {
            printf("sample %d is null\n", i);
            printf("input1: %p; input2: %p; output: %p\n", samples[i].input1, samples[i].input2, samples[i].output);
            return 0;
        }
    }
    printf("all pointers are non-null.\n");
    return 1;
}

int main() {
    int result0 = test_get_dstr_inputs();
    printf("+------------------------------------+\n");
    int result1 = test_get_samples(get_cat2_tobuff_split_samples, cat2_sample_size);
    printf("+------------------------------------+\n");
    int result2 = test_get_samples(get_cat2_tobuff_unsplit_samples, cat2_sample_size);
    printf("+------------------------------------+\n");
    int result3 = test_get_samples(get_cat2_tobuff_samples, 2*cat2_sample_size);
    printf("+------------------------------------+\n");
    /*int result4 = test_get_samples(get_cat2_toheap_split_samples, cat2_sample_size);
    printf("+------------------------------------+\n");
    int result5 = test_get_samples(get_cat2_toheap_unsplit_samples, cat2_sample_size);
    printf("+------------------------------------+\n");
    int result6 = test_get_samples(get_cat2_toheap_samples, 2*cat2_sample_size);
    printf("+------------------------------------+\n");
    int result7 = test_get_samples(get_cat2_tobloc_split_samples, cat2_sample_size);
    printf("+------------------------------------+\n");
    int result8 = test_get_samples(get_cat2_tobloc_unsplit_samples, cat2_sample_size);
    printf("+------------------------------------+\n");
    int result9 = test_get_samples(get_cat2_tobloc_samples, 2*cat2_sample_size);*/
    printf("+------------------------------------+\n");

    printf("Can you get dstr inputs to be catted:   %s\n", result0 ? "PASS" : "FAIL");
    printf("Can you get cat2 tobuff split samples:  %s\n", result1 ? "PASS" : "FAIL");
    printf("Can you get cat2 tobuff unsplit samples:%s\n", result2 ? "PASS" : "FAIL");
    printf("Can you get cat2 tobuff samples:        %s\n", result3 ? "PASS" : "FAIL");
    /*printf("Can you get cat2 toheap split samples:  %s\n", result4 ? "PASS" : "FAIL");
    printf("Can you get cat2 toheap unsplit samples:%s\n", result5 ? "PASS" : "FAIL");
    printf("Can you get cat2 toheap samples:        %s\n", result6 ? "PASS" : "FAIL");
    printf("Can you get cat2 tobloc split samples:  %s\n", result7 ? "PASS" : "FAIL");
    printf("Can you get cat2 tobloc unsplit samples:%s\n", result8 ? "PASS" : "FAIL");
    printf("Can you get cat2 tobloc samples:        %s\n", result9 ? "PASS" : "FAIL");*/

    return 0;
}