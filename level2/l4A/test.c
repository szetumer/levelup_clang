#include <stdio.h>
#include <stdlib.h>
#include <libcalg-1.0/libcalg/queue.h>
#include "samples.h"
#include "../../proto/ints.h"

int test_ints_from_sll() {
    return 0;
}

int test_remove_nth_leet19() {
    return 0;
}

int main() {
    int result0 = test_ints_from_sll();
    printf("+----------------------------------------+\n");
    int result1 = test_remove_nth_leet19();
    printf("+----------------------------------------+\n");

    printf("Can you create a linked list from an ints object:       %s\n", result0 ? "PASS" : "FAIL");
    printf("Can you used slingly linked lists to solve leet 19?:    %s\n", result0 ? "PASS" : "FAIL");

    return 0;
}