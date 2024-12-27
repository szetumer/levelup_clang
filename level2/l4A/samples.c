#include <stdlib.h>
#include <stdio.h>
#include <libcalg-1.0/libcalg/queue.h>
#include "../../proto/ints.h"
#include "../../proto/base.h"
#include "samples.h"

unsigned int queuetest_samples_size = 3;

queuetest_samples get_queuetest_samples() {
    queuetest_samples samples = (queuetest_samples)malloc(sizeof(queuetest_io) * queuetest_samples_size);
    samples[0] = (queuetest_io) {
        .input_queue = queue_new(),
        .input_ints = ints_attrs_tonew((int[]){1, 2, 3, 4, 5, 6}, 6),
        .matching_ints = ints_attrs_tonew((int[]){1, 2, 3, 4, 5, 6}, 6)};
    samples[1] = (queuetest_io) {
        .input_queue = queue_new(),
        .input_ints = ints_attrs_tonew((int[]){1, 2, 3, 4, 5, 6}, 6),
        .matching_ints = ints_attrs_tonew((int[]){6, 5, 4, 3, 2, 1}, 6)};
    samples[2] = (queuetest_io) {
        .input_queue = queue_new(),
        .input_ints = ints_attrs_tonew((int[]){1, 2, 3, 4, 5, 6}, 6),
        .matching_ints = ints_attrs_tonew((int[]){1, 6, 2, 5, 3, 4}, 6)};
    return samples;
}

void load_ints_to_queuehead(Queue* queue, ints input) {
    for(int i = 0; i < ints_len(input); i++) {
        queue_push_head(queue, (QueueValue)ints_nth_addrs(input, i));
    }
}

/*
Leet 2. Add Two Numbers
Medium
You are given two non-empty linked lists representing two non-negative integers. The digits are stored in reverse order, and each of their nodes contains a single digit. Add the two numbers and return the sum as a linked list.

You may assume the two numbers do not contain any leading zero, except the number 0 itself.

Example 1:

Input: l1 = [2,4,3], l2 = [5,6,4]
Output: [7,0,8]
Explanation: 342 + 465 = 807.
Example 2:

Input: l1 = [0], l2 = [0]
Output: [0]
Example 3:

Input: l1 = [9,9,9,9,9,9,9], l2 = [9,9,9,9]
Output: [8,9,9,9,0,0,0,1]

The number of nodes in each linked list is in the range [1, 100].
0 <= Node.val <= 9
It is guaranteed that the list represents a number that does not have leading zeros.

*/

unsigned int leet2_sample_size = 3;
leet2_samples get_leet2_samples() {
    leet2_samples samples = (leet2_samples)malloc(sizeof(leet2_io) * leet2_sample_size);
    samples[0] = (leet2_io){
        .input1 = ints_attrs_tonew((int[]){2, 4, 3}, 3),
        .input2 = ints_attrs_tonew((int[]){5, 6, 4}, 3),
        .output = ints_attrs_tonew((int[]){7, 0, 8}, 3)};
    samples[1] = (leet2_io){
        .input1 = ints_attrs_tonew((int[]){0}, 1),
        .input2 = ints_attrs_tonew((int[]){0}, 1),
        .output = ints_attrs_tonew((int[]){0}, 1)};
    samples[2] = (leet2_io){
        .input1 = ints_attrs_tonew((int[]){9, 9, 9, 9, 9, 9, 9}, 7),
        .input2 = ints_attrs_tonew((int[]){9, 9, 9, 9}, 4),
        .output = ints_attrs_tonew((int[]){8, 9, 9, 9, 0, 0, 0, 1}, 8)};
    return samples;
}

SListEntry* load_ints_to_slist(ints input) {
    SListEntry* slist = NULL;
    int* item;
    for(int i = 0; i < ints_len(input); i++) {
        item = ints_nth_addrs(input, i);
        slist_append(&slist, item);
    }
    return slist;
}

int list_matches_ints(SListEntry* listhead, ints matchingints) {
    for(int i = 0; i < ints_len(matchingints); i++) {
        if (listhead == NULL) {
            return 0;
        }
        if (*(int*)slist_nth_data(listhead, i) != ints_nth(matchingints, i, -1)) {
            return 0;
        }
    }
    return 1;
}

/*
19. Remove Nth Node From End of List
Medium
Topics
Companies
Hint
Given the head of a linked list, remove the nth node from the end of the list and return its head.

Example 1:

Input: head = [1,2,3,4,5], n = 2
Output: [1,2,3,5]
Example 2:

Input: head = [1], n = 1
Output: []
Example 3:

Input: head = [1,2], n = 1
Output: [1]

Constraints:

The number of nodes in the list is sz.
1 <= sz <= 30
0 <= Node.val <= 100
1 <= n <= sz

*/

