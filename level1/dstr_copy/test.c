#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../../proto/dstr.h"
#include "../../proto/base.h"
#include "samples.h"

int test_compiles_samples(){
    return 1; 
}

int test_copy_is_doesnt_change_data(copy_samples get_samples(), uint32 sample_size, uint32 breakpoint) {
    copy_samples samples = get_samples();
    for(int i = 0; i < sample_size; i++) {
        for(int j = 0; j < sample_size; j++) {
            printf("comparing %d to %d\n", i, j);
            dstr_printf(*samples[i].output, 0);
            printf("   ");
            dstr_printf(*samples[j].input, 1);
            printf("%d\n", ((int)j - (int)i));
            if(((int)j - (int)i) % (int)breakpoint == 0) {
                if(dstr_eq(*samples[i].output, *samples[j].input) == 0) {
                    printf("copy does not match input, but it should\n");
                    return 0;
                } else {
                    continue;
                }
            } else if (i != j) {
                if(dstr_eq(*samples[i].output, *samples[j].input) == 1) {
                    printf("copy matches input, but it should not\n");
                    return 0;
                } else {
                    continue;
                }
            } else {
                printf("error\n");
                return 0;
            }
        }
    }
    return 1;
}


int main() {
    int result0 = test_compiles_samples();
    printf("+------------------------------------+\n");
    int result1 = test_copy_is_doesnt_change_data(get_copy_tobuff_split_samples, copy_sample_size, copy_sample_size);
    printf("+------------------------------------+\n");
    int result2 = test_copy_is_doesnt_change_data(get_copy_tobuff_unsplit_samples, copy_sample_size, copy_sample_size);
    printf("+------------------------------------+\n");
    int result3 = test_copy_is_doesnt_change_data(get_copy_tobuff_samples, 2*copy_sample_size, copy_sample_size);
    printf("+------------------------------------+\n");
    int result4 = test_copy_is_doesnt_change_data(get_copy_toheap_split_samples, copy_sample_size, copy_sample_size);
    printf("+------------------------------------+\n");
    int result5 = test_copy_is_doesnt_change_data(get_copy_toheap_unsplit_samples, copy_sample_size, copy_sample_size);
    printf("+------------------------------------+\n");
    int result6 = test_copy_is_doesnt_change_data(get_copy_toheap_samples, 2*copy_sample_size, copy_sample_size);
    printf("+------------------------------------+\n");
    int result7 = test_copy_is_doesnt_change_data(get_copy_tobloc_split_samples, copy_sample_size, copy_sample_size);
    printf("+------------------------------------+\n");
    int result8 = test_copy_is_doesnt_change_data(get_copy_tobloc_unsplit_samples, copy_sample_size, copy_sample_size);
    printf("+------------------------------------+\n");
    int result9 = test_copy_is_doesnt_change_data(get_copy_tobloc_samples, 2*copy_sample_size, copy_sample_size);
    printf("+------------------------------------+\n");

    printf("Can you even compile this?:         %s\n", result0 ? "PASS" : "FAIL");
    printf("test copy_tobuff_split_samples:     %s\n", result1 ? "PASS" : "FAIL");
    printf("test copy_tobuff_unsplit_samples:   %s\n", result2 ? "PASS" : "FAIL");
    printf("test copy_tobuff_samples:           %s\n", result3 ? "PASS" : "FAIL");
    printf("test copy_toheap_split_samples:     %s\n", result4 ? "PASS" : "FAIL");
    printf("test copy_toheap_unsplit_samples:   %s\n", result5 ? "PASS" : "FAIL");
    printf("test copy_toheap_samples:           %s\n", result6 ? "PASS" : "FAIL");
    printf("test copy_tobloc_split_samples:     %s\n", result7 ? "PASS" : "FAIL");
    printf("test copy_tobloc_unsplit_samples:   %s\n", result8 ? "PASS" : "FAIL");
    printf("test copy_tobloc_samples:           %s\n", result9 ? "PASS" : "FAIL");
    return 0;
}