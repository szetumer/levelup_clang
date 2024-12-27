#include <stdio.h>
#include <stdlib.h>
#include <libcalg-1.0/libcalg/queue.h>
#include "samples.h"
#include "../../proto/ints.h"

int test_head_match_ints(Queue* q, ints matching_ints) {
    for(int i = 0; i < ints_len(matching_ints); i++) {
        printf("popping head i off: %d\n", i);
        if ((*(int*)queue_pop_head(q)) != ints_nth(matching_ints, i, -1)) {
            return 0;
        }
    }
    return 1;
}

int test_alternating_head_tail_match_ints(Queue* q, ints matching_ints) {
    for(int i = 0; i < ints_len(matching_ints); i++) {
        printf("popping head and tails alternatingly off: %d\n", i);
        if (i % 2 == 0) {
            if (*(int*)queue_pop_tail(q) != ints_nth(matching_ints, i, -1)) {
                return 0;
            }
        } else {
            if (*(int*)queue_pop_head(q) != ints_nth(matching_ints, i,-1)) {
                return 0;
            }
        }
    }
    return 1;
}

int test_queue_data_structure() {
    queuetest_samples samples = get_queuetest_samples();
    queuetest_io sample0 = samples[0];
    queuetest_io sample1 = samples[1];
    queuetest_io sample2 = samples[2];
    Queue* q;
    ints input_ints, matching_ints;
    //sample 0 tests.
    q = sample0.input_queue;
    load_ints_to_queuehead(q, sample0.input_ints);
    if (!test_tails_match_ints(q, sample0.matching_ints)) {
        printf("Sample 0 failed\n");
        return 0;
    }
    if (!queue_is_empty(q)) {
        printf("Sample 0 failed\n");
        return 0;
    }
    //sample 1 tests.
    load_ints_to_queuehead(q, sample1.input_ints);
    if (!test_head_match_ints(q, sample1.matching_ints)) {
        printf("Sample 1 failed\n");
        return 0;
    }
    if (!queue_is_empty(q)) {
        printf("Sample 1 failed to empty everything\n");
        return 0;
    }
    //sample 2 tests.
    load_ints_to_queuehead(q, sample2.input_ints);
    if (!test_alternating_head_tail_match_ints(q, sample2.matching_ints)) {
        printf("Sample 2 failed\n");
        return 0;
    }

    return 1;
}

int main() {
    int result0 = test_queue_data_structure();
    printf("+----------------------------------------+\n");

    printf("Can you test the queue data structure?: %s\n", result0 ? "PASS" : "FAIL");


    return 0;
}