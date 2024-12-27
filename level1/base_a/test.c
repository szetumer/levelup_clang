#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../../proto/base.h"
#include "samples.h"

int test_proto_from_lvi(){
    lvi_samples samples = get_lvi_samples();
    variety v_input, v_expected, v_actual;
    localization l_input, l_expected, l_actual;
    implementation i_input, i_expected, i_actual;
    proto expected, actual;
    for(int i = 0; i < lvi_sample_size; i++) {
        v_input = samples[i].v_input;
        l_input = samples[i].l_input;
        i_input = samples[i].i_input;
        expected = samples[i].output;
        actual = proto_from_lvi(l_input, v_input, i_input);
        printf("input variety: ");
        variety_printf(v_input);
        printf("\n");
        printf("input localization: ");
        localization_printf(l_input);
        printf("\n");
        printf("input implementation: ");
        implementation_printf(i_input);
        printf("\n");
        printf("expected output: ");
        proto_printf(expected);
        printf("\n");
        printf("actual output: ");
        proto_printf(actual);
        printf("\n");
        if (expected.__attrs != actual.__attrs) {
            printf("the protos are not the same.");
            printf("\n");
            return 0;
        }
        printf("+---+\n");
    }
    return 1;
}

int test_proto_from_lbsize(){
    lbsize_samples samples = get_lbsize_samples();
    blocksize bsize_input, bsize_expected, bsize_actual;
    localization l_input, l_expected, l_actual;
    proto expected, actual;
    for(int i = 0; i < lbsize_sample_size; i++) {
        bsize_input = samples[i].bsize_input;
        l_input = samples[i].l_input;
        expected = samples[i].output;
        actual = proto_from_lbsize(l_input, bsize_input);
        printf("input blocksize: %d\n", bsize_input);
        printf("input localization: ");
        localization_printf(l_input);
        printf("\n");
        printf("expected output: ");
        proto_printf(expected);
        printf("\n");
        printf("actual output: ");
        proto_printf(actual);
        printf("\n");
        if (expected.__attrs != actual.__attrs) {
            printf("the protos are not the same.");
            printf("\n");
            return 0;
        }
        printf("+---+\n");
    }
    return 1;
}

int main() {
    printf("+------------------------------------+\n");
    int result0 = test_proto_from_lvi();
    printf("+------------------------------------+\n");
    int result1 = test_proto_from_lbsize();
    printf("+------------------------------------+\n");

    printf("test get_proto_implementation:                  %s\n", result0 ? "PASS" : "FAIL");
    printf("test get_proto_blocksize:                       %s\n", result1 ? "PASS" : "FAIL");

    return 0;
}