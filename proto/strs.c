#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "str.h"
#include "strs.h"

void strs_printf(strs input){
    if (input.data == NULL) {
        printf("loc: %p; ", input.data);
        printf("size: %d; ", input.len);
        printf("<NULL>");
        return;
    }
    printf("loc: %p; ", input.data);
    printf("size: %d; ", input.len);
    for(int i = 0; i < input.len; i++) {
        if (input.data[i] == NULL) {
            printf("<NULL>, ");
        }
        else {
            printf("%s, ", input.data[i]);
        }
    }
}

int strs_eq(strs strs1, strs strs2) {
    if (strs1.len != strs2.len) {
        return 0;
    }
    //null check on char** ptr
    if (strs1.data == NULL) {
        if (strs2.data == NULL) {
            return 1;
        } else {
            return 0;
        }
    }
    for(int i = 0; i < strs1.len; i++) {
        //null check on each of the char* ptrs
        if ((strs1.data[i] == NULL) && (strs2.data[i] == NULL)) {
            continue;
        } else if ((strs1.data[i] == NULL) && (strs2.data[i] != NULL)) {
            return 0;
        } else if ((strs1.data[i] != NULL) && (strs2.data[i] == NULL)) {
            return 0;
        } else if (strcmp(strs1.data[i], strs2.data[i]) != 0) {
            return 0;
        } else {continue;}
    }
    return 1;
}

strs strs_copy_tonew(strs input) {
    if ((input.data == NULL) || (input.len == 0)) {
        return (strs){.data = NULL, .len = 0};
    }
    void* voidptr = malloc(sizeof(char*) * (input.len));
    if (voidptr == NULL) {
        printf("can't create char** pointer right now");
        exit(1);
    }
    char** strptr = (char**)voidptr;

    for(int i = 0; i < input.len; i++) {
        if (input.data[i] == NULL) {
            strptr[i] = NULL;
        } else {
            void* voidptr = malloc(sizeof(char) * (strlen(input.data[i])+1));
            if (voidptr == NULL) {
                printf("can't create individual string right now");
                exit(1);
            }
            char* charptr = (char*)voidptr;
            strptr[i] = charptr;
            strcpy(strptr[i], input.data[i]);
        }
    }
    strs output = {strptr, input.len};
    return output;
}

void* strs_copy_tobuff(void* buf, strs input) {
    void* start = buf;
    strs* strsptr = (strs*)start;
    char** dataptr = (char**)(strsptr + 1);
    if (input.data == NULL) {
        strsptr->len = 0;
        strsptr->data = NULL;
        return (void*)(dataptr);
    }
    //if there are char pointers to hold, make room for them.
    char* charptr = (char*)(dataptr + input.len);
    for(int j = 0; j < input.len; j++) {
        if (input.data[j] == NULL) {
            dataptr[j] = NULL;
            continue;
        }
        dataptr[j] = charptr;
        strcpy(charptr, input.data[j]);
        charptr = charptr + strlen(input.data[j]) + 1;
    }
    strsptr->len = input.len;
    strsptr->data = dataptr;
    return (void*)(charptr);
}

strs strs_attrs_tonew(char** attrs, int size) {
    //first, take care of the edge case:
    if ((size == 0) || (attrs == NULL)) {
        return (strs){NULL, 0};
    }
    //then, create enough room for the char** dynamic array.
    void* voidptr = malloc(sizeof(char*) * (size));
    if (voidptr == NULL) {
        printf("cannot create dynamic array of str pointers");
        exit(1);
    }
    char** strsptr = (char**)voidptr;
    //then, we need to copy each new string onto the heap. Later, we will
    //assign their location to the char** dynamic array.
    for(int j = 0; j < size; j++) {
        if (attrs[j] == NULL) {
            strsptr[j] = NULL;
        }
        else {
            void* voidptr = malloc(sizeof(char) * (strlen(attrs[j]) + 1));
            if (voidptr == NULL) {
                printf("errormessage");
                exit(1);
            }
            char* charptr = (char*)voidptr;
            strcpy(charptr, attrs[j]);
            strsptr[j] = charptr;
        }
    }
    strs output = {strsptr, size};
    return output;
}

void* strs_attrs_tobuff(void* buf, char** data, int size) {
    //let's replace this
    strs* strsptr = (strs*)buf;
    char** dataptr = (char**)(strsptr + 1);
    //first we take care of the edge case:
    if ((size == 0) || (data == NULL)) {
        //a null strs object is just a pointer to a null char**.
        strsptr->len = 0;
        strsptr->data = NULL;
        return (void*)dataptr;
    }
    //now we know that size is positive and attrs is not null.
    char* charptr = (char*)(dataptr + size);
    for(int j = 0; j < size; j++) {
        if (data[j] == NULL) {
            dataptr[j] = NULL;
            continue;
        }
        dataptr[j] = charptr; //the current position on the buffer.
        strcpy(charptr, data[j]);
        charptr = charptr + strlen(data[j]) + 1;
    }
    strsptr->len = size;
    strsptr->data = dataptr;
    return (void*)(charptr);
}

strs strs_cat_tonew(strs strs1, strs strs2) {
    //first, take care of the edge cases:
    if ((strs1.len == 0) || (strs1.data == NULL)) {
        return strs_copy_tonew(strs2);
    } 
    if ((strs2.len == 0) || (strs2.data == NULL)) {
        return strs_copy_tonew(strs1);
    }
    //now we know that neither of the strs are null.
    //first we want to copy the data.
    void* voidptr = malloc(sizeof(char*) * (strs1.len + strs2.len));
    if (voidptr == NULL) {
        printf("cannot create new data array");
        exit(1);
    }
    char** dataptr = (char**)voidptr;

    for(int i = 0; i < strs1.len; i++) {
        if (strs1.data[i] == NULL) {
            dataptr[i] = NULL;
        } else {
            dataptr[i] = strs1.data[i];
        }
    }
    for(int j = 0; j < strs2.len; j++) {
        if (strs2.data[j] == NULL) {
            dataptr[strs1.len + j] = NULL;
        } else {        
            dataptr[strs1.len + j] = strs2.data[j];
        }
    }
    //note: these are just references to the old data. We can use the old method to copy the strings.
    strs output = strs_copy_tonew((strs){dataptr, strs1.len + strs2.len});
    free(dataptr);
    return output;
}

void* strs_cat_tobuff(void* inbuff, strs strs1, strs strs2) {
    // not the ideal implementation. But a start
    //first, take care of the edge cases:
    if ((strs1.len == 0) || (strs1.data == NULL)) {
        return strs_copy_tobuff(inbuff, strs2);
    }
    if ((strs2.len == 0) || (strs2.data == NULL)) {
        return strs_copy_tobuff(inbuff, strs1);
    }
    //now we know that neither of the strs are null. They must both have positive size.
    void* voidptr = malloc(sizeof(char*) * (strs1.len + strs2.len));
    if (voidptr == NULL) {
        printf("errormessage");
        exit(1);
    }
    char** strptr = (char**)voidptr;
    for(int i = 0; i < strs1.len; i++) {
        strptr[i] = strs1.data[i];
    }
    for(int j = 0; j < strs2.len; j++) {
        strptr[strs1.len + j] = strs2.data[j];
    }
    void* outbuff = strs_attrs_tobuff(inbuff, strptr, strs1.len + strs2.len);
    free(strptr);
    return outbuff;
}

int strs_contains_str(strs strs1, char* str) {
    //take care of the edge cases
    if ((strs1.len == 0) || (strs1.data == NULL)) {
        return 0;
    }
    //now we know that strs1 is not null.
    if (str == NULL) {
        for(int i = 0; i < strs1.len; i++) {
            if (strs1.data[i] == NULL) {
                return 1;
        }
        return 0;
        }
    } else {
        for(int i = 0; i < strs1.len; i++) {
            if (strs1.data[i] == NULL) {
                continue;
            }
            if (strcmp(strs1.data[i], str) == 0) {
                return 1;
            }
        }
        return 0;
    }
    return 0;
}

int strs_contains_strs(strs strs1, strs strs2) {
    //take care of the edge cases
    if ((strs1.len == 0) || (strs1.data == NULL)) {
        //if strs1 is null, then strs2 must be null to be a subset.
        if((strs2.len == 0) || (strs2.data == NULL)) {
            return 1;
        }
        return 0;
    } else if ((strs2.len == 0) || (strs2.data == NULL)) {
        return 1;
    }
    //now we know that neither of the strs are null.
    for(int i = 0; i < strs2.len; i++) {
        if (strs_contains_str(strs1, strs2.data[i]) == 0) {
            return 0;
        }
    }
    return 1;
}

int strs_isnull(strs strs1) {
    if ((strs1.len == 0) || (strs1.data == NULL)) {
        return 1;
    }
    return 0;
}

int strs_memsize(strs strs1) {
    int strs_size = sizeof(strs);
    if (strs_isnull(strs1)) {
        return strs_size;
    }
    //now we know that data is not null.
    int data_size = strs1.len * sizeof(char*);
    int chars_size = 0;
    for(int j = 0; j < strs1.len; j++) {
        if (strs1.data[j] == NULL) {
            continue;
        }
        chars_size += strlen(strs1.data[j]) + 1;
    }
    return strs_size + data_size + chars_size;
}

int strs_blocksize(strs strs1) {
    return strs_memsize(strs1);
}

int strs_refsize(strs strs1) {
    int refsize = strs_memsize(strs1) - sizeof(strs);
    return (refsize);
}

char* strs_nth(strs strs1, int n) {
    //now we can make this object a little safer.
    if (strs1.data == NULL) {
        return NULL;
    }
    if (strs1.data[n] == NULL) {
        return NULL;
    }
    return strs1.data[n];
}

int strs_len(strs input) {
    return input.len;
}

strs strs_slice_tonew(strs input, int lowerbound, int upperbound) {
    //take care of the edge cases
    if ((input.len == 0) || (input.data == NULL)) {
        return (strs){NULL, 0};
    }
    //get real bounds
    upperbound = (upperbound > input.len ? input.len : upperbound);
    lowerbound = (lowerbound < 0 ? 0 : lowerbound);

    //another check:
    if (lowerbound >= upperbound) {
        return (strs){NULL, 0};
    }
    //now we get the data using strs_get_nth. Note that it must exist because input.data cannot be null.
    //first just get a pointer to strs
    int newsize = upperbound - lowerbound; //must be positive
    void* voidptr = malloc(sizeof(char*) * (newsize));
    if (voidptr == NULL) {
        printf("cannot create strptr");
        exit(1);
    }
    char** strsptr = (char**)voidptr;
    for(int i = 0; i < newsize; i++) {
        strsptr[i] = input.data[lowerbound + i];
    }
    strs output = strs_attrs_tonew(strsptr, newsize);
    return output;
}

void strs_free(strs input) {
    if (input.data == NULL) {
        return;
    }
    for(int i = 0; i < input.len; i++) {
        if (input.data[i] == NULL) {
            continue;
        }
        free(input.data[i]);
    }
    free(input.data);
}

void* strs_slice_tobuff(void* inbuff, strs input, int lowerbound, int upperbound) {
    //slicing without mallocs
    strs* strsaddrs = (strs*)inbuff;
    char** dataaddrs = (char**)(strsaddrs + 1);
    //take care of the edge cases
    if ((input.len == 0) || (input.data == NULL)) {
        strsaddrs->len=0;
        strsaddrs->data=NULL;
        return (void*)dataaddrs;
    }
    //get real bounds
    upperbound = (upperbound > input.len ? input.len : upperbound);
    lowerbound = (lowerbound < 0 ? 0 : lowerbound);

    //another check:
    if (lowerbound >= upperbound) {
        strsaddrs->len=0;
        strsaddrs->data=NULL;
        return (void*)dataaddrs;
    }
    int newsize = upperbound - lowerbound; //must be positive
    char* charptr = (char*)(dataaddrs + newsize); //room enough for newsize char ptrs.
    for(int i = 0; i < newsize; i++) {
        //copy the string onto the strip at the charptr location
        if (input.data[lowerbound + i] == NULL) {
            dataaddrs[i] = NULL;
            continue;
        }
        //the data address is not null. So copy it at the string location.
        strcpy(charptr, input.data[lowerbound + i]);
        //point the straddrs there:
        dataaddrs[i] = charptr;
        //update the charptr.
        charptr = charptr + strlen(charptr) + 1;
    }
    strsaddrs->len = newsize;
    strsaddrs->data = dataaddrs;
    void* outbuff = (void*)charptr;
    return outbuff;
}

strs strs_dropstr_tonew(strs input, char* str) {
    //first take care of the edge cases:
    if ((input.len == 0) || (input.data == NULL)) {
        return (strs){NULL, 0};
    }
    
    int newsize = 0;
    void* voidptr = malloc(sizeof(char*) * (input.len));
    if (voidptr == NULL) {
        printf("couldn't create the strptr");
        exit(1);
    }
    char** strsarray = (char**)voidptr;

    if (str == NULL) {
        for(int i = 0; i < input.len; i++) {
            if (input.data[i] != NULL) {
                strsarray[newsize] = input.data[i];
                newsize++; //next position
            }
        }
        if (newsize == 0) {
            free(strsarray);
            return (strs){NULL, 0};
        }
        strs output = strs_attrs_tonew(strsarray, newsize);
        free(strsarray);
        return output;
    }

    //now we know that input is not null and str is not null.
    //iterate through the strings and get the ones that are not equal to str.
    for(int i = 0; i < input.len; i++) {
        if (input.data[i] == NULL) {
            strsarray[newsize] = NULL;
            newsize++;
            continue;
        }
        if (strcmp(input.data[i], str) != 0) {
            strsarray[newsize] = input.data[i];
            newsize++;
            continue;
        }
    }
    if (newsize == 0) {
        free(strsarray);
        return (strs){NULL, 0};
    }
    strs output = strs_attrs_tonew(strsarray, newsize);
    free(strsarray);
    return output;
}

void* strs_dropstr_tobuff(void* inbuff, strs input, char* str) {
    //first take care of the edge cases:
    strs* strsptr = (strs*)inbuff;
    char** dataptr = (char**)(strsptr + 1);
    int newsize = 0;
    if ((input.len == 0) || (input.data == NULL)) {
        strsptr->len = 0;
        strsptr->data = NULL;
        return (void*)(strsptr + 1);
    }
    //two cases: if str is null, then we just copy the strings that are not null.
    if (str == NULL) {
        printf("str is null\n");
        for(int i = 0; i < input.len; i++) {
            if (input.data[i] != NULL) {
                dataptr[newsize] = input.data[i];
                newsize++;
            }
        }
    } else if (str != NULL) {
        printf("str is not null\n");
        for(int i = 0; i < input.len; i++) {
            if (input.data[i] == NULL) {
                dataptr[newsize] = NULL;
                newsize++;
                continue;
            }
            if (strcmp(input.data[i], str) != 0) {
                dataptr[newsize] = input.data[i];
                newsize++;
                continue;
            }
        }
    } else {exit(1);}
    //if we have no strings to copy, then we return a null strs object.
    if (newsize == 0) {
        strs* strsptr = (strs*)inbuff;
        strsptr->len = 0;
        strsptr->data = NULL;
        return (void*)(strsptr + 1);
    }
    //now we know that we have strings to copy, and that newsize is positive.
    char* charptr = (char*)(dataptr + newsize);
    for(int j = 0; j < newsize; j++) {
        if (dataptr[j] == NULL) {
            continue;
        }
        strcpy(charptr, dataptr[j]);
        dataptr[j] = charptr; //update the pointer to the new location on the buffer.
        charptr = charptr + strlen(charptr) + 1;
    }
    strsptr->len = newsize;
    strsptr->data = dataptr;
    return (void*)(charptr);
}

strs strs_splitbychar_tonew(char* str, char splitchar) {
    //first handle the edge cases:
    if (str == NULL) {
        strs output = strs_attrs_tonew((char**)NULL, 0);
        return output;
    }
    if (strcmp(str, "") == 0) {
        char** strptr = &str;
        strs output = strs_attrs_tonew(strptr, 1);
        return output;
    }
    if (splitchar == '\0') {
        char** strptr = &str;
        strs output = strs_attrs_tonew(strptr, 1);
        return output;
    }
    //now we know that str is not null and splitchar is not null.
    //first, we count the number of times splitchar appears in str.
    char* heapstr = strdup(str);
    int count = _str_char_count(heapstr, splitchar);
    //if count is zero, then we return a strs object with one string.
    if (count == 0) {
        char** strptr = &str;
        strs output = strs_attrs_tonew(strptr, 1);
        return output;
    }
    //now we know that count is positive.
    //we will create enough room for the char** dynamic array.
    void* voidptr = malloc(sizeof(char*) * (count+1));
    if (voidptr == NULL) {
        printf("errormessage");
        exit(1);
    }
    char** dataptr = (char**)voidptr;
    dataptr[0] = heapstr;
    int counttodate = 1;
    int len = strlen(heapstr);
    for (int j = 0; j < len; j++) {
        if (heapstr[j] == splitchar) {
            if (j != len - 1) {
                dataptr[counttodate] = heapstr + j + 1;
                counttodate++;
            }
            heapstr[j] = '\0';
        }
    }
    strs raw_output = strs_attrs_tonew(dataptr, counttodate);
    //then we will point to every position after the splitchar. This is the start of the new string.
    free(heapstr);
    return raw_output;
}

strs strs_from_splitfirststr_tonew(char* str, char* splitstr) {
    //we will first handle the edge cases.
    //if str is null, then we return a strs object with one string.
    if (str == NULL) {
        char** strptr = &str;
        strs output = strs_attrs_tonew(strptr, 1);
        return output;
    }
    //if str is zerostr, then we return a strs object with one string.
    if (strcmp(str, "") == 0) {
        char** strptr = &str;
        strs output = strs_attrs_tonew(strptr, 1);
        return output;
    }
    //if splitstr is null, then we return a strs object with the whole str.
    if (splitstr == NULL) {
        char** strptr = &str;
        strs output = strs_attrs_tonew(strptr, 1);
        return output;
    }
    //if splitstr is zerostr, then we return a strs object with the whole str.
    if (strcmp(splitstr, "") == 0) {
        char** strptr = &str;
        strs output = strs_attrs_tonew(strptr, 1);
        return output;
    }
    //now we know that str is not null and splitstr is not null.
    //get the first index of splitstr in str.
    int index = str_substr_index(str, splitstr);
    //if index is -1, then we return a strs object with the whole str.
    if (index == -1) {
        char** strptr = &str;
        strs output = strs_attrs_tonew(strptr, 1);
        return output;
    }
    if (index == 0) {
        //now we know that index is non-negative. If index is zero, then we return a strs object with two strs: the splitstr and the rest of the str.
        void* voidptr = malloc(sizeof(char) * (strlen(splitstr) + 1));
        if (voidptr == NULL) {
            printf("errormessage");
            exit(1);
        }
        char* fstword = (char*)voidptr;
        strcpy(fstword, splitstr);
        void* voidptr1 = malloc(sizeof(char) * (strlen(str + strlen(splitstr)) + 1));
        if (voidptr1 == NULL) {
            printf("errormessage");
            exit(1);
        }
        char* sndword = (char*)voidptr1;
        strcpy(sndword, str + strlen(splitstr));
        char* strptrs[2] = {fstword, sndword};
        strs output = strs_attrs_tonew(strptrs, 2);
        free(fstword);
        free(sndword);
        return output;
    }
    //break for now
    return (strs){NULL, 0};
}

void* strs_splitbychar_tobuff(void* inbuff, char* str, char splitchar) {
    //I can't even think to implement this right now.
    strs newstrs = strs_splitbychar_tonew(str, splitchar);
    void* outbuff = strs_copy_tobuff(inbuff, newstrs);
    strs_free(newstrs);
    return outbuff;
}

strs strs_splitbynchars_tonew(char* str, char* chars, int n) {
    return (strs){NULL, 0};
}

void* strs_splitbynchars_tobuff(void* inbuff, char* str, char* chars, int n) {
    return inbuff;
}

/*
*
*
*
*
*
*/

int _str_char_count(char* str, char c) {
    if ((str == NULL) || (c == '\0')) {
        return -1;
    }
    if (*str == '\0') {
        return 0;
    }
    int count = 0;
    for(int i = 0; i < strlen(str); i++) {
        if (str[i] == c) {
            count++;
        }
    }
    return count;
}



//strs utility functions
int PROTOSTRSSAMPLES = 5;
strs* strs_samples() {
    void* voidptr = malloc(sizeof(strs) * (PROTOSTRSSAMPLES));
    if (voidptr == NULL) {
        printf("can't create strs array");
        exit(1);
    }
    strs* strsarray = (strs*)voidptr;
    strsarray[0] = strs_attrs_tonew((char* []){"alpha", "beta", "gamma"}, 3);
    strsarray[1] = strs_attrs_tonew((char* []){"alpha", "beta", "gamma", "delta", "eta"}, 5);
    strsarray[2] = strs_attrs_tonew((char* []){""}, 1);
    strsarray[3] = strs_attrs_tonew((char* []){(char*)NULL, (char*)NULL}, 2);
    strsarray[4] = strs_attrs_tonew(NULL, 0);
    return strsarray;
}