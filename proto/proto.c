#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "strs.h"
#include "ints.h"
#include "proto.h"

//get ints from the lengths of strs strings.
ints ints_from_strslens_tonew(strs input) {
    return (ints){NULL, 0};
}

void* ints_from_strslens_onbuff(void* inbuff, strs input) {
    return inbuff;
}

//get strs by splitting string on ints indicies.
strs strs_from_splitonindicies_tonew(char* str, ints indicies) {
    return (strs){NULL, 0};
}

void* strs_from_splitonindicies_onbuff(void* inbuff, char* str, ints indicies) {
    return inbuff;
}

//get strs from copying the indicies of these indicies.
strs strs_from_copyatindicies_tonew(strs input, ints indicies) {
    return input;
}

void* strs_from_copyatindicies_onbuff(void* inbuff, strs input, ints indicies) {
    return inbuff;
}

//strs from others
strs strs_from_intscast_tonew(ints input, int2str f) {
    return (strs){NULL, 0};
}

void* strs_from_intscast_onbuff(void* inbuff, ints input, int2str f) {
    return inbuff;
}
