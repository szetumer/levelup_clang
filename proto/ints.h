#ifndef PROTOINTS
#define PROTOINTS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "int.h"
#include "base.h"

//ints are the simplest implementation of a dynamic array of integers.
typedef struct ints {
    int*           data;
    unsigned int   len;
    unsigned int   _impl;
} ints;

/*
THESE METHODS ARE THE GETTERS FOR THE INTS OBJECT.
*/
int             ints_nth(ints, int, int defaultval);
int*            ints_nth_addrs(ints, int);    
unsigned int    ints_len(ints);
impl            ints_impl(ints);
unsigned int    ints_memsize(ints);
unsigned int    ints_itemsize(ints);
unsigned int    ints_blocksize(ints);

/*

THESE ARE THE SUPPORT TYPES.
*/
typedef int ints_index;
//evaluations
typedef bool (*ints_criteria )(ints);
typedef bool (*ints_relation)(ints, ints);
typedef bool (*ints_powerset_relation)(int, ints);

//these are functions which take an ints and an index and return a value.
typedef int (*ints_iter_toint)(ints, ints_index);
typedef int (*ints_iter2_toint)(ints, ints_index, ints_index);
typedef int (*ints_iter3_toint)(ints, ints_index, ints_index, ints_index);

//provide the attributes directly.
ints    ints_attrs_tonew(int*, int);
void*   ints_attrs_tobuff(void*, int*, int);

//concatenate two ints
ints    ints_cat_tonew(ints, ints);
void*   ints_cat_tobuff(void*, ints, ints);

//slice a ints, taking the lowerbound, inclusive to the upper bound, exclusive
ints    ints_slice_tonew(ints, int, int);
void*   ints_slice_tobuff(void*, ints, int, int);
ints    ints_slice_toref(ints, int, int);

//create a new ints with the values at the indicies of the input ints.
ints    ints_fromindicies_tonew(ints, ints indicies);
void*   ints_fromindicies_tobuff(void*, ints, ints indicies);

//get ints from specifying a range
ints    ints_range_tonew(int, int, int);
void*   ints_range_tobuff(void*, int, int, int);

//provide an ints with constant values.
ints    ints_repeat_tonew(int, int);
void*   ints_repeat_tobuff(void*, int, int);

//get ints from intersecting two ints
ints    ints_intersect_tonew(ints, ints);
void*   ints_intersect_tobuff(void*, ints, ints);

//get indicies of ints that meet a criteria.
ints    ints_toindicies_matchingcriteria_tonew(ints, int_criteria);
void*   ints_toindicies_matchingcriteria_tobuff(void*, ints, int_criteria);

//get indicies of ints that match a value.
ints    ints_toindicies_matchingint_tonew(ints, int);
void*   ints_toindicies_matchingint_tobuff(void*, ints, int);

//copy a pre-existing ints
ints    ints_copy_tonew(ints);
void*   ints_copy_tobuff(void*, ints);
ints    ints_copy_toref(ints);

//create an ints by using an iterator on another ints.
//creation from others must be done in the proto file.
ints    ints_applyiter_toint_tonew(ints, ints_iter_toint);
void*   ints_applyiter_toint_tobuff(void*, ints, ints_iter_toint);

//compare two ints
int     ints_eq(ints, ints);

//memory management help
void    ints_free(ints); //free the memory ints sits in, only if it was created by new.

//getters. There are no setters at this time.

//reductions
int ints_min(ints, int defaultval);
int ints_max(ints, int defaultval);
int ints_valmax_from_intsiter_toint(ints, ints_iter_toint, int defaultval);
int ints_valmax_from_intsiter2_toint(ints, ints_iter2_toint, int defaultval);

//operations
void ints_printf(ints);

//mutations - objects that take in an object and change its internal state.
//there is a mutation phenotype for each of the evaluation types that take an object.
    //note this would be much easier if c were a more functional language but whatever.
    //drop obj meeting a criteria.
void ints_droplast_criteriamatch(ints*, int_criteria);
void ints_dropfirst_criteriamatch(ints*, int_criteria);
void ints_dropall_criteriamatch(ints*, int_criteria);
    //drop obj that is a match for input obj.

void ints_droplast_intmatch(ints*, int);
void ints_dropfirst_intmatch(ints*, int);
void ints_dropall_intmatches(ints*, int);
    //drop obj that is a match for

//evaulations (return 1 if true, 0 if false)
int ints_contains_int(ints, int);
int ints_contains_ints(ints, ints);
int ints_has_subints(ints, ints);
int ints_isnull(ints);

//ints utility functions
int PROTOINTSSAMPLES;
ints* ints_samples();

//util functions
int _int_sqrt(int);
int _int_cbrt(int);

/*
THESE ARE THE GENERIC METHODS FOR THE INTS OBJECT. THEY ALLOW
US TO INTERFACE BETWEEN PROTO BASE AND THE INTS OBJECT.
*/

unsigned int    ints_proto_memsize(void*);
unsigned int    ints_proto_itemsize(void*, unsigned int index);
unsigned int    ints_proto_datasize(void*);

/*
THESE ARE BUILDER METHODS FOR ADJUSTING MUTABLE STATE.
A builder is just like a smart pointer, but it is used to adjust the state of the object.
It contains enough information to know which memory it can and cannot touch.
*/

typedef struct ints_bldr {
    ints*           strs_;
    void*           leftmost_byte;
    void*           rightmost_byte;
    unsigned int    leftmin_itemsshouldbe_addable;
    unsigned int    rightmin_itemsshouldbe_addable;
} ints_bldr;

void*           ints_indexlowerbound(ints_bldr);
void*           ints_indexupperbound(ints_bldr);
unsigned int    ints_totalbytes_capacity(ints_bldr);
unsigned int    ints_totalitems_capacity(ints_bldr);
unsigned int    ints_totalbytes_available(ints_bldr);
unsigned int    ints_totalitems_available(ints_bldr);
unsigned int    ints_totalbytes_beingused(ints_bldr);
unsigned int    ints_totalitems_beingused(ints_bldr);
unsigned int    ints_leftbytes_available(ints_bldr);
unsigned int    ints_leftitems_available(ints_bldr);
unsigned int    ints_rightbytes_available(ints_bldr);
unsigned int    ints_rightitems_available(ints_bldr);
unsigned int    ints_bytes_toshift_left(ints_bldr); //the number of bytes that data must be shifted left to regain the minimum left bytes.
unsigned int    ints_bytes_toshift_right(ints_bldr); //the number of bytes that data must be shifted right to regain the minimum right bytes. 
result          ints_shift_leftn(ints_bldr, unsigned int n); //shifts the data to the left, returns a result.
result          ints_shift_rightn(ints_bldr, unsigned int n); //shifts the data to the right, returns a result.
result          ints_shift_leftn_fromindex(ints_bldr, unsigned int n, unsigned int index); //shifts the data to the left from the index, returns a result.
result          ints_shift_rightn_fromindex(ints_bldr, unsigned int n, unsigned int index); //shifts the data to the right from the index, returns a result.
unsigned int    ints_leftitems_couldadd(ints_bldr); //the number of items that could be added to the left side.
unsigned int    ints_rightitems_couldadd(ints_bldr); //the number of items that could be added to the right side.

#endif