#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../proto/base.h"
#include "samples.h"

/*Sample Functions:*/
buff get_buffer(){
    void* buff = malloc(2048);
    return buff;
}

int methods_sample_size = 9;
method* get_methods(){
    void* buff = get_buffer();
    method* methods = (method*)malloc(sizeof(method) * methods_sample_size);
    methods[0] = method_with_blocksize(NULL, buff, 8);
    methods[1] = method_with_blocksize(buff, buff, 8);
    methods[2] = method_with_blocksize(buff, buff, 34245);
    methods[3] = method_with_instruction(NULL, buff, TOBUFF);
    methods[4] = method_with_instruction(buff, buff, TOBUFF);
    methods[5] = method_with_instruction(NULL, buff, TOHEAP);
    methods[6] = method_with_instruction(buff, buff, TOHEAP);
    methods[7] = method_with_instruction(buff, NULL, TOREF);
    methods[8] = method_with_instruction(NULL, NULL, INPLACE);
    return methods;
}

uint32 protos_sample_size = 20;
proto* get_protos(){
    proto* samples = (proto*)malloc(sizeof(proto)* protos_sample_size);
    for(int i = 0; i < protos_sample_size; i++) {
        samples[i] = (proto){.__attrs = i};
    }
    return samples;
}

uint32 lvi_sample_size = 20;
lvi_samples get_lvi_samples(){
    lvi_io* samples = (lvi_io*)malloc(sizeof(lvi_io) * lvi_sample_size);
    samples[0] = (lvi_io){.l_input = UNSPLIT, .v_input = VARIETY_ERROR, .i_input = NULL_IMPLEMENTATION, .output = PROTOERROR,
        .l_output = LOCALIZATION_ERROR, .v_output = VARIETY_ERROR,  .i_output = IMPLEMENTATION_ERROR};
    samples[1] = (lvi_io){ .l_input = UNSPLIT, .v_input = REFERENCE, .i_input = STANDARD, .output = PROTOERROR,
        .l_output = LOCALIZATION_ERROR, .v_output = VARIETY_ERROR,  .i_output = IMPLEMENTATION_ERROR};
    samples[2] = (lvi_io){.l_input = SPLIT, .v_input = REFERENCE, .i_input = STANDARD, .output = PROTOERROR,
        .l_output = LOCALIZATION_ERROR, .v_output = VARIETY_ERROR,  .i_output = IMPLEMENTATION_ERROR};
    samples[3] = (lvi_io){.l_input = NONLOCAL, .v_input = REFERENCE, .i_input = STANDARD, .output = (proto){.__attrs = 1},
        .l_output = NONLOCAL, .v_output = REFERENCE,  .i_output = STANDARD};
    samples[4] = (lvi_io){.l_input = UNSPLIT, .v_input = BUFF, .i_input = STANDARD, .output = (proto){.__attrs = 2},
        .l_output = UNSPLIT, .v_output = BUFF, .i_output = STANDARD};
    samples[5] = (lvi_io){.l_input = SPLIT, .v_input = BUFF, .i_input = STANDARD, .output = (proto){.__attrs = 3},
        .l_output = SPLIT, .v_output = BUFF, .i_output = STANDARD};
    samples[6] = (lvi_io){.l_input = NONLOCAL, .v_input = BUFF, .i_input = STANDARD, .output = (proto){.__attrs = 0},
        .l_output = LOCALIZATION_ERROR, .v_output = VARIETY_ERROR, .i_output = IMPLEMENTATION_ERROR};
    samples[7] = (lvi_io){.l_input = UNSPLIT, .v_input = BUFF, .i_input = GERMAN, .output = (proto){.__attrs = 4},
        .l_output = UNSPLIT, .v_output = BUFF, .i_output = GERMAN};
    samples[8] = (lvi_io){.l_input = SPLIT, .v_input = BUFF, .i_input = GERMAN, .output = (proto){.__attrs = 5},
        .l_output = SPLIT, .v_output = BUFF, .i_output = GERMAN};
    samples[9] = (lvi_io){.l_input = NONLOCAL, .v_input = BUFF, .i_input = GERMAN, .output = (proto){.__attrs = 0},
        .l_output = LOCALIZATION_ERROR, .v_output = VARIETY_ERROR, .i_output = IMPLEMENTATION_ERROR};
    samples[10] = (lvi_io){.l_input = NONLOCAL, .v_input = BUFF, .i_input = GERMAN, .output = (proto){.__attrs = 0},
        .l_output = LOCALIZATION_ERROR, .v_output = VARIETY_ERROR, .i_output = IMPLEMENTATION_ERROR};
    samples[11] = (lvi_io){.l_input = UNSPLIT, .v_input = HEAP, .i_input = STANDARD, .output = (proto){.__attrs = 6},
        .l_output = UNSPLIT, .v_output = HEAP, .i_output = STANDARD};
    samples[12] = (lvi_io){.l_input = SPLIT, .v_input = HEAP, .i_input = STANDARD, .output = (proto){.__attrs = 7},
        .l_output = SPLIT, .v_output = HEAP, .i_output = STANDARD};
    samples[13] = (lvi_io){.l_input = UNSPLIT, .v_input = HEAP, .i_input = GERMAN, .output = (proto){.__attrs = 8},
        .l_output = UNSPLIT, .v_output = HEAP, .i_output = GERMAN};
    samples[14] = (lvi_io){.l_input = SPLIT, .v_input = HEAP, .i_input = GERMAN, .output = (proto){.__attrs = 9},
        .l_output = SPLIT, .v_output = HEAP, .i_output = GERMAN};
    samples[15] = (lvi_io){.l_input = NONLOCAL, .v_input = HEAP, .i_input = STANDARD, .output = (proto){.__attrs = 0},
        .l_output = LOCALIZATION_ERROR, .v_output = VARIETY_ERROR, .i_output = IMPLEMENTATION_ERROR};
    samples[16] = (lvi_io){.l_input = NONLOCAL, .v_input = HEAP, .i_input = STANDARD, .output = (proto){.__attrs = 0},
        .l_output = LOCALIZATION_ERROR, .v_output = VARIETY_ERROR, .i_output = IMPLEMENTATION_ERROR};
    samples[17] = (lvi_io){.l_input = NULL_LOCALIZATION, .v_input = NULL_VARIETY, .i_input = NULL_IMPLEMENTATION, .output = (proto){.__attrs = 10},
        .l_output = NULL_LOCALIZATION, .v_output = NULL_VARIETY, .i_output = NULL_IMPLEMENTATION};
    samples[18] = (lvi_io){.l_input = NULL_LOCALIZATION, .v_input = NULL_VARIETY, .i_input = STANDARD, .output = (proto){.__attrs = 0},
        .l_output = LOCALIZATION_ERROR, .v_output = VARIETY_ERROR, .i_output = IMPLEMENTATION_ERROR};
    return samples;
}

uint32 lbsize_sample_size = 17;
lbsize_samples get_lbsize_samples(){
    lbsize_samples samples = (lbsize_samples)malloc(sizeof(lbsize_io) * lbsize_sample_size);
    samples[0] = (lbsize_io){.l_input = UNSPLIT, .bsize_input = 12, .output = PROTOERROR, .l_output = LOCALIZATION_ERROR, .bsize_output = 0};
    samples[1] = (lbsize_io){.l_input = SPLIT, .bsize_input = 12, .output = PROTOERROR, .l_output = LOCALIZATION_ERROR, .bsize_output = 0};
    samples[2] = (lbsize_io){.l_input = NONLOCAL, .bsize_input = 16, .output = (proto){.__attrs = 0}, .l_output = LOCALIZATION_ERROR, .bsize_output = 0};
    samples[3] = (lbsize_io){.l_input = UNSPLIT, .bsize_input = 16, .output = (proto){.__attrs = 16}, .l_output = UNSPLIT, .bsize_output = 16};
    samples[4] = (lbsize_io){.l_input = SPLIT, .bsize_input = 16, .output = (proto){.__attrs = 17}, .l_output = SPLIT, .bsize_output = 16};
    samples[5] = (lbsize_io){.l_input = NONLOCAL, .bsize_input = 17, .output = (proto){.__attrs = 0}, .l_output = LOCALIZATION_ERROR, .bsize_output = 0};
    samples[6] = (lbsize_io){.l_input = UNSPLIT, .bsize_input = 17, .output = (proto){.__attrs = 16}, .l_output = UNSPLIT, .bsize_output = 16};
    samples[7] = (lbsize_io){.l_input = SPLIT, .bsize_input = 17, .output = (proto){.__attrs = 17}, .l_output = SPLIT, .bsize_output = 16};
    samples[8] = (lbsize_io){.l_input = NONLOCAL, .bsize_input = 18, .output = (proto){.__attrs = 0}, .l_output = LOCALIZATION_ERROR, .bsize_output = 0};
    samples[9] = (lbsize_io){.l_input = UNSPLIT, .bsize_input = 18, .output = (proto){.__attrs = 18}, .l_output = UNSPLIT, .bsize_output = 18};
    samples[10] = (lbsize_io){.l_input = SPLIT, .bsize_input = 18, .output = (proto){.__attrs = 19}, .l_output = SPLIT, .bsize_output = 18};
    samples[11] = (lbsize_io){.l_input = NONLOCAL, .bsize_input = 19, .output = (proto){.__attrs = 0}, .l_output = LOCALIZATION_ERROR, .bsize_output = 0};
    samples[12] = (lbsize_io){.l_input = UNSPLIT, .bsize_input = 19, .output = (proto){.__attrs = 18}, .l_output = UNSPLIT, .bsize_output = 18};
    samples[13] = (lbsize_io){.l_input = SPLIT, .bsize_input = 19, .output = (proto){.__attrs = 19}, .l_output = SPLIT, .bsize_output = 18};
    samples[14] = (lbsize_io){.l_input = NONLOCAL, .bsize_input = 8, .output = (proto){.__attrs = 0}, .l_output = LOCALIZATION_ERROR, .bsize_output = 0};
    samples[15] = (lbsize_io){.l_input = UNSPLIT, .bsize_input = 8, .output = (proto){.__attrs = 0}, .l_output = LOCALIZATION_ERROR, .bsize_output = 0};
    samples[16] = (lbsize_io){.l_input = SPLIT, .bsize_input = 6, .output = (proto){.__attrs = 0}, .l_output = LOCALIZATION_ERROR, .bsize_output = 0};
    return samples;
}