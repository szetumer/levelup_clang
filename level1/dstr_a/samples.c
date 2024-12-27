#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../proto/dstr.h"
#include "../../proto/base.h"
#include "samples.h"

int attrs_sample_size = 6;
char** get_charstar_inputs() {
    void* voidptr = malloc(sizeof(char*) * (attrs_sample_size));
    if (voidptr == NULL) {
        printf("errormessage");
        exit(1);
    }
    char** inputs = (char**)voidptr;
    printf("got to first copy instance\n");
    inputs[0] = strdup((char []){""});
    printf("copied first string\n");
    inputs[1] = (char*)NULL;
    inputs[2] = strdup("alpha");
    inputs[3] = strdup("new line:\n");
    inputs[4] = strdup("012345678911234567892");
    inputs[5] = strdup("0123456789112345678921234567893");

    printf("got inputs\n");
    return inputs;
}

uint32* get_len_outputs() {
    void* voidptr = malloc(sizeof(uint32) * (attrs_sample_size));
    if (voidptr == NULL) {
        printf("errormessage");
        exit(1);
    }
    uint32* ptr = (uint32*)voidptr;
    ptr[0] = 0;
    ptr[1] = 0;
    ptr[2] = 5;
    ptr[3] = 10;
    ptr[4] = 21;
    ptr[5] = 31;
    return ptr;
}

void* get_tailbuff() {
    void* voidptr = malloc(sizeof(char) * (2056));
    if (voidptr == NULL) {
        printf("errormessage");
        exit(1);
    }
    void* ptr = (void*)voidptr;
    return ptr;
}

void free_inputs(char** inputs) {
    for(int i = 0; i < attrs_sample_size; i++) {
        free(inputs[i]);
    }
    free(inputs);
    return;
}

attrs_samples get_attrs_tobuff_unsplit_samples(){
    char** inputs = get_charstar_inputs();
    dstr** dstrs = (dstr**)malloc(sizeof(dstr*) * attrs_sample_size);
    void* void_ptr = get_tailbuff();
    attrs_samples samples = (attrs_samples)malloc(sizeof(attrs_io) * attrs_sample_size);
    for(int i = 0; i < attrs_sample_size; i++) {
        printf("%d; ", i);
        dstrs[i] = (dstr*)void_ptr;
        void_ptr = dstr_attrs_tobuff_unsplit(inputs[i], void_ptr); // assign the dstrs.
    }
    samples[0] = (attrs_io){.charstar_input = inputs[0],
    .expected_dstr = dstrs[0], .expected_data = inputs[0], .expected_len = 0};
    samples[1] = (attrs_io){.charstar_input = inputs[1],
    .expected_dstr = dstrs[1], .expected_data = NULL, .expected_len = 0};
    samples[2] = (attrs_io){.charstar_input = inputs[2],
    .expected_dstr = dstrs[2], .expected_data = inputs[2], .expected_len = 5};
    samples[3] = (attrs_io){.charstar_input = inputs[3],
    .expected_dstr = dstrs[3], .expected_data = inputs[3], .expected_len = 10};
    samples[4] = (attrs_io){.charstar_input = inputs[4],
    .expected_dstr = dstrs[4], .expected_data = inputs[4], .expected_len = 21};
    samples[5] = (attrs_io){.charstar_input = inputs[5],
    .expected_dstr = dstrs[5], .expected_data = inputs[5], .expected_len = 31};
    return samples;
}

attrs_samples get_attrs_tobuff_split_samples(){
    printf("getting the split samples\n");
    char** inputs = get_charstar_inputs();
    dstr* dstrs = (dstr*)malloc(sizeof(dstr) * attrs_sample_size);
    void* void_ptr = get_tailbuff();
    attrs_samples samples = (attrs_samples)malloc(sizeof(attrs_io) * attrs_sample_size);
    for(int i = 0; i < attrs_sample_size; i++) {
        printf("%d; ", i);
        void_ptr = dstr_attrs_tobuff_split(inputs[i], dstrs + i, void_ptr);
    }
    //notice that ptr is just this latent, hidden object that we don't really have to worry about.
    samples[0] = (attrs_io){.charstar_input = inputs[0],
    .expected_dstr = dstrs + 0, .expected_data = inputs[0], .expected_len = 0};
    samples[1] = (attrs_io){.charstar_input = inputs[1],
    .expected_dstr = dstrs + 1, .expected_data = NULL, .expected_len = 0};
    samples[2] = (attrs_io){.charstar_input = inputs[2],
    .expected_dstr = dstrs + 2, .expected_data = inputs[2], .expected_len = 5};
    samples[3] = (attrs_io){.charstar_input = inputs[3],
    .expected_dstr = dstrs + 3, .expected_data = inputs[3], .expected_len = 10};
    samples[4] = (attrs_io){.charstar_input = inputs[4],
    .expected_dstr = dstrs + 4, .expected_data = inputs[4], .expected_len = 21};
    samples[5] = (attrs_io){.charstar_input = inputs[5],
    .expected_dstr = dstrs + 5, .expected_data = inputs[5], .expected_len = 31};
    return samples;
}

attrs_samples get_attrs_tobuff_samples(){
    //you can do this process any way that you want to do it.
    //you can do things linked.
    printf("getting the split and unsplit samples\n");
    char** inputs = get_charstar_inputs();
    dstr* dstrs1 = (dstr*)malloc(sizeof(dstr) * 2 * attrs_sample_size);
    dstr** dstrs2 = (dstr**)malloc(sizeof(dstr*) * 2 * attrs_sample_size);
    void* void_ptr = get_tailbuff();
    char* charptr = (char*)get_tailbuff();
    dstr* dstrptr = (dstr*)get_tailbuff();
    printf("got all the buffers.");
    attrs_samples samples = (attrs_samples)malloc(sizeof(attrs_io) * 2 * attrs_sample_size);
    for(int i = 0; i < attrs_sample_size; i++) {
        //first is the split version.
        printf("%d; ", i);
        void_ptr = dstr_attrs_tobuff(inputs[i], dstrs1 + i, void_ptr);
    }
    void* next_dstrs;
    for(int i = 0; i < attrs_sample_size; i++) {
        //second is the unsplit version.
        printf("%d; ", i + attrs_sample_size);
        dstrs2[i] = (dstr*)void_ptr;
        void_ptr = dstr_attrs_tobuff(inputs[i], NULL, void_ptr);
    }
    samples[0] = (attrs_io){.charstar_input = inputs[0],
    .expected_dstr = dstrs1 + 0, .expected_data = inputs[0], .expected_len = 0};
    samples[1] = (attrs_io){.charstar_input = inputs[1],
    .expected_dstr = dstrs1 + 1, .expected_data = NULL, .expected_len = 0};
    samples[2] = (attrs_io){.charstar_input = inputs[2],
    .expected_dstr = dstrs1 + 2, .expected_data = inputs[2], .expected_len = 5};
    samples[3] = (attrs_io){.charstar_input = inputs[3],
    .expected_dstr = dstrs1 + 3, .expected_data = inputs[3], .expected_len = 10};
    samples[4] = (attrs_io){.charstar_input = inputs[4],
    .expected_dstr = dstrs1 + 4, .expected_data = inputs[4], .expected_len = 21};
    samples[5] = (attrs_io){.charstar_input = inputs[5],
    .expected_dstr = dstrs1 + 5, .expected_data = inputs[5], .expected_len = 31};
    samples[6] = (attrs_io){.charstar_input = inputs[0],
    .expected_dstr = dstrs2[0], .expected_data = inputs[0], .expected_len = 0};
    samples[7] = (attrs_io){.charstar_input = inputs[1],
    .expected_dstr = dstrs2[1], .expected_data = NULL, .expected_len = 0};
    samples[8] = (attrs_io){.charstar_input = inputs[2],
    .expected_dstr = dstrs2[2], .expected_data = inputs[2], .expected_len = 5};
    samples[9] = (attrs_io){.charstar_input = inputs[3],
    .expected_dstr = dstrs2[3], .expected_data = inputs[3], .expected_len = 10};
    samples[10] = (attrs_io){.charstar_input = inputs[4],
    .expected_dstr = dstrs2[4], .expected_data = inputs[4], .expected_len = 21};
    samples[11] = (attrs_io){.charstar_input = inputs[5],
    .expected_dstr = dstrs2[5], .expected_data = inputs[5], .expected_len = 31};
    return samples;
}

attrs_samples get_attrs_toheap_unsplit_samples() {
    printf("getting the attrs_toheap_unsplit samples");
    char** inputs = get_charstar_inputs();
    uint32* outputlens = get_len_outputs();
    void* tail = get_tailbuff();
    attrs_samples samples = (attrs_samples)malloc(sizeof(attrs_io) * attrs_sample_size);
    void* newtail;
    for(int i = 0; i < attrs_sample_size; i++) {
        printf("%d; ", i);
        newtail = dstr_attrs_toheap_unsplit(inputs[i], tail); //this will put a pointer
        samples[i] = (attrs_io){.charstar_input = inputs[i], .expected_dstr = *(dstr**)tail,
        .expected_data = inputs[i], .expected_len = outputlens[i]};
    }
    return samples;
}

attrs_samples get_attrs_toheap_split_samples() {
    printf("getting the attrs_toheap_split samples");
    char** inputs = get_charstar_inputs();
    dstr* outputdstrs = (dstr*)malloc(sizeof(dstr) * attrs_sample_size);
    attrs_samples samples = (attrs_samples)malloc(sizeof(attrs_io) * attrs_sample_size);
    uint32* outputlens = get_len_outputs();
    for(int i = 0; i < attrs_sample_size; i++) {
        dstr_attrs_toheap_split(inputs[i], outputdstrs + i);
        samples[i] = (attrs_io){.charstar_input = inputs[i], .expected_dstr = outputdstrs + i,
        .expected_data = inputs[i], .expected_len = outputlens[i]};
    }
    return samples;
}

attrs_samples get_attrs_toheap_samples(){
    printf("getting the attrs_toheap_samples");
    char** inputs = get_charstar_inputs();
    uint32* outputlens = get_len_outputs();
    dstr* splitoutputdstrs = (dstr*)malloc(sizeof(dstr) * attrs_sample_size);
    dstr** unsplitoutputdstrs = (dstr**)malloc(sizeof(dstr*) * attrs_sample_size);
    attrs_samples samples = (attrs_samples)malloc(sizeof(attrs_io) * 2 * attrs_sample_size);
    for(int i = 0; i < attrs_sample_size; i++) {
        //first do the split thing.
        dstr_attrs_toheap(inputs[i], splitoutputdstrs + i, NULL);
    }
    for(int i = 0; i < attrs_sample_size; i++) {
        //then we do the unsplit thing.
        dstr_attrs_toheap(inputs[i], NULL, (void*)(unsplitoutputdstrs + i));
    }
    for(int i = 0; i < attrs_sample_size; i++) {
        //assign the inputs
        samples[i].charstar_input = inputs[i]; samples[attrs_sample_size + i].charstar_input = inputs[i];
        //assign the expected chars.
        samples[i].expected_data = inputs[i]; samples[i + attrs_sample_size].expected_data = inputs[i];
        //assign the expected lens.
        samples[i].expected_len = outputlens[i]; samples[attrs_sample_size + i].expected_len = outputlens[i];
        //then assign the dstrs, first the split version, then the unsplit version;
        samples[i].expected_dstr = splitoutputdstrs + i; samples[attrs_sample_size + i].expected_dstr = unsplitoutputdstrs[i];
    }
    return samples;
}

attrs_samples get_attrs_tobloc_unsplit_samples() {
    blocksize b = 64;
    printf("getting the attrs_tobloc_unsplit samples\n");
    char** inputs = get_charstar_inputs();
    void* void_ptr = get_tailbuff();
    dstr** dstr_ptrs = (dstr**)malloc(sizeof(dstr*) * attrs_sample_size);
    printf("got dstr_pointers\n");
    attrs_samples samples = (attrs_samples)malloc(sizeof(attrs_io) * attrs_sample_size);
    printf("got resources\n");
    for(int i = 0; i < attrs_sample_size; i++) {
        printf("%d\n", i);
        samples[i].expected_dstr = (dstr*)void_ptr;
        void_ptr = dstr_attrs_tobloc_unsplit(inputs[i], void_ptr, 64);
        samples[i].charstar_input = inputs[i];
        samples[i].expected_data = inputs[i];
        samples[i].expected_len = inputs[i] == NULL ? 0 : strlen(inputs[i]);
        void_ptr = void_ptr + 64; // this is inefficient.
    }
    printf("successfully run all the dstrs_tobloc operations.\n");
    return samples;
}

attrs_samples get_attrs_tobloc_split_samples() {
    printf("getting the attrs_tobloc_split samples\n");
    char** inputs = get_charstar_inputs();
    void* void_ptr = get_tailbuff();
    dstr* dstrs = (dstr*)malloc(sizeof(dstr) * attrs_sample_size);
    attrs_samples samples = (attrs_samples)malloc(sizeof(attrs_io) * attrs_sample_size);
    for(int i = 0; i < attrs_sample_size; i++) {
        void_ptr = dstr_attrs_tobloc_split(inputs[i], dstrs + i, void_ptr, 64);
        samples[i].expected_dstr = dstrs + i;
        samples[i].charstar_input = inputs[i];
        samples[i].expected_data = inputs[i];
        samples[i].expected_len = inputs[i] == NULL ? 0 : strlen(inputs[i]);
        void_ptr = void_ptr + 64;
    }
    return samples;
}

attrs_samples get_attrs_tobloc_samples(){
    printf("getting the attrs_tobloc_samples\n");
    char** inputs = get_charstar_inputs();
    void* void_ptr = get_tailbuff();
    uint32* outputlens = get_len_outputs();
    dstr* splitoutputdstrs = (dstr*)malloc(sizeof(dstr) * attrs_sample_size);
    dstr** unsplitoutputdstrs = (dstr**)malloc(sizeof(dstr*) * attrs_sample_size);
    attrs_samples samples = (attrs_samples)malloc(sizeof(attrs_io) * 2 * attrs_sample_size);
    for(int i = 0; i < attrs_sample_size; i++) {
        //first do the split thing.
        void_ptr = dstr_attrs_tobloc(inputs[i], splitoutputdstrs + i, void_ptr, 64);
        void_ptr += 64;
    }
    for(int i = 0; i < attrs_sample_size; i++) {
        //then we do the unsplit thing.
        unsplitoutputdstrs[i] = (dstr*)void_ptr;
        void_ptr = dstr_attrs_tobloc(inputs[i], NULL, void_ptr, 64);
    }
    for(int i = 0; i < attrs_sample_size; i++) {
        //assign the inputs
        samples[i].charstar_input = inputs[i]; samples[attrs_sample_size + i].charstar_input = inputs[i];
        //assign the expected chars.
        samples[i].expected_data = inputs[i]; samples[attrs_sample_size + i].expected_data = inputs[i];
        //assign the expected lens.
        samples[i].expected_len = outputlens[i]; samples[attrs_sample_size + i].expected_len = outputlens[i];
        //then assign the dstrs, first the split version, then the unsplit version;
        samples[i].expected_dstr = splitoutputdstrs + i; samples[attrs_sample_size + i].expected_dstr = unsplitoutputdstrs[i];
    }
    return samples;
}