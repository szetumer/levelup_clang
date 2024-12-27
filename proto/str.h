#ifndef PROTOSTR
#define PROTOSTR
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "base.h"

typedef char* str;

unsigned int str_len(str);
unsigned int str_memsize(str);
char str_nth(str, unsigned int n, char defaultval);

//reverse a string
void str_reverse_inplace(str*);
void* str_reverse_tobuff(void*, str);
str str_reverse_tonew(str);

//slice a string
str str_slice_tonew(str, int, int);
void* str_slice_tobuff(void*, str, int, int);

//del whitespace
str str_delwhitespace_tonew(str);
void* str_delwhitespace_tobuff(void*, str);

//copy a string
str str_copy_tonew(str);
void* str_copy_tobuff(void*, str);
str str_copy_toref(str);

int str_substr_index(str, str);
int str_str2int(str, int default_val);

//criteria, properties
int str_contains_alpha(str);
int str_contains_num(str);
int str_isnull(str);
int str_isemptystr(str);

//relationships
int str_eq(str, str);

//str str functions
int str_substr_firstindex(str, str);
int str_substr_lastindex(str, str);

#endif