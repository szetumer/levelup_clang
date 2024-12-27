#ifndef PROTOPROTO
#define PROTOPROTO
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "strs.h"
#include "ints.h"
#include "str.h"

//this includes all methods which require two different proto objects to exist.
//it prevents mutual dependencies among proto objects.

//get ints of strlens from a strs.
ints ints_from_strslens_tonew(strs);
void* ints_from_strslens_onbuff(void*, strs);

//get strs from a string broken at certain indicies.
strs strs_from_splitonindicies_tonew(char*, ints);
void* strs_from_splitonindicies_onbuff(void*, char*, ints);

//get strs by copying indicies provided by ints.
strs strs_from_copyatindicies_tonew(strs, ints);
void* strs_from_copyatindicies_onbuff(void*, strs, ints);

//map typealiases
typedef char* (int2str)(int);
typedef int (int2int)(int);
typedef char* (str2str)(char*);

//strs from others
strs strs_from_intscast_tonew(ints, int2str);
void* strs_from_intscast_onbuff(void*, ints, int2str);

//ints from others
#endif