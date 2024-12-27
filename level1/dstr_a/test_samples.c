#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../proto/dstr.h"
#include "samples.h"

int test_get_attrs_tobuff_unsplit_samples(){
    attrs_samples samples = get_attrs_tobuff_unsplit_samples();
    for(int i = 0; i < attrs_sample_size; i++) {
        dstr* dstr = samples[i].expected_dstr;
        char* data = dstr_data(dstr);
        printf("dstr: %p", dstr);
        dstr_printf(*dstr, 1);
    }
    return 1;
}

int test_get_attrs_tobuff_split_samples(){
    attrs_samples samples = get_attrs_tobuff_split_samples();
    for(int i = 0; i < attrs_sample_size; i++) {
        dstr* d = samples[i].expected_dstr;
        char* data = dstr_data(d);
        printf("dstr: %p", d);
        dstr_printf(*d, 1);
    }
    return 1;
}

int test_get_attrs_tobuff_samples(){
    printf("getting the attrs_tobuff_samples");
    attrs_samples samples = get_attrs_tobuff_samples();
    for(int i = 0; i < 2*attrs_sample_size; i++) {
        dstr* d = samples[i].expected_dstr;
        char* data = dstr_data(d);
        printf("dstr: %p", d);
        dstr_printf(*d, 1);
    }
    return 1;
}

int test_get_attrs_toheap_unsplit_samples(){
    printf("getting the attrs_toheap_unsplit samples");
    attrs_samples samples = get_attrs_toheap_unsplit_samples();
    for(int i = 0; i < attrs_sample_size; i++) {
        dstr* d = samples[i].expected_dstr;
        char* data = dstr_data(d);
        printf("dstr: %p", d);
        dstr_printf(*d, 1);
    }
    return 1;
}

int test_get_attrs_toheap_split_samples(){
    printf("getting the attrs_toheap_split samples");
    attrs_samples samples = get_attrs_toheap_split_samples();
    for(int i = 0; i < attrs_sample_size; i++) {
        dstr* d = samples[i].expected_dstr;
        char* data = dstr_data(d);
        printf("dstr: %p", d);
        dstr_printf(*d, 1);
    }
    return 1;
}

int test_get_attrs_toheap_samples(){
    printf("getting the attrs_toheap_samples");
    attrs_samples samples = get_attrs_toheap_samples();
    for(int i = 0; i < 2*attrs_sample_size; i++) {
        dstr* d = samples[i].expected_dstr;
        char* data = dstr_data(d);
        printf("dstr: %p", d);
        dstr_printf(*d, 1);
    }
    return 1;
}

int test_get_attrs_tobloc_unsplit_samples(){
    printf("getting the attrs_tobloc_unsplit samples\n");
    attrs_samples samples = get_attrs_tobloc_unsplit_samples();
    for(int i = 0; i < attrs_sample_size; i++) {
        dstr* d = samples[i].expected_dstr;
        printf("dstr: %p\n", d);
    }
    return 1;
}

int test_get_attrs_tobloc_split_samples(){
    printf("getting the attrs_tobloc_split samples\n");
    attrs_samples samples = get_attrs_tobloc_split_samples();
    for(int i = 0; i < attrs_sample_size; i++) {
        dstr* d = samples[i].expected_dstr;
        printf("dstr: %p\n", d);
    }
    return 1;
}

int test_get_attrs_tobloc_samples(){
    printf("getting the attrs_tobloc_samples\n");
    attrs_samples samples = get_attrs_tobloc_samples();
    for(int i = 0; i < 2*attrs_sample_size; i++) {
        dstr* d = samples[i].expected_dstr;
        printf("dstr: %p\n", d);
    }
    return 1;
}

/*
int test_that_outputdstr_not_null(attrs_samples get_samples(), uint32 sample_size) {
    attrs_samples samples = get_samples();
    for(int i = 0; i < sample_size; i++) {
        dstr* d = samples[i].expected_dstr;
        if (d == NULL) {
            printf("dstr was null\n");
            return 0;
        }
    }
    return 1;
}*/

int main(void) {
    printf("+------------------------------------+\n");
    int result0 = test_get_attrs_tobuff_unsplit_samples();
    printf("+------------------------------------+\n");
    int result1 = test_get_attrs_tobuff_split_samples();
    printf("+------------------------------------+\n");
    int result2 = test_get_attrs_tobuff_samples();
    printf("+------------------------------------+\n");
    int result3 = test_get_attrs_toheap_unsplit_samples();
    printf("+------------------------------------+\n");
    int result4 = test_get_attrs_toheap_split_samples();
    printf("+------------------------------------+\n");
    int result5 = test_get_attrs_toheap_samples();
    printf("+------------------------------------+\n");
    int result6 = test_get_attrs_tobloc_unsplit_samples();
    printf("+------------------------------------+\n");
    int result7 = test_get_attrs_tobloc_split_samples();
    printf("+------------------------------------+\n");
    int result8 = test_get_attrs_tobloc_samples();
    printf("+------------------------------------+\n");

    printf("test_get_attrs_tobuff_unsplit_samples          %s\n", result0 ? "PASS" : "FAIL");
    printf("test_get_attrs_tobuff_split_samples            %s\n", result1 ? "PASS" : "FAIL");
    printf("test_get_attrs_tobuff_samples:                 %s\n", result2 ? "PASS" : "FAIL");
    printf("test_get_attrs_toheap_unsplit_samples          %s\n", result3 ? "PASS" : "FAIL");
    printf("test_get_attrs_toheap_split_samples:           %s\n", result4 ? "PASS" : "FAIL");
    printf("test_get_attrs_toheap_samples:                 %s\n", result5 ? "PASS" : "FAIL");
    printf("test_get_attrs_tobloc_unsplit_samples:         %s\n", result6 ? "PASS" : "FAIL");
    printf("test_get_attrs_tobloc_split_samples:           %s\n", result7 ? "PASS" : "FAIL");
    printf("test_get_attrs_tobloc_samples:                 %s\n", result8 ? "PASS" : "FAIL");

    return 0;
}