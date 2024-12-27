#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "ints.h"
#include "base.h"

/*
THESE METHODS ARE THE GETTERS FOR THE INTS OBJECT.
*/
int             ints_nth(ints input, int n, int defaultval) {
    if (ints_isnull(input)) {
        return defaultval;
    } else if (n < 0) {
        return defaultval;
    } else if (n >= ints_len(input)) {
        return defaultval;
    } else {
        return input.data[n];
    }
}

int*            ints_nth_addrs(ints input, int n) {
    if (ints_isnull(input)) {
        return NULL;
    } else if (n < 0) {
        return NULL;
    } else if (n >= ints_len(input)) {
        return NULL;
    } else {
        return input.data + n;
    }
}

unsigned int    ints_len(ints input) {
    return input.len;
}

unsigned int    ints_impl(ints input) {
    return impl_get_repr(input._impl);
}

unsigned int    ints_memsize(ints input) {
    if (ints_isnull(input)) {
        return sizeof(ints);
    }
    return sizeof(int) * ints_len(input) + sizeof(ints);
}

unsigned int    ints_blocksize(ints input) {
    //return 0 if ints is not implemented as a block.
    impl implementation = ints_impl(input);
    if (implementation != BLOCK) {
        return 0;
    } else { return input._impl; }
}

/*
CREATION METHODS.
*/

//create with attributes
ints    ints_attrs_tonew(int* data, int size) {
    if ((size == 0) || (data == NULL)) {
        return (ints){.data = NULL, .len = 0, ._impl = proto_attrs(NEW)};
    }
    void* voidptr = malloc(sizeof(int) * size);
    if (voidptr == NULL) {
        printf("cannot create new data array");
        exit(1);
    }
    int* intsptr = (int*)voidptr;
    for(int j = 0; j < size; j++) {
        intsptr[j] = data[j];
    }
    ints output = {intsptr, size, proto_attrs(NEW)};
    return output;
}

void*   ints_attrs_tobuff(void* inbuff, int* data, int size) {
    ints* intsptr = (ints*)inbuff;
    int* dataptr = (int*)(intsptr + 1);
    if ((size == 0) || (data == NULL)) {
        intsptr->len = 0;
        intsptr->data = NULL;
        intsptr->_impl = proto_attrs(BUFF);
        return (void*)dataptr;
    }
    for(int j = 0; j < size; j++) {
        dataptr[j] = data[j];
    }
    intsptr->len = size;
    intsptr->data = dataptr;
    intsptr->_impl = proto_attrs(BUFF);
    return (void*)(dataptr + size);
}

//concatination methods
ints    ints_cat_tonew(ints ints1, ints ints2) {
    if (ints_isnull(ints1)) {
        return ints_copy_tonew(ints2);
    }
    if (ints_isnull(ints2)) {
        return ints_copy_tonew(ints1);
    }
    void* voidptr = malloc(sizeof(int) * (ints1.len + ints2.len));
    if (voidptr == NULL) {
        printf("cannot create new data array");
        exit(1);
    }
    int* dataptr = (int*)voidptr;
    for(int i = 0; i < ints1.len; i++) {
        dataptr[i] = ints1.data[i];
    }
    for(int j = 0; j < ints2.len; j++) {
        dataptr[ints1.len + j] = ints2.data[j];
    }
    ints output = {dataptr, ints1.len + ints2.len, proto_attrs(NEW)};
    return output;
}

void*   ints_cat_tobuff(void* inbuff, ints ints1, ints ints2) {
    if (ints_isnull(ints1)) {
        return ints_copy_tobuff(inbuff, ints2);
    }
    if (ints_isnull(ints2)) {
        return ints_copy_tobuff(inbuff, ints1);
    }
    ints* intsptr = (ints*)inbuff;
    int* dataptr = (int*)(intsptr + 1);
    for(int i = 0; i < ints1.len; i++) {
        dataptr[i] = ints1.data[i];
    }
    for(int j = 0; j < ints2.len; j++) {
        dataptr[ints1.len + j] = ints2.data[j];
    }
    intsptr->len = ints1.len + ints2.len;
    intsptr->data = dataptr;
    return (void*)(dataptr + ints1.len + ints2.len);
}

//slice vector
ints    ints_slice_tonew(ints input, int lowerbound, int upperbound) {
    if (ints_isnull(input)) {
        return (ints){.data = NULL, .len = 0, ._impl = proto_attrs(NEW)};
    }
    if (lowerbound >= upperbound) {
        return (ints){.data = NULL, .len = 0, ._impl = proto_attrs(NEW)};
    }
    if (lowerbound < 0) {
        lowerbound = 0;
    }
    if (upperbound > input.len) {
        upperbound = input.len;
    }
    int newsize = upperbound - lowerbound;
    if (newsize <= 0) {
        return (ints){.data = NULL, .len = 0, ._impl = proto_attrs(NEW)};
    }
    void* voidptr = malloc(sizeof(int) * newsize);
    if (voidptr == NULL) {
        printf("cannot create new data array");
        exit(1);
    }
    int* dataptr = (int*)voidptr;
    for(int i = 0; i < newsize; i++) {
        dataptr[i] = input.data[lowerbound + i];
    }
    ints output = {dataptr, newsize, ._impl = proto_attrs(NEW)};
    return output;
}

void*   ints_slice_tobuff(void* inbuff, ints input, int lowerbound, int upperbound) {
    ints* intsptr = (ints*)inbuff;
    int* dataptr = (int*)(intsptr + 1);
    if (ints_isnull(input)) {
        intsptr->len = 0;
        intsptr->data = NULL;
        intsptr->_impl = proto_attrs(BUFF);
        return (void*)dataptr;
    }
    if (lowerbound >= upperbound) {
        intsptr->len = 0;
        intsptr->data = NULL;
        intsptr->_impl = proto_attrs(BUFF);
        return (void*)dataptr;
    }
    if (lowerbound < 0) {
        lowerbound = 0;
    }
    if (upperbound > input.len) {
        upperbound = input.len;
    }
    int newsize = upperbound - lowerbound;
    if (newsize <= 0) {
        intsptr->len = 0;
        intsptr->data = NULL;
        intsptr->_impl = proto_attrs(BUFF);
        return (void*)dataptr;
    }
    for(int i = 0; i < newsize; i++) {
        dataptr[i] = input.data[lowerbound + i];
    }
    intsptr->len = newsize;
    intsptr->data = dataptr;
    intsptr->_impl = proto_attrs(BUFF);
    return (void*)(dataptr + newsize);
}

ints    ints_slice_toref(ints input, int lowerbound, int upperbound) {
    if (ints_isnull(input)) {
        return (ints){.data = NULL, .len = 0, ._impl = proto_attrs(REF)};
    }
    if (lowerbound >= upperbound) {
        return (ints){.data = NULL, .len = 0, ._impl = proto_attrs(REF)};
    }
    if (lowerbound < 0) {
        lowerbound = 0;
    }
    if (upperbound > input.len) {
        upperbound = input.len;
    }
    int newsize = upperbound - lowerbound;
    if (newsize <= 0) {
        return (ints){.data = NULL, .len = 0, ._impl = proto_attrs(REF)};
    }
    ints output = {input.data + lowerbound, newsize, ._impl = proto_attrs(REF)};
    return output;

}

//helper functions for the range functions
int* _range_up(int* intptr, int start, int stop, int step) {
    //we do NOT address the circumstance where start == stop or start > stop.
    if (step == 0) {
        intptr[0] = start;
        return intptr + 1;
    } else if (step < 0) {
        step = 1;
    } else if (stop < start + step) {
        intptr[0] = start;
        return intptr + 1;
    }
    printf("\n");
    for(int i = start; i < stop; i += step) {
        printf("%d,  ", i);
        intptr[0] = i;
        intptr++;
    }
    printf("\n");
    return intptr;
}

int* _range_down(int* intptr, int start, int stop, int step) {
    //we do NOT address the circumstances where start == stop or start < stop.
    if (step == 0) {
        intptr[0] = start;
        return intptr + 1;
    } else if (step < 0) {
        step = 1;
    } else if (start - step < stop) {
        intptr[0] = start;
        return intptr + 1;
    }
    int neg_step = -step;
    for(int i = start; i > stop; i += neg_step) {
        intptr[0] = i;
        intptr++;
    }
    return intptr;
}

//create ints using a range specifiers
ints    ints_range_tonew(int start, int stop, int step) {
    if (start == stop) {
        return (ints){.data = NULL, .len = 0, ._impl = proto_attrs(NEW)};
    }
    if (step == 0) {
        return ints_attrs_tonew((int[]){start}, 1);
    }
    if (step < 0) {
        step = 1;
    }
    int n, size, remainder;
    n = abs(start - stop);
    remainder = n % step;
    if (remainder != 0) {
        size = (n / step) + 1;
    } else {
        size = (n / step);
    }
    printf("\nallocating %d space\n", size);
    void* voidptr = malloc(sizeof(int) * (size));
    if (voidptr == NULL) {
        printf("couldn't create int array");
        exit(1);
    }
    int* dataarray = (int*)voidptr;
    if (start < stop) {
        _range_up(dataarray, start, stop, step);
    } else {
        _range_down(dataarray, start, stop, step);
    }
    ints output = {dataarray, size, ._impl = proto_attrs(NEW)};
    return output;
}

void*   ints_range_tobuff(void* inbuff, int start, int stop, int step) {
    ints* intsptr = (ints*)inbuff;
    int* dataptr = (int*)(intsptr + 1);
    if (start == stop) {
        intsptr->len = 0;
        intsptr->data = NULL;
        intsptr->_impl = proto_attrs(BUFF);
        return (void*)dataptr;
    }
    if (step == 0) {
        intsptr->len = 1;
        intsptr->data = dataptr;
        intsptr->_impl = proto_attrs(BUFF);
        dataptr[0] = start;
        return (void*)(dataptr + 1);
    }
    if (step < 0) {
        step = 1;
    }
    int n, size, remainder;
    n = abs(start - stop);
    remainder = n % step;
    if (remainder != 0) {
        size = (n / step) + 1;
    } else {
        size = (n / step);
    }
    if (start < stop) {
        _range_up(dataptr, start, stop, step);
    } else {
        _range_down(dataptr, start, stop, step);
    }
    intsptr->len = size;
    intsptr->data = dataptr;
    intsptr->_impl = proto_attrs(BUFF);
    return (void*)(dataptr + size);
}

//create ints of the values in the input ints at the indicies of the second ints.
ints    ints_intersect_tonew(ints input1, ints input2) {
    if (ints_isnull(input1)) {
        return (ints){.data = NULL, .len = 0, ._impl = proto_attrs(NEW)};
    }
    if (ints_isnull(input2)) {
        return (ints){.data = NULL, .len = 0, ._impl = proto_attrs(NEW)};
    }
    void* voidptr = malloc(sizeof(int) * input2.len);
    if (voidptr == NULL) {
        printf("can't create intptr");
        exit(1);
    }
    int* intarray = (int*)voidptr;
    int inboth = 0;
    int in1;
    for(int i = 0; i < input1.len; i++) {
        in1 = ints_nth(input1, i, -1);
        if (ints_contains_int(input2, in1)) {
            intarray[inboth] = in1;
            inboth++;
        }
    }
    if (inboth == 0) {
        free(intarray);
        return (ints){.data = NULL, .len = 0, ._impl = proto_attrs(NEW)};
    }
    ints output = ints_attrs_tonew(intarray, inboth);
    free(intarray);
    return output;
}

void*   ints_intersect_tobuff(void* inbuff, ints input1, ints input2) {
    if (ints_isnull(input1)) {
        ints* intsptr = (ints*)inbuff;
        intsptr->len = 0;
        intsptr->data = NULL;
        intsptr->_impl = proto_attrs(BUFF);
        return (void*)(intsptr + 1);
    }
    if (ints_isnull(input2)) {
        ints* intsptr = (ints*)inbuff;
        intsptr->len = 0;
        intsptr->data = NULL;
        intsptr->_impl = proto_attrs(BUFF);
        return (void*)(intsptr + 1);
    }
    void* voidptr = malloc(sizeof(int) * input2.len);
    if (voidptr == NULL) {
        printf("can't create intptr");
        exit(1);
    }
    int* intarray = (int*)voidptr;
    int inboth = 0;
    int in1;
    for(int i = 0; i < input1.len; i++) {
        in1 = ints_nth(input1, i, -1);
        if (ints_contains_int(input2, in1)) {
            intarray[inboth] = in1;
            inboth++;
        }
    }
    if (inboth == 0) {
        free(intarray);
        ints* intsptr = (ints*)inbuff;
        intsptr->len = 0;
        intsptr->data = NULL;
        intsptr->_impl = proto_attrs(BUFF);
        return (void*)(intsptr + 1);
    }
    void* outbuff = ints_attrs_tobuff(inbuff, intarray, inboth);
    free(intarray);
    return outbuff;
}

//create ints by repeating n things a certain number of times.
ints    ints_repeat_tonew(int val, int times) {
    void* voidptr = malloc(sizeof(int) * (times));
    if (voidptr == NULL) {
        printf("can't create intptr");
        exit(1);
    }
    int* intarray = (int*)voidptr;
    for(int i = 0; i < times; i++) {
        intarray[i] = val;
    }
    ints new = ints_attrs_tonew(intarray, times);
    free(intarray);
    return new;
}

void*   ints_repeat_tobuff(void* inbuff, int val, int times) {
    //not ideal void a buffer function to call malloc, but quick and
    //easy for now.
    void* voidptr = malloc(sizeof(int) * (times));
    if (voidptr == NULL) {
        printf("can't create intptr");
        exit(1);
    }
    int* intarray = (int*)voidptr;
    for(int i = 0; i < times; i++) {
        intarray[i] = val;
    }
    void* outbuff = ints_attrs_tobuff(inbuff, intarray, times);
    free(intarray);
    return outbuff;
}

//create ints by copying the values of the first ints at the indicies of the second ints.
ints    ints_fromindicies_tonew(ints input, ints indicies) {
    if (ints_isnull(input)) {
        return (ints){.data = NULL, .len = 0, ._impl = proto_attrs(NEW)};
    }
    if (ints_isnull(indicies)) {
        return (ints){.data = NULL, .len = 0, ._impl = proto_attrs(NEW)};
    }
    void* voidptr = malloc(sizeof(int) * indicies.len);
    if (voidptr == NULL) {
        printf("can't create intptr");
        exit(1);
    }
    int* intarray = (int*)voidptr;
    for(int i = 0; i < indicies.len; i++) {
        intarray[i] = input.data[indicies.data[i]];
    }
    ints output = {intarray, indicies.len, ._impl = proto_attrs(NEW)};
    return output;
}

void*   ints_fromindicies_tobuff(void* inbuff, ints input, ints indicies) {
    if (ints_isnull(input)) {
        ints* intsptr = (ints*)inbuff;
        intsptr->len = 0;
        intsptr->data = NULL;
        intsptr->_impl = proto_attrs(BUFF);
        return (void*)(intsptr + 1);
    }
    if (ints_isnull(indicies)) {
        ints* intsptr = (ints*)inbuff;
        intsptr->len = 0;
        intsptr->data = NULL;
        intsptr->_impl = proto_attrs(BUFF);
        return (void*)(intsptr + 1);
    }
    void* voidptr = malloc(sizeof(int) * indicies.len);
    if (voidptr == NULL) {
        printf("can't create intptr");
        exit(1);
    }
    int* intarray = (int*)voidptr;
    for(int i = 0; i < indicies.len; i++) {
        intarray[i] = input.data[indicies.data[i]];
    }
    void* outbuff = ints_attrs_tobuff(inbuff, intarray, indicies.len);
    free(intarray);
    return outbuff;
}

//create ints by getting the indicies of matches of criteria.
ints    ints_toindicies_matchingcriteria_tonew(ints input, int_criteria criteria) {
    if (ints_isnull(input)) {
        return (ints){.data = NULL, .len = 0, ._impl = proto_attrs(NEW)};
    }
    int count = 0;
    for(int i = 0; i < input.len; i++) {
        if ((*criteria)(input.data[i])) {
            count++;
        }
    }
    if (count == 0) {
        return (ints){.data = NULL, .len = 0, ._impl = proto_attrs(NEW)};
    }
    void* voidptr = malloc(sizeof(int) * count);
    if (voidptr == NULL) {
        printf("can't create intptr");
        exit(1);
    }
    int* intarray = (int*)voidptr;
    int j = 0;
    for(int i = 0; i < input.len; i++) {
        if ((*criteria)(input.data[i])) {
            intarray[j] = i;
            j++;
        }
    }
    ints output = {intarray, count, ._impl = proto_attrs(NEW)};
    free(intarray);
    return output;
}

void*   ints_toindicies_matchingcriteria_tobuff(void* inbuff, ints input, int_criteria criteria) {
    if (ints_isnull(input)) {
        ints* intsptr = (ints*)inbuff;
        intsptr->len = 0;
        intsptr->data = NULL;
        intsptr->_impl = proto_attrs(BUFF);
        return (void*)(intsptr + 1);
    }
    int count = 0;
    for(int i = 0; i < input.len; i++) {
        if ((*criteria)(input.data[i])) {
            count++;
        }
    }
    if (count == 0) {
        ints* intsptr = (ints*)inbuff;
        intsptr->len = 0;
        intsptr->data = NULL;
        intsptr->_impl = proto_attrs(BUFF);
        return (void*)(intsptr + 1);
    }
    void* voidptr = malloc(sizeof(int) * count);
    if (voidptr == NULL) {
        printf("can't create intptr");
        exit(1);
    }
    int* intarray = (int*)voidptr;
    int j = 0;
    for(int i = 0; i < input.len; i++) {
        if ((*criteria)(input.data[i])) {
            intarray[j] = i;
            j++;
        }
    }
    void* outbuff = ints_attrs_tobuff(inbuff, intarray, count);
    free(intarray);
    return outbuff;
}

//create ints by getting the indicies of matches of an int.
ints    ints_toindicies_matchingint_tonew(ints input, int match) {
    if (ints_isnull(input)) {
        return (ints){.data = NULL, .len = 0, ._impl = proto_attrs(NEW)};
    }
    int count = 0;
    for(int i = 0; i < input.len; i++) {
        if (input.data[i] == match) {
            count++;
        }
    }
    if (count == 0) {
        return (ints){.data = NULL, .len = 0, ._impl = proto_attrs(NEW)};
    }
    void* voidptr = malloc(sizeof(int) * count);
    if (voidptr == NULL) {
        printf("can't create intptr");
        exit(1);
    }
    int* intarray = (int*)voidptr;
    int j = 0;
    for(int i = 0; i < input.len; i++) {
        if (input.data[i] == match) {
            intarray[j] = i;
            j++;
        }
    }
    ints output = {intarray, count, ._impl = proto_attrs(NEW)};
    free(intarray);
    return output;
}

void*   ints_toindicies_matchingint_tobuff(void* inbuff, ints input, int match) {
    if (ints_isnull(input)) {
        ints* intsptr = (ints*)inbuff;
        intsptr->len = 0;
        intsptr->data = NULL;
        intsptr->_impl = proto_attrs(BUFF);
        return (void*)(intsptr + 1);
    }
    int count = 0;
    for(int i = 0; i < input.len; i++) {
        if (input.data[i] == match) {
            count++;
        }
    }
    if (count == 0) {
        ints* intsptr = (ints*)inbuff;
        intsptr->len = 0;
        intsptr->data = NULL;
        intsptr->_impl = proto_attrs(BUFF);
        return (void*)(intsptr + 1);
    }
    void* voidptr = malloc(sizeof(int) * count);
    if (voidptr == NULL) {
        printf("can't create intptr");
        exit(1);
    }
    int* intarray = (int*)voidptr;
    int j = 0;
    for(int i = 0; i < input.len; i++) {
        if (input.data[i] == match) {
            intarray[j] = i;
            j++;
        }
    }
    void* outbuff = ints_attrs_tobuff(inbuff, intarray, count);
    free(intarray);
    return outbuff;
}

//create ints by using an iterator taking in an ints.
ints    ints_applyiter_toint_tonew(ints input, ints_iter_toint iter) {
    ints output = ints_repeat_tonew(0, input.len);
    for(int i = 0; i < input.len; i++) {
        output.data[i] = (*iter)(input, i);
    }
    return output;
}

void*   ints_applyiter_toint_tobuff(void* inbuff, ints input, ints_iter_toint iter) {
    void* outbuff = ints_repeat_tobuff(inbuff, 0, input.len);
    ints* intsptr = (ints*)inbuff;
    for(int i = 0; i < input.len; i++) {
        (intsptr->data)[i] = iter(input, i);
    }
    return outbuff;
}

/*
COPY METHODS
*/
ints    ints_copy_tonew(ints input) {
    if (ints_isnull(input)) {
        return (ints){.data = NULL, .len = 0, ._impl=proto_attrs(NEW)};
    }
    void* voidptr = malloc(sizeof(int) * (input.len));
    if (voidptr == NULL) {
        printf("can't create ints pointer right now");
        exit(1);
    }
    int* intsptr = (int*)voidptr;
    for(int i = 0; i < input.len; i++) {
        intsptr[i] = input.data[i];
    }
    ints output = {intsptr, input.len, ._impl=proto_attrs(NEW)};
    return output;
}

void*   ints_copy_tobuff(void* inbuff, ints input) {
    ints* intsptr = (ints*)inbuff;
    int* dataptr = (int*)(intsptr + 1);
    if (ints_isnull(input)) {
        intsptr->len = 0;
        intsptr->data = NULL;
        intsptr->_impl = proto_attrs(BUFF);
        return (void*)dataptr;
    }
    for(int i = 0; i < input.len; i++) {
        dataptr[i] = input.data[i];
    }
    intsptr->len = input.len;
    intsptr->data = dataptr;
    intsptr->_impl = proto_attrs(BUFF);
    return (void*)(dataptr + input.len);
}

ints    ints_copy_toref(ints input) {
    ints output = {input.data, input.len, ._impl=proto_attrs(REF)};
    return output;
}

/*
OPERATIONS
*/

//print methods
void    ints_printf(ints input){
    if (input.data == NULL) {
        printf("loc: %p; ", input.data);
        printf("impl: ");
        impl_printf(input._impl);
        printf(", ");
        printf("size: %d; ", input.len);
        printf("<NULL>");
        return;
    }
    printf("loc: %p; ", input.data);
    printf("size: %d; ", input.len);
    printf("impl: ");
    impl_printf(input._impl);
    printf(", ");
    for(int i = 0; i < input.len; i++) {
        printf("%d, ", input.data[i]);
    }
}

/*
EVALUATIONS
*/
int     ints_eq(ints ints1, ints ints2) {
    if (ints1.len != ints2.len) {
        return 0;
    }
    //null check on char** ptr
    if (ints1.data == NULL) {
        if (ints2.data == NULL) {
            return 1;
        } else {
            return 0;
        }
    }
    for(int i = 0; i < ints1.len; i++) {
        //null check on each of the char* ptrs
        if (ints1.data[i] != ints2.data[i]) {
            return 0;
        }
    }
    return 1;
}

/*
*
*
*
*
*
*/

int     ints_contains_int(ints input, int n) {
    if (ints_isnull(input)) {
        return 0;
    }
    for(int i = 0; i < input.len; i++) {
        if (input.data[i] == n) {
            return 1;
        }
    }
    return 0;
}

int     ints_contains_ints(ints bigints, ints smallints) {
    if (ints_isnull(bigints)) {
        if (ints_isnull(smallints)) {
            return 1;
        }
        return 0;
    }
    if (ints_isnull(smallints)) {
        return 1;
    }
    for(int i = 0; i < smallints.len; i++) {
        if (!ints_contains_int(bigints, smallints.data[i])) {
            return 0;
        }
    }
    return 1;
}

void    ints_free(ints input) {
    if (ints_isnull(input)) {
        return;
    }
    if (impl_get_repr(input._impl) == NEW) {
        free(input.data);
    } else {
        printf("cannot free ints that are not new");
        exit(1);
    }
}

int     ints_isnull(ints input) {
    if ((input.data == NULL) || (input.len == 0)) {
        return 1;
    }
    return 0;
}

int     ints_ith_jth(ints input, int i, int j, int defaultval) {
    if (ints_isnull(input)) {
        return defaultval;
    }
    if ((i < 0) || (j < 0)) {
        return defaultval;
    }
    int smallsize = _int_sqrt(input.len);
    if ((smallsize == -1) || (i >= smallsize) || (j >= smallsize)) {
        return defaultval;
    }
    return input.data[(i * smallsize) + j];
}

int     ints_ith_jth_kth(ints input, int i, int j, int k, int defaultval) {
    if (ints_isnull(input)) {
        return defaultval;
    }
    if ((i < 0) || (j < 0) || (k < 0)) {
        return defaultval;
    }
    int smallsize = _int_cbrt(input.len);
    if ((smallsize == -1) || (i >= smallsize) || (j >= smallsize) || (k >= smallsize)) {
        return defaultval;
    }
    return input.data[(i * smallsize * smallsize) + (j * smallsize) + k];
}

int     ints_min(ints input, int defaultval) {
    if (ints_isnull(input)) {
        return defaultval;
    }
    int min = input.data[0];
    for(int i = 1; i < input.len; i++) {
        if (input.data[i] < min) {
            min = input.data[i];
        }
    }
    return min;
}

int     ints_max(ints input, int defaultval) {
    if (ints_isnull(input)) {
        return defaultval;
    }
    int max = input.data[0];
    for(int i = 1; i < input.len; i++) {
        if (input.data[i] > max) {
            max = input.data[i];
        }
    }
    return max;
}

int     ints_valmax_from_intsiter_toint(ints input, ints_iter_toint f, int defaultval) {
    if (ints_isnull(input)){
        return defaultval;
    }
    int max = (*f)(input, 0);
    for(int i = 0; i < input.len; i++) {
        int val = (*f)(input, i);
        if (val > max) {
            max = val;
        }
    }
    return max;
}

int     ints_valmax_from_intsiter2_toint(ints input, ints_iter2_toint f, int defaultval) {
    if (ints_isnull(input)) {
        return defaultval;
    }
    int max, val;
    max = (*f)(input, 0, 0);
    for(int i = 0; i < input.len; i++) {
        for(int j = 0; j < input.len; j++) {
            val = (*f)(input, i, j);
            max = (val > max) ? val : max;
        }
    }
    return max;
}


ints    ints_iter2_toints_tonew(ints input, ints_iter2_toint f) {
    if (ints_isnull(input)) {
        return ints_attrs_tonew(NULL, 0);
    }
    int outputsize = input.len * input.len;
    ints output = ints_repeat_tonew(0, outputsize);
    for(int i = 0; i < input.len; i++) {
        for(int j = 0; j < input.len; j++) {
            output.data[(i * input.len) + j] = (*f)(input, i, j);
        }
    }
    return output;
}

//drop with criteria
void    ints_dropfirst_criteriamatch(ints* input, int_criteria criteria) {
    //first null case: return nothing after doing nothing.
    if (ints_isnull(*input)) {
        return;
    }
    //size must now be positive if input is properly formatted.
    //now set the first index
    int firstindex = -1;
    for(int i = 0; i < input->len; i++) {
        if ((*criteria)((input->data)[i])) {
            firstindex = i;
            break;
        }
    }
    //if no match, do nothing.
    if (firstindex < 0) {
        return;
    }
    //if match, and removing the only element, then set to null,
    if ((firstindex >= 0) && (input->len == 1)) {
        if (impl_get_repr(input->_impl) == NEW) {ints_free(*input);}
        input->data = NULL;
        input->len = 0;
        return;
    }
    //if match, and removing not the only element, do the following:
    for(int i = firstindex; i < input->len - 1; i++) {
        (input->data)[i] = (input->data)[i + 1];
    }
    input->len = input->len - 1;
    return;
}

void    ints_droplast_criteriamatch(ints* input, int_criteria criteria) {
    //if the input is null
    if (ints_isnull(*input)) {
        return;
    }
    //find the last index that meets the selector
    int lastindex = -1;
    for(int i = input->len - 1; i >= 0; i--) {
        if ((*criteria)((input->data)[i])) {
            lastindex = i;
            break;
        }
    }
    //if there is no element to remove
    if (lastindex == -1) {
        return;
    }
    //if we are removing the only element
    if ((lastindex != -1) && (input->len == 1)) {
        if (impl_get_repr(input->_impl) == NEW) {ints_free(*input);}
        input->data = NULL;
        input->len = 0;
        return;
    }
    for(int i = lastindex; i < input->len; i++) {
        //get the above element
        (input->data)[i] = (input->data)[i + 1];
    }
    input->len = input->len - 1;
    return;
}

void    ints_dropall_criteriamatch(ints* input, int_criteria criteria) {
    //these are not the best implementations but they are not terrible.
    //we have a totally templatable approach, making this amenable to code gen.
    //meaning we don't actually access any of the specific properties of the ints class,
    //just its generic-able properties.
    //if the input is null
    if (ints_isnull(*input)) {
        return;
    }
    int matchcount = 0;
    int size = ints_len(*input);
    for(int i = 0; i < size; i++) {
        if ((*criteria)(ints_nth(*input, i, -1))) {
            matchcount++;
        }
    }
    if (matchcount == 0) {return;}
    for(int j = 0; j <= matchcount; j++) {
        ints_droplast_criteriamatch(input, criteria);
    }
    //there is never any thing to think about.
    return;
}

//drop with matching integer
void    ints_dropfirst_intmatch(ints* input, int matchint) {
    //first null case: return nothing after doing nothing.
    if (ints_isnull(*input)) {
        return;
    }
    //size must now be positive if input is properly formatted.
    //now set the first index
    int firstindex = -1;
    for(int i = 0; i < input->len; i++) {
        if (ints_nth(*input, i, -1) == matchint) {
            firstindex = i;
            break;
        }
    }
    //if no match, do nothing.
    if (firstindex < 0) {
        return;
    }
    //if match, and removing the only element, then set to null,
    if ((firstindex >= 0) && (input->len == 1)) {
        if (impl_get_repr(input->_impl) == NEW) {ints_free(*input);}
        input->data = NULL;
        input->len = 0;
        return;
    }
    //if match, and removing not the only element, do the following:
    for(int i = firstindex; i < input->len - 1; i++) {
        (input->data)[i] = (input->data)[i + 1];
    }
    input->len = input->len - 1;
    return;
}

void    ints_droplast_intmatch(ints* input, int matchint) {
    //if the input is null
    if (ints_isnull(*input)) {
        return;
    }
    //find the last index that meets the selector
    int lastindex = -1;
    for(int i = input->len - 1; i >= 0; i--) {
        if (ints_nth(*input, i, -1) == matchint) {
            lastindex = i;
            break;
        }
    }
    //if there is no element to remove
    if (lastindex == -1) {
        return;
    }
    //if we are removing the only element
    if ((lastindex != -1) && (input->len == 1)) {
        if (impl_get_repr(input->_impl) == NEW) {ints_free(*input);}
        input->data = NULL;
        input->len = 0;
        return;
    }
    for(int i = lastindex; i < input->len; i++) {
        //get the above element
        (input->data)[i] = (input->data)[i + 1];
    }
    input->len = input->len - 1;
    return;
}

void    ints_dropall_intmatches(ints* input, int matchint) {
    if (ints_isnull(*input)) {
        return;
    }
    int matchcount = 0;
    int size = ints_len(*input);
    for(int i = 0; i < size; i++) {
        if (ints_nth(*input, i, -1) == matchint) {
            matchcount++;
        }
    }
    if (matchcount == 0) {return;}
    for(int j = 0; j <= matchcount; j++) {
        ints_droplast_intmatch(input, matchint);
    }
    //there is never any thing to think about.
    return;
}


int PROTOINTSSAMPLES = 4;
ints*   ints_samples() {
    void* voidptr = malloc(sizeof(ints) * (PROTOINTSSAMPLES));
    if (voidptr == NULL) {
        printf("can't create ints array");
        exit(1);
    }
    ints* intsarray = (ints*)voidptr;
    intsarray[0] = ints_attrs_tonew((int []){1, 2, 3}, 3);
    intsarray[1] = ints_attrs_tonew((int []){1, 2, 3, 4, 5}, 5);
    intsarray[2] = ints_attrs_tonew((int []){0}, 1);
    intsarray[3] = ints_attrs_tonew(NULL, 0);
    return intsarray;
}

int _int_sqrt(int n) {
    int out = (int)sqrt((double)n);
    if (out * out != n) {
        return -1;
    }
    return out;
}

int _int_cbrt(int n) {
    int out = (int)cbrt((double)n);
    if (out * out * out != n) {
        return -1;
    }
    return out;
}

/*
BUILDER FUNCTIONS AND UTILITIES
*/

unsigned int    ints_proto_memsize(void* input) {
    ints* inputptr = (ints*)input;
    if (inputptr == NULL) {
        return sizeof(ints);
    }
    return sizeof(ints) + sizeof(int) * inputptr->len;
}

unsigned int    ints_proto_itemsize(void* input, unsigned int index) {
    return sizeof(int);
}

unsigned int    ints_proto_datasize(void* input) {
    ints* inputptr = (ints*)input;
    if (inputptr == NULL) {
        return 0;
    }
    return sizeof(int) * inputptr->len;
}


/*
THESE ARE BUILDER METHODS FOR ADJUSTING MUTABLE STATE.
Builders for fixed size objects only have lowerindex bounds and upperindex bounds.
*/

void*           ints_indexlowerbound(ints_bldr bldr) {
    return NULL;
}
void*           ints_indexupperbound(ints_bldr bldr) {
    return NULL;
}
unsigned int    ints_totalbytes_capacity(ints_bldr bldr) {
    return 1;
}
unsigned int    ints_totalitems_capacity(ints_bldr bldr) {
    return 1;
}
unsigned int    ints_totalbytes_available(ints_bldr bldr) {
    return 1;
}
unsigned int    ints_totalitems_available(ints_bldr bldr) {
    return 1;
}
unsigned int    ints_totalbytes_beingused(ints_bldr bldr) {
    return 1;
}
unsigned int    ints_totalitems_beingused(ints_bldr bldr) {
    return 1;
}
unsigned int    ints_leftbytes_available(ints_bldr bldr) {
    return 1;
}
unsigned int    ints_leftitems_available(ints_bldr bldr) {
    return 1;
}
unsigned int    ints_rightbytes_available(ints_bldr bldr) {
    return 1;
}
unsigned int    ints_rightitems_available(ints_bldr bldr) {
    return 1;
}
unsigned int    ints_bytes_toshift_left(ints_bldr bldrs) {//the number of bytes that data must be shifted left to regain the minimum left bytes.
    return 1;
}
unsigned int    ints_bytes_toshift_right(ints_bldr bldr) { //the number of bytes that data must be shifted right to regain the minimum right bytes.
    return 1;
}
/*
result          ints_shift_leftn(ints_bldr bldr, unsigned int n); //shifts the data to the left, returns a result.
result          ints_shift_rightn(ints_bldr bldr, unsigned int n); //shifts the data to the right, returns a result.
result          ints_shift_leftn_fromindex(ints_bldr bldr, unsigned int n, unsigned int index); //shifts the data to the left from the index, returns a result.
result          ints_shift_rightn_fromindex(ints_bldr bldr, unsigned int n, unsigned int index); //shifts the data to the right from the index, returns a result.
*/
unsigned int    ints_leftitems_couldadd(ints_bldr bldr) { //the number of items that could be added to the left side.
    return 1;
}
unsigned int    ints_rightitems_couldadd(ints_bldr bldr) { //the number of items that could be added to the right side.
    return 1;
}