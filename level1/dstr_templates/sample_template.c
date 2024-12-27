#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../proto/dstr.h"
#include "../../proto/base.h"
#include "samples.h"

uint32 cat2_sample_size = 6;

dstr* get_dstr_inputs() {
    void* voidptr = malloc(sizeof(dstr) * (cat2_sample_size));
    if (voidptr == NULL) {
        printf("errormessage");
        exit(1);
    }
    dstr* dstrs = (dstr*)voidptr;
    dstr_attrs_toheap_split(NULL, dstrs + 0);
    dstr_attrs_toheap_split("", dstrs + 1);
    dstr_attrs_toheap_split("alpha", dstrs + 2);
    dstr_attrs_toheap_split("new line:\n", dstrs + 3);
    dstr_attrs_toheap_split("012345678911234567892", dstrs + 4);
    dstr_attrs_toheap_split("0123456789112345678921234567893", dstrs + 5);
    return dstrs;
}

void free_dstrs(dstr* dstrs) {
    for(int i = 0; i < cat2_sample_size; i++) {
        dstr_free(dstrs + i);
    }
    free(dstrs);
}

dstr* get_headbuff() {
    //an array of sample_size dstrs.
    void* voidptr = malloc(sizeof(dstr) * (cat2_sample_size) * (cat2_sample_size));
    if (voidptr == NULL) {
        printf("failed to allocate memory for dstrs");
        exit(1);
    }
    dstr* dstrs = (dstr*)voidptr;
    return dstrs;
}

void* get_tailbuff() {
    //an array of generic memory to copy the back end of our dstrs to.
    void* voidptr = malloc(sizeof(char) * (4112));
    if (voidptr == NULL) {
        printf("failed to allocate memory for tailbuff");
        exit(1);
    }
    return voidptr;
}

cat2_samples get_samples_array() {
    void* voidptr = malloc(sizeof(cat2_io) * (cat2_sample_size) * (cat2_sample_size));
    if (voidptr == NULL) {
        printf("failed to allocate memory for copy samples");
        exit(1);
    }
    return (cat2_samples)voidptr;
}

cat2_samples get_cat2_tobuff_split_samples() {
    printf("allocated resources for copy tobuff split samples\n");
    printf("NOT IMPLEMENTED\n");
    return NULL;
}

cat2_samples get_cat2_tobuff_unsplit_samples() {
    printf("allocated resources for copy tobuff unsplit samples\n");
    printf("NOT IMPLEMENTED\n");
    return NULL;
}

cat2_samples get_cat2_tobuff_samples() {
    printf("allocated resources for copy tobuff samples\n");
    printf("NOT IMPLEMENTED\n");
    return NULL;
}

cat2_samples get_cat2_toheap_split_samples() {
    printf("allocated resources for copy toheap split samples\n");
    printf("NOT IMPLEMENTED\n");
    return NULL;
}

cat2_samples get_cat2_toheap_unsplit_samples() {
    printf("allocated resources for copy toheap unsplit samples\n");
    printf("NOT IMPLEMENTED\n");
    return NULL;
}

cat2_samples get_cat2_toheap_samples(){
    printf("allocated resources for copy toheap samples\n");
    printf("NOT IMPLEMENTED\n");
    return NULL;
}

cat2_samples get_cat2_tobloc_split_samples(){
    printf("allocated resources for copy tobloc split samples\n");
    printf("NOT IMPLEMENTED\n");
    return NULL;
}

cat2_samples get_cat2_tobloc_unsplit_samples(){
    printf("allocated resources for copy tobloc unsplit samples\n");
    printf("NOT IMPLEMENTED\n");
    return NULL;
}

cat2_samples get_cat2_tobloc_samples(){
    printf("allocated resources for copy tobloc samples\n");
    printf("NOT IMPLEMENTED\n");
    return NULL;
}