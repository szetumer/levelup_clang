#include <stdio.h>
#include <libcalg-1.0/libcalg/queue.h>
#include "samples.h"
#include "../../proto/ints.h"

int test_get_queuetest_samples() {
    queuetest_samples samples = get_queuetest_samples();
    for(int i = 0; i < queuetest_samples_size; i++) {
        printf("Sample %d\n", i);
        printf("Input ints   : ");
        ints_printf(samples[i].input_ints);
        printf("\n");
        printf("Matching ints: ");
        ints_printf(samples[i].matching_ints);
        printf("\n");
    }
    return 1;
}

int test_leet2_samples() {
    leet2_samples samples = get_leet2_samples();
    for(int i = 0; i < leet2_sample_size; i++) {
        printf("Sample %d\n", i);
        printf("Input 1: ");
        ints_printf(samples[i].input1);
        printf("\n");
        printf("Input 2: ");
        ints_printf(samples[i].input2);
        printf("\n");
        printf("Output : ");
        ints_printf(samples[i].output);
        printf("\n");
        SListEntry* list = load_ints_to_slist(samples[i].input1);
        if (!list_matches_ints(list, samples[i].input1)) {
            printf("list and ints don't match");
            return 0;
        }
    }
    return 1;
}


int main(void) {

    int result0 = test_get_queuetest_samples();
    printf("+------------------------------------+\n");
    int result1 = test_leet2_samples();
    printf("+------------------------------------+\n");

    printf("Can you get queuetest_samples?:    %s\n", result0 ? "PASS" : "FAIL");
    printf("Can you get leet2_samples?:        %s\n", result1 ? "PASS" : "FAIL");

    return 0;
}