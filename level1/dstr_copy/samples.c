#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../proto/dstr.h"
#include "../../proto/base.h"
#include "samples.h"

uint32 copy_sample_size = 6;

dstr* get_dstr_inputs() {
    void* voidptr = malloc(sizeof(dstr) * (copy_sample_size));
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
    for(int i = 0; i < copy_sample_size; i++) {
        dstr_free(dstrs + i);
    }
    free(dstrs);
}

dstr* get_headbuff() {
    //an array of sample_size dstrs.
    void* voidptr = malloc(sizeof(dstr) * (copy_sample_size));
    if (voidptr == NULL) {
        printf("failed to allocate memory for dstrs");
        exit(1);
    }
    dstr* dstrs = (dstr*)voidptr;
    return dstrs;
}

void* get_tailbuff() {
    //an array of generic memory to copy the back end of our dstrs to.
    void* voidptr = malloc(sizeof(char) * (2056));
    if (voidptr == NULL) {
        printf("failed to allocate memory for tailbuff");
        exit(1);
    }
    return voidptr;
}

copy_samples get_samples_array() {
    void* voidptr = malloc(sizeof(copy_io) * (copy_sample_size));
    if (voidptr == NULL) {
        printf("failed to allocate memory for copy samples");
        exit(1);
    }
    return (copy_samples)voidptr;
}

copy_samples get_2samples_array() {
    void* voidptr = malloc(sizeof(copy_io) * (2) * (copy_sample_size));
    if (voidptr == NULL) {
        printf("failed to allocate memory for copy samples");
        exit(1);
    }
    return (copy_samples)voidptr;
}

copy_samples get_copy_tobuff_split_samples() {
    dstr* dstrs = get_dstr_inputs();
    dstr* headbuff = get_headbuff();
    void* tailbuff = get_tailbuff();
    copy_samples samples = get_samples_array();
    printf("allocated resources for copy tobuff split samples\n");
    for(int i = 0; i < copy_sample_size; i++) {
        samples[i].input = dstrs + i;
        samples[i].output = headbuff + i;
        tailbuff = dstr_copy_tobuff_split(dstrs[i], headbuff + i, tailbuff);
    }
    return samples;
}

copy_samples get_copy_tobuff_unsplit_samples() {
    dstr* dstrs = get_dstr_inputs();
    dstr* headbuff = get_headbuff();
    void* tailbuff = get_tailbuff();
    copy_samples samples = get_samples_array();
    printf("allocated resources for copy tobuff unsplit samples\n");
    for(int i = 0; i < copy_sample_size; i++) {
        samples[i].input = dstrs + i;
        samples[i].output = (dstr*)tailbuff;
        tailbuff = dstr_copy_tobuff_unsplit(dstrs[i], tailbuff);
    }
    return samples;
}

copy_samples get_copy_tobuff_samples() {
    dstr* dstrs = get_dstr_inputs();
    dstr* headbuff1 = get_headbuff();
    void* tailbuff1 = get_tailbuff();
    void* tailbuff2 = get_tailbuff();
    copy_samples samples = get_2samples_array();
    printf("allocated resources for copy tobuff samples\n");
    for(int i = 0; i < copy_sample_size; i++) {
        //first is split. Second is unsplit.
        samples[i].input = dstrs + i;       samples[copy_sample_size + i].input = dstrs + i;
        samples[i].output = headbuff1 + i;  samples[copy_sample_size + i].output = (dstr*)tailbuff2;
        tailbuff1 = dstr_copy_tobuff(dstrs[i], headbuff1 + i, tailbuff1);
        tailbuff2 = dstr_copy_tobuff(dstrs[i], NULL, tailbuff2);
    }
    return samples;
}

copy_samples get_copy_toheap_split_samples() {
    dstr* dstrs = get_dstr_inputs();
    dstr* headbuff = get_headbuff();
    void* tailbuff = get_tailbuff();
    copy_samples samples = get_samples_array();
    printf("allocated resources for copy toheap split samples\n");
    for(int i = 0; i < copy_sample_size; i++) {
        samples[i].input = dstrs + i;
        samples[i].output = headbuff + i;
        dstr_copy_toheap_split(dstrs[i], headbuff + i);
    }
    return samples;
}

copy_samples get_copy_toheap_unsplit_samples() {
    dstr* dstrs = get_dstr_inputs();
    dstr* headbuff = get_headbuff();
    void* tailbuff = get_tailbuff();
    void* newtail;
    copy_samples samples = get_samples_array();
    printf("allocated resources for copy toheap unsplit samples\n");
    for(int i = 0; i < copy_sample_size; i++) {
        samples[i].input = dstrs + i;
        newtail = dstr_copy_toheap_unsplit(dstrs[i], tailbuff);
        samples[i].output = (*(dstr**)tailbuff); //the tail is an array of pointers to dstrs on heaps.
        tailbuff = newtail;
    }
    return samples;
}

copy_samples get_copy_toheap_samples(){
    dstr* dstrs = get_dstr_inputs();
    dstr* headbuff1 = get_headbuff();
    void* tailbuff1 = get_tailbuff();
    void* tailbuff2 = get_tailbuff();
    void* newtail;
    copy_samples samples = get_2samples_array();
    printf("allocated resources for copy toheap samples\n");
    for(int i = 0; i < copy_sample_size; i++) {
        //first is split. Second is unsplit.
        newtail = dstr_copy_toheap(dstrs[i], NULL, tailbuff2);
        samples[i].input = dstrs + i;       samples[copy_sample_size + i].input = dstrs + i;
        samples[i].output = headbuff1 + i;  samples[copy_sample_size + i].output = *(dstr**)tailbuff2;
        tailbuff1 = dstr_copy_toheap(dstrs[i], headbuff1 + i, tailbuff1);
        tailbuff2 = newtail;
    }
    return samples;
}

copy_samples get_copy_tobloc_split_samples(){
    dstr* dstrs = get_dstr_inputs();
    dstr* headbuff = get_headbuff();
    void* tailbuff = get_tailbuff();
    copy_samples samples = get_samples_array();
    printf("allocated resources for copy tobloc split samples\n");
    for(int i = 0; i < copy_sample_size; i++) {
        samples[i].input = dstrs + i;
        samples[i].output = headbuff + i;
        tailbuff = dstr_copy_tobloc_split(dstrs[i], headbuff + i, tailbuff, 64);
    }
    return samples;
}

copy_samples get_copy_tobloc_unsplit_samples(){
    dstr* dstrs = get_dstr_inputs();
    dstr* headbuff = get_headbuff();
    void* tailbuff = get_tailbuff();
    copy_samples samples = get_samples_array();
    printf("allocated resources for copy tobloc unsplit samples\n");
    for(int i = 0; i < copy_sample_size; i++) {
        samples[i].input = dstrs + i;
        samples[i].output = (dstr*)tailbuff;
        tailbuff = dstr_copy_tobloc_unsplit(dstrs[i], tailbuff, 64);
    }
    return samples;
}

copy_samples get_copy_tobloc_samples(){
    dstr* dstrs = get_dstr_inputs();
    dstr* headbuff1 = get_headbuff();
    void* tailbuff1 = get_tailbuff();
    void* tailbuff2 = get_tailbuff();
    copy_samples samples = get_2samples_array();
    printf("allocated resources for copy tobloc samples\n");
    for(int i = 0; i < copy_sample_size; i++) {
        //first is split. Second is unsplit.
        samples[i].input = dstrs + i;       samples[copy_sample_size + i].input = dstrs + i;
        samples[i].output = headbuff1 + i;  samples[copy_sample_size + i].output = (dstr*)tailbuff2;
        tailbuff1 = dstr_copy_tobloc(dstrs[i], headbuff1 + i, tailbuff1, 64);
        tailbuff2 = dstr_copy_tobloc(dstrs[i], NULL, tailbuff2, 64);
    }
    return samples;
}