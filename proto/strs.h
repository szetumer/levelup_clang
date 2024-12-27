#ifndef PROTOSTRS
#define PROTOSTRS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "str.h"

//strs are functional objects. They cannot be mutated, only created, copied.
//They can be compared, and you can extract strings from them with getters.
//Note: you can only free onnew. Otherwise  
typedef struct strs {
    /// a dynamic array of strings.
    char**          data;
    unsigned int    len;
} strs;

//provide the attributes directly.
strs strs_attrs_tonew(char**, int);
void* strs_attrs_tobuff(void*, char**, int);

//copy a pre-existing strs
strs strs_copy_tonew(strs);
void* strs_copy_tobuff(void*, strs);

//concatenate two strs
strs strs_cat_tonew(strs, strs);
void* strs_cat_tobuff(void*, strs, strs);

//slice a strs, taking the lowerbound, inclusive to the upper bound, exclusive
strs strs_slice_tonew(strs, int, int);
void* strs_slice_tobuff(void*, strs, int, int);

//drop a string from strs
strs strs_dropstr_tonew(strs, char*);
void* strs_dropstr_tobuff(void*, strs, char*);

//split a string by a single char, deleting it, giving strings to put in a strs
strs strs_splitbychar_tonew(char*, char);
void* strs_splitbychar_tobuff(void*, char*, char);

//split a string by a set of chars, deleting the splitting chars when encountered, giving a set of strings.
strs strs_splitbynchars_tonew(char*, char*, int);
void* strs_splitbynchars_tobuff(void*, char*, char*, int);

//compare two strs
int strs_eq(strs, strs);

//memory management help
int strs_memsize(strs); //the smallest amount of memory you need to copy all the data in strs. Combines with onbuff methods if you want a single strip to contain your strs.
int strs_blocksize(strs); //right now, this is the same as memsize.
int strs_refsize(strs); //the size of the strings strs references.
void strs_free(strs); //free the memory strs sits in, only if it was created by new.

//getters. There are no setters at this time.
char* strs_nth(strs, int);
int strs_len(strs);
//so far we have no setters. The whole point of strs is to be a tight, read-only array of strings.

//operations
void strs_printf(strs);

//evaulations (return 1 if true, 0 if false)
int strs_contains_str(strs, char*);
int strs_contains_strs(strs, strs);
int strs_has_substrs(strs, strs);
int strs_isnull(strs);

//mutations
void strs_removenulls_withfree(strs);
void strs_removenulls(strs);

//strs utility functions
int PROTOSTRSSAMPLES;
strs* strs_samples();

//strs helper functions
int _str_char_count(char*, char);

#endif