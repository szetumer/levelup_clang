#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../../proto/dstr.h"
#include "../../proto/base.h"
#include "samples.h"

int test_compiles_samples(){
    return 1; 
}

int test_attrs_tobuff_unsplit(){
    attrs_samples samples = get_attrs_tobuff_unsplit_samples();
    for(int i = 0; i < attrs_sample_size; i++) {
        char* input = samples[i].charstar_input;
        dstr* dstr_output = samples[i].expected_dstr;
        char* output = dstr_data(dstr_output);
        dstr_printf(*dstr_output, 1);
        if (input == NULL) {
            printf("inputcharstr: NULL\n");
        } else {printf("inputcharstr: %s\n", input);}
        if (output == NULL) {
            printf("outputcharstr: NULL\n");
        } else {printf("outputcharstr: %s\n", output);}
        if ((input == NULL) && (output == NULL)) {
            printf("both strings were null");
            continue;
        } else if ((input == NULL) || (output == NULL)){
            printf("only one pointer was null;\n");
            return 0;
        } else if ((strcmp(input, output) != 0)){
            printf("input string: %s\n", input);
            printf("output charstr: %s\n", output);
            return 0;
        } else {
            continue;
        }
    }
    return 1;
}

int test_attrs_tobuff_unsplit_localization(){
    attrs_samples samples = get_attrs_tobuff_unsplit_samples();
    for(int i = 0; i < attrs_sample_size; i++) {
        if (i == attrs_sample_size - 1) {
            return 1;
        }
        dstr*  first_dstr = samples[i].expected_dstr;
        dstr*  second_dstr = samples[i+1].expected_dstr;
        printf("%d: ", i);
        dstr_printf(*first_dstr, 0);
        printf("; totalsize: %d\n", dstr_totalsize(*first_dstr));
        if ((void*)first_dstr + dstr_totalsize(*first_dstr) != (void*)second_dstr) {
            printf("dstrs are not contiguous:\n");
            printf("start: %p; end: %p\n", first_dstr, second_dstr);
            printf("difference between pointers: %ld\n", (long int)second_dstr - (long int)first_dstr);
            return 0;
        }
    }
    return 1;
}

int test_attrs_tobuff_split(){
    attrs_samples samples = get_attrs_tobuff_split_samples();
    for(int i = 0; i < attrs_sample_size; i++) {
        char* input = samples[i].charstar_input;
        dstr* dstr_output = samples[i].expected_dstr;
        char* output = dstr_data(dstr_output);
        dstr_printf(*dstr_output, 1);
        if (input == NULL) {
            printf("inputcharstr: NULL\n");
        } else {printf("inputcharstr: %s\n", input);}
        if (output == NULL) {
            printf("outputcharstr: NULL\n");
        } else {printf("outputcharstr: %s\n", output);}
        if ((input == NULL) && (output == NULL)) {
            printf("both strings were null");
            continue;
        } else if ((input == NULL) || (output == NULL)){
            printf("only one pointer was null;\n");
            return 0;
        } else if ((strcmp(input, output) != 0)){
            printf("input string: %s\n", input);
            printf("output charstr: %s\n", output);
            return 0;
        } else {
            continue;
        }
    }
    return 1;
}

int test_attrs_tobuff_split_localization(){
    attrs_samples samples = get_attrs_tobuff_split_samples();
    for(int i = 0; i < attrs_sample_size; i++) {
        if (i == attrs_sample_size - 1) {
            return 1;
        }
        dstr*  first_dstr = samples[i].expected_dstr;
        dstr*  second_dstr = samples[i+1].expected_dstr;
        printf("%d: ", i);
        dstr_printf(*first_dstr, 0);
        printf("; totalsize: %d\n", dstr_totalsize(*first_dstr));
        if (first_dstr + 1 != second_dstr) {
            printf("dstr heads are not contiguous:\n");
            printf("start: %p; end: %p\n", first_dstr, second_dstr);
            printf("difference between pointers: %ld\n", (long int)second_dstr - (long int)first_dstr);
            return 0;
        }
    }
    return 1;
}

int test_attrs_tobuff(){
    attrs_samples samples = get_attrs_tobuff_samples();
    for(int i = 0; i < 2 * attrs_sample_size; i++) {
        char* input = samples[i].charstar_input;
        dstr* dstr_output = samples[i].expected_dstr;
        char* output = dstr_data(dstr_output);
        dstr_printf(*dstr_output, 1);
        if (input == NULL) {
            printf("inputcharstr: NULL\n");
        } else {printf("inputcharstr: %s\n", input);}
        if (output == NULL) {
            printf("outputcharstr: NULL\n");
        } else {printf("outputcharstr: %s\n", output);}
        if ((input == NULL) && (output == NULL)) {
            printf("both strings were null");
            continue;
        } else if ((input == NULL) || (output == NULL)){
            printf("only one pointer was null;\n");
            return 0;
        } else if ((strcmp(input, output) != 0)){
            printf("input string: %s\n", input);
            printf("output charstr: %s\n", output);
            return 0;
        } else {
            continue;
        }
    }
    return 1;
}

int test_attrs_toheap_unsplit(){
    attrs_samples samples = get_attrs_toheap_unsplit_samples();
    for(int i = 0; i < attrs_sample_size; i++) {
        char* input = samples[i].charstar_input;
        dstr* dstr_output = samples[i].expected_dstr;
        char* output = dstr_data(dstr_output);
        dstr_printf(*dstr_output, 1);
        if (input == NULL) {
            printf("inputcharstr: NULL\n");
        } else {printf("inputcharstr: %s\n", input);}
        if (output == NULL) {
            printf("outputcharstr: NULL\n");
        } else {printf("outputcharstr: %s\n", output);}
        if ((input == NULL) && (output == NULL)) {
            printf("both strings were null");
            continue;
        } else if ((input == NULL) || (output == NULL)){
            printf("only one pointer was null;\n");
            return 0;
        } else if ((strcmp(input, output) != 0)){
            printf("input string: %s\n", input);
            printf("output charstr: %s\n", output);
            return 0;
        } else {
            continue;
        }
    }
    return 1;
}

int test_attrs_generic(attrs_samples get_attrs_samples(), uint32 sample_size){
    attrs_samples samples = get_attrs_samples();
    for(int i = 0; i < sample_size; i++) {
        char* input = samples[i].charstar_input;
        dstr* dstr_output = samples[i].expected_dstr;
        char* output = dstr_data(dstr_output);
        dstr_printf(*dstr_output, 1);
        if (input == NULL) {
            printf("inputcharstr: NULL\n");
        } else {printf("inputcharstr: %s\n", input);}
        if (output == NULL) {
            printf("outputcharstr: NULL\n");
        } else {printf("outputcharstr: %s\n", output);}
        if ((input == NULL) && (output == NULL)) {
            printf("both strings were null");
            continue;
        } else if ((input == NULL) || (output == NULL)){
            printf("only one pointer was null;\n");
            return 0;
        } else if ((strcmp(input, output) != 0)){
            printf("input string: %s\n", input);
            printf("output charstr: %s\n", output);
            return 0;
        } else {
            continue;
        }
    }
    return 1;
}

int test_attrs_length_property(attrs_samples get_attrs_samples(), uint32 sample_size){
    attrs_samples samples = get_attrs_samples();
    for(int i = 0; i < sample_size; i++) {
        char* input = samples[i].charstar_input;
        uint32 inputlen = input == NULL ? (uint32)0 : (uint32)strlen(input);
        dstr* dstr_output = samples[i].expected_dstr;
        uint32 actuallen = dstr_len(*dstr_output);
        printf("input str: %s; strlen: %d\n", input, inputlen);
        dstr_printf(*dstr_output, 0);
        printf(" dstrlen: %d\n", actuallen);
        if (inputlen != actuallen) {
            printf("expected length: %d\n", inputlen);
            printf("actual length: %d\n", actuallen);
            return 0;
        }
    }
    return 1;
}

int main() {
    int result0 = test_compiles_samples();
    printf("+------------------------------------+\n");
    int result1 = test_attrs_tobuff_unsplit();
    printf("+------------------------------------+\n");
    int result2 = test_attrs_tobuff_unsplit_localization();
    printf("+------------------------------------+\n");
    int result3 = test_attrs_tobuff_split();
    printf("+------------------------------------+\n");
    int result4 = test_attrs_tobuff_split_localization();
    printf("+------------------------------------+\n");
    int result5 = test_attrs_tobuff();
    printf("+------------------------------------+\n");
    int result6 = test_attrs_toheap_unsplit();
    printf("+------------------------------------+\n");
    int result7 = test_attrs_generic(get_attrs_tobuff_samples, attrs_sample_size);
    printf("+------------------------------------+\n");
    int result8 = test_attrs_generic(get_attrs_toheap_unsplit_samples, attrs_sample_size);
    printf("+------------------------------------+\n");
    int result9 = test_attrs_length_property(get_attrs_tobuff_samples, attrs_sample_size);
    printf("+------------------------------------+\n");
    int result10 = test_attrs_generic(get_attrs_toheap_split_samples, attrs_sample_size);
    printf("+------------------------------------+\n");
    int result11 = test_attrs_length_property(get_attrs_toheap_split_samples, attrs_sample_size);
    printf("+------------------------------------+\n");
    int result12 = test_attrs_length_property(get_attrs_toheap_unsplit_samples, attrs_sample_size);
    printf("+------------------------------------+\n");
    int result13 = test_attrs_generic(get_attrs_toheap_samples, 2 * attrs_sample_size);
    printf("+------------------------------------+\n");
    int result14 = test_attrs_length_property(get_attrs_toheap_samples, 2 * attrs_sample_size);
    printf("+------------------------------------+\n");
    int result15 = test_attrs_generic(get_attrs_tobloc_unsplit_samples, attrs_sample_size);
    printf("+------------------------------------+\n");
    int result16 = test_attrs_length_property(get_attrs_tobloc_unsplit_samples, attrs_sample_size);
    printf("+------------------------------------+\n");
    int result17 = test_attrs_generic(get_attrs_tobloc_split_samples, attrs_sample_size);
    printf("+------------------------------------+\n");
    int result18 = test_attrs_generic(get_attrs_tobloc_split_samples, attrs_sample_size);
    printf("+------------------------------------+\n");
    int result19 = test_attrs_generic(get_attrs_tobloc_samples, 2 * attrs_sample_size);
    printf("+------------------------------------+\n");


    printf("Can you even compile this?:             %s\n", result0 ? "PASS" : "FAIL");
    printf("test attrs_tobuff_unsplit:              %s\n", result1 ? "PASS" : "FAIL");
    printf("is tobuff unsplit localized correctly:  %s\n", result2 ? "PASS" : "FAIL");
    printf("test attrs_tobuff_split:                %s\n", result3 ? "PASS" : "FAIL");
    printf("is tobuff split localized correctly:    %s\n", result4 ? "PASS" : "FAIL");
    printf("test attrs_tobuff:                      %s\n", result5 ? "PASS" : "FAIL");
    printf("test attrs_toheap_unsplit:              %s\n", result6 ? "PASS" : "FAIL");
    printf("test attrs_tobuff_samples with generic: %s\n", result7 ? "PASS" : "FAIL");
    printf("test attrs_toheap_unsplit_samples w gen:%s\n", result8 ? "PASS" : "FAIL");
    printf("test attrs_length_property for tobuff:  %s\n", result9 ? "PASS" : "FAIL");
    printf("test attrs_toheap_split                 %s\n", result10 ? "PASS" : "FAIL");
    printf("test attrs_toheap_split len prop        %s\n", result11 ? "PASS" : "FAIL");
    printf("test attrs_toheap_unsplit len prop:     %s\n", result12 ? "PASS" : "FAIL");
    printf("test_attrs_toheap both sites.           %s\n", result13 ? "PASS" : "FAIL");
    printf("test_attrs_length for toheap generic:   %s\n", result14 ? "PASS" : "FAIL");
    printf("test_attrs_tobloc_unsplit_samples:      %s\n", result15 ? "PASS" : "FAIL");
    printf("test_attrs_tobloc_unsplit length match: %s\n", result16 ? "PASS" : "FAIL");
    printf("test_attrs_tobloc_split_samples:        %s\n", result17 ? "PASS" : "FAIL");
    printf("test_attrs_tobloc_split length match:   %s\n", result18 ? "PASS" : "FAIL");
    printf("test_attrs_tobloc_samples:              %s\n", result19 ? "PASS" : "FAIL");
    printf("+------------------------------------+\n");

    return 0;
}