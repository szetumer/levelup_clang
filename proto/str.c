#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "str.h"
#include "base.h"

str str_copy_tonew(str input) {
    if (input == NULL) {
        return NULL;
    }
    str newstr = strdup(input);
    return newstr;
}

void* str_copy_tobuff(void* inbuff, str input) {
    char** newstr = (char**)inbuff;
    if (input == NULL) {
        *newstr = NULL;
        printf("Copying null onto buffer.\n");
        void* outbuff = (void*)(newstr + 1);
        return outbuff;
    }
    *newstr = (str)(newstr + 1);
    str charptr = (str)(newstr + 1);
    strcpy(charptr, input);
    void* outbuff = (void*)(charptr + (strlen(charptr) + 1)*sizeof(char));
    return outbuff;
}

str str_copy_toref(str input) {
    return input;
}

void str_reverse_inplace(str* inputptr) {
    if (inputptr == NULL) {
        return;
    } else if (*inputptr == NULL) {
        return;
    } else if (**inputptr == '\0') {
        return;
    }
    str input = *inputptr;
    int len = strlen(input);
    for(int i = 0; i < len/2; i++) {
        char temp = input[i];
        input[i] = input[len - i - 1];
        input[len - i - 1] = temp;
    }
    return;
}

str str_reverse_tonew(str input) {
    if (input == NULL) {
        return NULL;
    }
    if (*input == '\0') {
        return str_copy_tonew(input);
    }
    int len = strlen(input);
    str newstr = (str)malloc(sizeof(char) * (len + 1));
    if (newstr == NULL) {
        printf("couldn't make the new string");
        exit(1);
    }
    for(int i = 0; i < len; i++) {
        newstr[i] = input[len - i - 1];
    }
    newstr[len] = '\0';
    return newstr;
}

void* str_reverse_tobuff(void* inbuff, str input) {
    if (input == NULL) {
        str* newstr = (str*)inbuff;
        *newstr = NULL;
        void* outbuff = (void*)(newstr + sizeof(str));
        return outbuff;
    }
    if (*input == '\0') {
        return str_copy_tobuff(inbuff, input);
    }
    int len = strlen(input);
    str* newstr = (str*)inbuff;
    str charptr = (str)(newstr + 1);
    for(int i = 0; i < len; i++) {
        charptr[i] = input[len - i - 1];
    }
    charptr[len] = '\0';
    *newstr = charptr;
    void* outbuff = (void*)(charptr + (len + 1)*sizeof(char));
    return outbuff;
}

int str_substr_index(char* str, char* substr) {
    if ((str == NULL) || (substr == NULL)) {
        return -1;
    }
    if ((*str == '\0') || (*substr == '\0')) {
        return -1;
    }
    int str_len = strlen(str);
    int substr_len = strlen(substr);
    if (substr_len > str_len) {
        return -1;
    }
    for(int i = 0; i < str_len - substr_len + 1; i++) {
        if (strncmp(str + i, substr, substr_len) == 0) {
            return i;
        }
    }
    return -1;
}

typedef enum currently_in {
    START,
    EVALING_WHITESPACE,
    EVALING_LEADINGZEROES,
    EVALING_SIGN,
    EVALING_FIRSTDIGIT,
    EVALING_NONFIRSTDIGIT,
    REPORTING_ERROR,
    DONE,
} currently_in;

typedef struct statemachine {
    int             currentindex;
    int             val;
    int             exists;
    int             valence;
    currently_in    currentstate;
} statemachine;

int __char_is_whitespace(char c) {
    return ((c == ' ') || (c == '\t'));
}

int __char_is_anydigit(char c) {
    return ((c >= '0') && (c <= '9'));
}

int __char_is_nonzerodigit(char c) {
    return ((c >= '1') && (c <= '9'));
}

int __chardigitval(char c) {
    if (!__char_is_anydigit(c)) {
        return -1;
    }
    int val = (int)(c - '0');
    return val;
}

int __char_is_zero(char c) {
    return (c == '0');
}

int __char_is_sign(char c) {
    return ((c == '-') || (c == '+'));
}

int __char_is_alpha(char c) {
    return (((c >= 'a') && (c <= 'z')) || ((c >= 'A') && (c <= 'Z')));
}

char sm_get_next_char(statemachine* sm, char* str){
    int next_index = sm->currentindex + 1;
    if (next_index > strlen(str)) {
        printf("went beyond reader");
        sm->currentstate = REPORTING_ERROR;
        return '\0';
    } else if (next_index == strlen(str)) {
        sm->currentstate = DONE;
        return '\0';
    } else {
        return str[next_index];
    }
}

//if you're in the start state, implement this.
void sm_start_update(statemachine* sm, char next_char) {
    if (__char_is_whitespace(next_char)) {
        sm->currentstate = EVALING_WHITESPACE;
        sm->currentindex++;
    } else if (__char_is_zero(next_char)) {
        sm->currentstate = EVALING_LEADINGZEROES;
        sm->currentindex++;
    } else if (__char_is_sign(next_char)) {
        sm->currentstate = EVALING_SIGN;
        if (next_char == '+') {
            sm->valence = 1;
        } else {
            sm->valence = -1;
        }
        sm->currentindex++;
    } else if (__char_is_nonzerodigit(next_char)) {
        sm->currentstate = EVALING_FIRSTDIGIT;
        sm->val = __chardigitval(next_char);
        sm->currentindex++;
        sm->valence = 1;
        sm->exists = 1;
    } else {
        sm->currentstate = REPORTING_ERROR;
        sm->currentindex++;
    }
}

void sm_evalingwhitespace_update(statemachine* sm, char next_char) {
    if (__char_is_whitespace(next_char)) {
        sm->currentstate = EVALING_WHITESPACE;
        sm->currentindex++;
    } else if (__char_is_zero(next_char)) {
        sm->currentstate = EVALING_LEADINGZEROES;
        sm->currentindex++;
    } else if (__char_is_sign(next_char)) {
        sm->currentstate = EVALING_SIGN;
        if (next_char == '+') {
            sm->valence = 1;
        } else {
            sm->valence = -1;
        }
        sm->currentindex++;
    } else if (__char_is_nonzerodigit(next_char)) {
        sm->currentstate = EVALING_FIRSTDIGIT;
        sm->val = __chardigitval(next_char);
        sm->currentindex++;
        sm->valence = 1;
        sm->exists = 1;
    } else {
        sm->currentstate = REPORTING_ERROR;
        sm->currentindex++;
    }
}

void sm_evaling_leadingzeroes_update(statemachine* sm, char next_char) {
    if (__char_is_whitespace(next_char)) {
        sm->currentstate = DONE; //the value is actually zero because we have "    0    something else".
        sm->exists = 1;
        sm->val = 0;
        sm->currentindex++;
    } else if (__char_is_zero(next_char)) {
        sm->currentstate = EVALING_LEADINGZEROES;
        sm->currentindex++;
    } else if (__char_is_sign(next_char)) {
        sm->currentstate = REPORTING_ERROR;
        sm->currentindex++;
    } else if (__char_is_nonzerodigit(next_char)) {
        sm->currentstate = EVALING_FIRSTDIGIT;
        sm->val = __chardigitval(next_char);
        sm->currentindex++;
        sm->valence = 1;
        sm->exists = 1;
    } else {
        sm->currentstate = REPORTING_ERROR;
        sm->currentindex++;
    }
}

void sm_evalingsign_update(statemachine* sm, char next_char) {
    if (__char_is_whitespace(next_char)) {
        sm->currentstate = REPORTING_ERROR;
        sm->currentindex++;
    } else if (__char_is_zero(next_char)) {
        sm->currentstate = EVALING_LEADINGZEROES;
        sm->currentindex++;
    } else if (__char_is_sign(next_char)) {
        sm->currentstate = REPORTING_ERROR;
        sm->currentindex++;
    } else if (__char_is_nonzerodigit(next_char)) {
        sm->currentstate = EVALING_FIRSTDIGIT;
        sm->val = (sm->val) * 10 + (sm->valence) * __chardigitval(next_char);
        sm->currentindex++;
        sm->exists = 1;
    } else {
        sm->currentstate = REPORTING_ERROR;
        sm->currentindex++;
    }
}

void sm_evalingfirstdigit_update(statemachine* sm, char next_char) {
    //we've already seen the first digit. So the number must exist.
    if (sm->exists == 0) {
        sm->currentstate = REPORTING_ERROR;
        sm->currentindex++;
    } else if (__char_is_whitespace(next_char)) {
        sm->currentstate = DONE;
        sm->currentindex++;
    } else if (__char_is_anydigit(next_char)) {
        sm->currentstate = EVALING_NONFIRSTDIGIT;
        sm->val = (sm->val) * 10 + (sm->valence) * __chardigitval(next_char);
        sm->currentindex++;
    } else if (__char_is_sign(next_char)) {
        sm->currentstate = DONE;
        sm->currentindex++;
    } else {
        sm->currentstate = DONE;
        sm->currentindex++;
    }
}

void sm_evaling_nonfirstdigit_update(statemachine* sm, char next_char) {
    //we've already seen the first digit. So the number must exist.
    if (sm->exists == 0) {
        sm->currentstate = REPORTING_ERROR;
        sm->currentindex++;
    } else if (__char_is_whitespace(next_char)) {
        sm->currentstate = DONE;
        sm->currentindex++;
    } else if (__char_is_anydigit(next_char)) {
        sm->currentstate = EVALING_NONFIRSTDIGIT;
        sm->val = (sm->val) * 10 + (sm->valence) * __chardigitval(next_char);
        sm->currentindex++;
    } else if (__char_is_sign(next_char)) {
        sm->currentstate = DONE;
        sm->currentindex++;
    } else {
        sm->currentstate = DONE;
        sm->currentindex++;
    }
}

void update_statemachine(statemachine* sm, char* str) {
    char next_char = sm_get_next_char(sm, str);
    if (sm->currentstate == START) {
        sm_start_update(sm, next_char);
    } else if (sm->currentstate == EVALING_WHITESPACE) {
        sm_evalingwhitespace_update(sm, next_char);
    } else if (sm->currentstate == EVALING_LEADINGZEROES) {
        sm_evaling_leadingzeroes_update(sm, next_char);
    } else if (sm->currentstate == EVALING_SIGN){
        sm_evalingsign_update(sm, next_char);
    } else if (sm->currentstate == EVALING_FIRSTDIGIT) {
        sm_evalingfirstdigit_update(sm, next_char);
    } else if (sm->currentstate == EVALING_NONFIRSTDIGIT) {
        sm_evaling_nonfirstdigit_update(sm, next_char);
    } else if (sm->currentstate == REPORTING_ERROR) {
        return;
    } else if (sm->currentstate == DONE) {
        return;
    } else {
        sm->currentstate = REPORTING_ERROR;
        return;
    }
}


int str_str2int(char* str, int default_val) {
    statemachine sm = {-1, 0, 0, 0, START};
    //rewrite this
    while ((sm.currentstate != DONE) && (sm.currentstate != REPORTING_ERROR)) {
        update_statemachine(&sm, str);
    }
    if (sm.currentstate == REPORTING_ERROR) {
        return default_val;
    } else if ((sm.currentstate == DONE) && (sm.exists == 1)) {
        return sm.val;
    } else if ((sm.currentstate == DONE) && (sm.exists == 0)) {
        return default_val; //this may need to be zero, but not sure.
    } else {return default_val;}
}

str str_slice_tonew(str input, int lowerbound, int upperbound) {
    if (input == NULL) {
        str output = NULL;
        return output;
    }
    if (lowerbound >= upperbound) {
        str output = NULL;
        return output;
    }
    if (lowerbound < 0) {
        lowerbound = 0;
    }
    if (upperbound > strlen(input)) {
        upperbound = strlen(input);
    }
    int newsize = upperbound - lowerbound;
    if (newsize <= 0) {
        str output = NULL;
        return output;
    }
    str lowercharptr = input + lowerbound;
    str output = strndup(lowercharptr, newsize);
    return output;
}

void* str_slice_tobuff(void* inbuff, str input, int lowerbound, int upperbound) {
    //remember, this gives a str* (which is a char*).
    if (input == NULL) {
        return str_copy_tobuff(inbuff, NULL);
    }
    if (lowerbound >= upperbound) {
        return str_copy_tobuff(inbuff, NULL);
    }
    lowerbound = (lowerbound < 0) ? 0 : lowerbound;
    upperbound = (upperbound > strlen(input)) ? strlen(input) : upperbound;
    if (upperbound <= lowerbound) {
        return str_copy_tobuff(inbuff, NULL);
    }
    str lowercharptr = input + lowerbound;
    if (upperbound == strlen(input)) {
        void* outbuff = str_copy_tobuff(inbuff, lowercharptr);
        return outbuff;
    }
    int newsize = upperbound - lowerbound;
    if (newsize <= 0) {
        return str_copy_tobuff(inbuff, NULL);
    }
    str* newstr = (str*)inbuff;
    str strstart = (char*)(newstr + 1);
    strncpy(strstart, input, newsize);
    strstart[newsize] = '\0';
    *newstr = strstart;
    void* outbuff = (void*)(strstart + (newsize + 1)*sizeof(char));
    return outbuff;
}

str str_delwhitespace_tonew(str input) {
    if (input == NULL) {
        char* output = (char*)NULL;
        return output;
    }
    char* output = strdup(input);
    if (*input == '\0') {
        return output;
    }
    unsigned int copy_gap = 0;
    for(int i = 0; i < strlen(input); i++) {
        //if the ith + copy gap is at the end, copy the symbol, and you're done.
        if (input[i + copy_gap] == '\0') {
            output[i] = '\0';
            return output;
        } else if (input[i + copy_gap] == ' ') {
            //if the thing to copy is whitespace, increase the copy_gap and try again.
            //but don't copy anything because you haven't found a nonwhitespace character yet.
            copy_gap++;
            i--;
            continue;
        } else {
            //if the thing isn't the end, and isn't a blank, you can copy this into the correct space.
            output[i] = input[i + copy_gap];
            continue;
        }
    }
    return input;
}

void* str_delwhitespace_tobuff(void* inbuff, char* input) {
    //this needs to be optimized. Currently uses malloc.
    char* output = str_delwhitespace_tonew(input);
    void* outbuff = str_copy_tobuff(inbuff, output);
    free(output);
    return outbuff;
}

int str_substr_firstindex(char* input, char* substr) {
    return 1;
    
}

int str_substr_lastindex(char* input, char* substr) {
    return 1;
}

/*
PROPERTIES
*/

unsigned int str_len(str input) {
    if (input == NULL) {
        return 0;
    }
    return strlen(input);
}

char str_nth(str input, unsigned int n, char defaultval) {
    if (input == NULL) {
        return defaultval;
    }
    if (n >= strlen(input)) {
        return defaultval;
    }
    return input[n];
}

unsigned int str_memsize(str input) {
    if (input == NULL) {
        return sizeof(str);
    }
    return sizeof(str) + sizeof(char) * (strlen(input) + 1);
}

int str_contains_alpha(str input) {
    for(int i = 0; i < strlen(input); i++) {
        if (__char_is_alpha(input[i])) {
            return 1;
        }
    }
    return 0;
}

int str_contains_num(str input) {
    for(int i = 0; i < strlen(input); i++) {
        if (__char_is_anydigit(input[i])) {
            return 1;
        }
    }
    return 0;
}



/*
RELATIONSHIPS
*/

int str_eq(str str1, str str2) {
    if ((str1 == NULL) && (str2 == NULL)) {
        return 1;
    } else if ((str1 == NULL) || (str2 == NULL)) {
        return 0;
    } else if (strcmp(str1, str2) == 0) {
        return 1;
    } else {
        return 0;
    }
}


/*
CRITERIA
*/
int str_isnull(str input) {
    return (input == NULL);
}

int str_isemptystr(str input) {
    return (*input == '\0');
}