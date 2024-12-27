#ifndef SAMPLE
#define SAMPLE
#include <stdlib.h>
#include <stdio.h>
#include <libcalg-1.0/libcalg/queue.h>
#include <libcalg-1.0/libcalg/slist.h>
#include "../../proto/ints.h"
#include "../../proto/base.h"

void load_ints_to_queuehead(Queue*, ints);

unsigned int queuetest_samples_size;
typedef struct queuetest_io {
    Queue* input_queue;
    ints  input_ints;
    ints  matching_ints;
} queuetest_io;
typedef queuetest_io* queuetest_samples;

queuetest_samples get_queuetest_samples();

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

unsigned int leet2_sample_size;
typedef struct leet2_io {
    ints input1;
    ints input2;
    ints output;
} leet2_io;
typedef leet2_io* leet2_samples;
leet2_samples get_leet2_samples();
SListEntry* load_ints_to_slist(ints);
int list_matches_ints(SListEntry*, ints);

unsigned int leet19_sample_size;
typedef struct leet19_io {
    SListEntry* input;
    int         nth_to_drop;
    SListEntry* matching_output;     
} leet19_io;
typedef leet19_io* leet19_samples;

SListEntry*     slist_from_nrandom_ints(int n);
int             slist_eq(SListEntry* slist1, SListEntry* slist2);
leet19_samples  get_leet19_samples();

#endif