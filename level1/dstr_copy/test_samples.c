#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../proto/dstr.h"
#include "samples.h"

int test_get_dstr_inputs() {
    dstr* dstrs = get_dstr_inputs();
    for(int i = 0; i < copy_sample_size; i++) {
        dstr* d = dstrs + i;
        char* data = dstr_data(d);
        printf("dstr: %p", d);
        dstr_printf(*d, 1);
    }
    return 1;
}

int test_get_samples(copy_samples get_samples(), uint32 sample_size) {
    copy_samples samples = get_samples();
    for(int i = 0; i < sample_size; i++) {
        if ((samples[i].input == NULL) || (samples[i].output == NULL)) {
            printf("sample %d is null\n", i);
            printf("input: %p; output: %p\n", samples[i].input, samples[i].output);
            return 0;
        }
    }
    printf("all pointers are non-null.\n");
    return 1;
}

int main() {
    int result0 = test_get_dstr_inputs();
    printf("+------------------------------------+\n");
    int result1 = test_get_samples(get_copy_tobuff_split_samples, copy_sample_size);
    printf("+------------------------------------+\n");
    int result2 = test_get_samples(get_copy_tobuff_unsplit_samples, copy_sample_size);
    printf("+------------------------------------+\n");
    int result3 = test_get_samples(get_copy_tobuff_samples, 2*copy_sample_size);
    printf("+------------------------------------+\n");
    int result4 = test_get_samples(get_copy_toheap_split_samples, copy_sample_size);
    printf("+------------------------------------+\n");
    int result5 = test_get_samples(get_copy_toheap_unsplit_samples, copy_sample_size);
    printf("+------------------------------------+\n");
    int result6 = test_get_samples(get_copy_toheap_samples, 2*copy_sample_size);
    printf("+------------------------------------+\n");
    int result7 = test_get_samples(get_copy_tobloc_split_samples, copy_sample_size);
    printf("+------------------------------------+\n");
    int result8 = test_get_samples(get_copy_tobloc_unsplit_samples, copy_sample_size);
    printf("+------------------------------------+\n");
    int result9 = test_get_samples(get_copy_tobloc_samples, 2*copy_sample_size);
    printf("+------------------------------------+\n");

    printf("Can you get dstr inputs to be copied:   %s\n", result0 ? "PASS" : "FAIL");
    printf("Can you get copy tobuff split samples:  %s\n", result1 ? "PASS" : "FAIL");
    printf("Can you get copy tobuff unsplit samples:%s\n", result2 ? "PASS" : "FAIL");
    printf("Can you get copy tobuff samples:        %s\n", result3 ? "PASS" : "FAIL");
    printf("Can you get copy toheap split samples:  %s\n", result4 ? "PASS" : "FAIL");
    printf("Can you get copy toheap unsplit samples:%s\n", result5 ? "PASS" : "FAIL");
    printf("Can you get copy toheap samples:        %s\n", result6 ? "PASS" : "FAIL");
    printf("Can you get copy tobloc split samples:  %s\n", result7 ? "PASS" : "FAIL");
    printf("Can you get copy tobloc unsplit samples:%s\n", result8 ? "PASS" : "FAIL");
    printf("Can you get copy tobloc samples:        %s\n", result9 ? "PASS" : "FAIL");

    return 0;
}