#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "base.h"
#include "dstr.h"

const dstr DSTRNULL = (dstr){.stnd = {.__impl = 10, .len = 0, .data = NULL}};
const uint32 DSTR_MAX_GERMAN_BYTES = 12;

void check_dstrs(dstr tocheck) {
    assert(sizeof(dstr_stnd) == sizeof(dstr_germ));
    assert(sizeof(dstr_bloc) == sizeof(dstr_stnd));
    assert(tocheck.bloc.__impl == tocheck.stnd.__impl);
    assert(tocheck.bloc.__impl == tocheck.germ.__impl);
    assert(tocheck.bloc.__impl == tocheck.dstr_proto.__attrs);
    return;
}

/*PROPERTIES*/
variety         dstr_variety(dstr input){return proto_get_variety(input.dstr_proto);}
blocksize       dstr_blocksize(dstr input){return proto_get_blocksize(input.dstr_proto);}
implementation  dstr_implementation(dstr input){return proto_get_implementation(input.dstr_proto);}
localization    dstr_localization(dstr input){return proto_get_localization(input.dstr_proto);}

/*attrs-properties*/
char* dstr_data(dstr* pinput){
    assert(pinput != NULL);
    dstr input = *pinput;
    switch(dstr_implementation(input)){
        case(STANDARD) : return input.stnd.data;
        case(GERMAN) : return (char*)(((void*)(pinput)) + 4);
        case(BLOCK_IMPLEMENTION) : {
            if (input.bloc.__len == 0) {
                return NULL;
            } else {
                return input.bloc.data;
            }
        }
        case(NULL_IMPLEMENTATION) : return NULL;
        case(IMPLEMENTATION_ERROR) : return NULL;
        default: return NULL;
    }
}

/*boolean properties*/
/*implementations*/
int dstr_isgerm(dstr input){return proto_is_german(input.dstr_proto);}
int dstr_isbloc(dstr input){return proto_is_blockimpl(input.dstr_proto);}
int dstr_isstnd(dstr input){return proto_is_standard(input.dstr_proto);}
/*localizations*/
int dstr_isunspl(dstr input){return proto_is_unsplit(input.dstr_proto);}
int dstr_issplit(dstr input){return proto_is_split(input.dstr_proto);}
int dstr_isnonlo(dstr input){return proto_is_refr(input.dstr_proto);}
/*varieties*/
int dstr_isbuff(dstr input){return proto_is_buff(input.dstr_proto);}
int dstr_isrefr(dstr input){return proto_is_refr(input.dstr_proto);}
int dstr_isheap(dstr input){return proto_is_heap(input.dstr_proto);}

/*other properties*/
int dstr_isnull(dstr input){
    switch(dstr_implementation(input)){
        case(NULL_IMPLEMENTATION) : {printf("shouldn't have dstr null implementation.\n"); exit(1);}
        case(IMPLEMENTATION_ERROR) : {printf("dstr error implementation.\n"); exit(1);}
        case(STANDARD) : return (input.stnd.data == NULL);
        case(GERMAN) : return 0; //german strings cannot be null.
        case(BLOCK_IMPLEMENTION) : return (input.bloc.__len == 0 ? 1 : 0);
        default: return 0;
    }
}

int dstr_iserr(dstr input){
    switch(dstr_implementation(input)){
        case(IMPLEMENTATION_ERROR) : return 1;
        default: return 0;
    }
}

/*length and size properties*/
uint32  dstr_datasize(dstr input){
    switch(dstr_implementation(input)){
        case(STANDARD) : return (input.stnd.data == NULL) ? 0 : input.stnd.len + 1;
        case(GERMAN) : return 0;
        case(BLOCK_IMPLEMENTION) : return proto_get_blocksize(input.dstr_proto);
        case(NULL_IMPLEMENTATION) : return 0;
        case(IMPLEMENTATION_ERROR) : return 0;
        default: return 0;
    }
}

uint32 dstr_tailsize(dstr input){
    switch(dstr_implementation(input)){
        case(STANDARD) : return (input.stnd.data == NULL) ? 0 : input.stnd.len + 1;
        case(GERMAN) : return 0;
        case(BLOCK_IMPLEMENTION) : {
            if (dstr_isunspl(input)) {
                return proto_get_blocksize(input.dstr_proto) - sizeof(dstr_bloc);
            } else if (dstr_issplit(input)) {
                return proto_get_blocksize(input.dstr_proto);
            } else {
                return 0;
            }
        }
        case(NULL_IMPLEMENTATION) : return 0;
        case(IMPLEMENTATION_ERROR) : return 0;
        default: return 0;
    }
}

uint32  dstr_totalsize(dstr input) {
    switch(dstr_implementation(input)){
        case(STANDARD) : return sizeof(dstr_stnd) + dstr_datasize(input);
        case(GERMAN) : return sizeof(dstr_germ);
        case(BLOCK_IMPLEMENTION) : {
            if (dstr_localization(input) == UNSPLIT) {
                return proto_get_blocksize(input.dstr_proto);
            } else if (dstr_localization(input) == SPLIT) {
                return proto_get_blocksize(input.dstr_proto) + sizeof(dstr);
            } else {
                return 0;
            }
        }
        case(NULL_IMPLEMENTATION) : return sizeof(dstr);
        case(IMPLEMENTATION_ERROR) : return sizeof(dstr);
        default: return sizeof(dstr);
    }
}

//length and size properties

uint32  dstr_len(dstr input){
    switch(dstr_implementation(input)){
        case(STANDARD) : return input.stnd.len;
        case(GERMAN) : {char* ptr = input.germ.string; return strlen(ptr);}
        case(BLOCK_IMPLEMENTION) : return ((input.bloc.__len == 0) ? 0 : input.bloc.__len - 1);
        case(NULL_IMPLEMENTATION) : return 0;
        case(IMPLEMENTATION_ERROR) : return 0;
        default: return 0;
    }
}

//string properties
char dstr_nth(dstr input, uint32 nth, char defaultval){
    if ((nth >= dstr_len(input)) || (dstr_isnull(input))){
        return defaultval;
    } else if ((dstr_isgerm(input)) || (nth < 4)){
        char* start = input.germ.string; //this works for both german strings and non-german strings.
        return start[nth];
    } else {
        return input.stnd.data[nth];
    }
}

/*CREATE DSTR FROM CHAR*.*/

/*OPERATIONS*/
void dstr_stnd_printf(dstr_stnd input, int newline){
    printf("dstr: ");
    localization_printf(proto_get_localization((proto){input.__impl}));
    printf(" ");
    variety_printf(proto_get_variety((proto){input.__impl}));
    printf(", ");
    implementation_printf(proto_get_implementation((proto){input.__impl}));
    printf("; %s", input.data);
    if (newline) {
        printf("\n");
    }
}

void dstr_german_printf(dstr_germ input, int newline){
    printf("dstr: ");
    localization_printf(proto_get_localization((proto){input.__impl}));
    printf(" ");
    variety_printf(proto_get_variety((proto){input.__impl}));
    printf(", ");
    implementation_printf(proto_get_implementation((proto){input.__impl}));
    char* string = input.string;
    printf("; %s", string);
    if (newline) {
        printf("\n");
    }
}

void dstr_block_printf(dstr_bloc input, int newline){
    printf("dstr: ");
    localization_printf(proto_get_localization((proto){input.__impl}));
    printf(" ");
    variety_printf(proto_get_variety((proto){input.__impl}));
    printf("; blocksize: %u", proto_get_blocksize((proto){input.__impl}));
    printf("; %s", input.data);
    if (newline) {
        printf("\n");
    }
}

void dstr_null_printf(dstr input, int newline){
    printf("dstr: NULLOBJ; (null)");
    if (newline) {
        printf("\n");
    }
}

void dstr_printf(dstr input, int newline) {
    switch(dstr_implementation(input)){
        case(BLOCK_IMPLEMENTION) : dstr_block_printf(input.bloc, newline); return;
        case(GERMAN) : dstr_german_printf(input.germ, newline); return;
        case(NULL_IMPLEMENTATION): dstr_stnd_printf(input.stnd, newline); return;
        case(STANDARD): dstr_stnd_printf(input.stnd, newline); return;
        default: dstr_stnd_printf(input.stnd, newline); return;
    }
}

/*RELATIONSHIPS*/
int dstr_eq(dstr input1, dstr input2) {
    if (dstr_isnull(input1) && dstr_isnull(input2)) {return 1;}
    if (dstr_isnull(input1) || dstr_isnull(input2)) {return 0;}
    if (input1.dstr_proto.__attrs == 10) {printf("shouldn't have dstrnull;\n"); exit(1);}
    if (strcmp(dstr_data(&input1), dstr_data(&input2)) == 0) {
        printf("strings are equal\n");
        return 1;
    } else {
        printf("strings unequal\n");
        return 0;
    }
}

/*
HELPER FUNCTIONS
*/

static void __dstr_assign_at_german(dstr* input, char* data){
    char* germsite = input->germ.string;
    strcpy(germsite, data);
}

/*CREATION METHODS*/
    /*CREATE BY ATTRIBUTES*/
void* dstr_attrs_tobuff_unsplit(char* data, void* tail){
    assert(tail != NULL);
    dstr* output = (dstr*)tail;
    if (data == NULL) {
        output->dstr_proto = proto_from_lvi(UNSPLIT, BUFF, STANDARD);
        output->stnd.data = NULL;
        output->stnd.len = 0;
        return (void*)(output + 1);
    } else if (strlen(data) + 1 < DSTR_MAX_GERMAN_BYTES) {
        output->dstr_proto = proto_from_lvi(UNSPLIT, BUFF, GERMAN);
        char* ptr = output->germ.string;
        strcpy(ptr, data);
        return (void*)(output + 1);
    } else {
        uint32 str_index = 0;
        output->dstr_proto = proto_from_lvi(UNSPLIT, BUFF, STANDARD);
        char* charptr = (char*)(output + 1);
        output->stnd.data = charptr;
        //copy the first element because it could be '\0'.
        *charptr = data[str_index];
        while (data[str_index] != '\0') {
            str_index++;
            charptr[str_index] = data[str_index];
        }
        output->stnd.len = str_index;
        return (void*)(charptr + str_index + 1);
    }
}

void* dstr_attrs_tobuff_split(char* data, dstr* head, void* tail){
    assert(head != NULL);
    if (data == NULL) { //this should put a DSTRNULL in the head, and not use the tail at all.
        head->dstr_proto = proto_from_lvi(SPLIT, BUFF, STANDARD);
        head->stnd.data = NULL;
        head->stnd.len = 0;
        return tail;
    } else if (strlen(data) + 1 < DSTR_MAX_GERMAN_BYTES) { //this is if the chars are small enough to fit in a german string.
        head->dstr_proto = proto_from_lvi(SPLIT, BUFF, GERMAN);
        __dstr_assign_at_german(head, data);
        return tail;
    } else { //this is when you actually need the tail to store the strung.
        head->dstr_proto = proto_from_lvi(SPLIT, BUFF, STANDARD);
        head->stnd.data = tail;
        uint32 str_index = 0;
        char* chararray = (char*)tail;
        *chararray = data[str_index];
        while (data[str_index] != '\0') {
            str_index++;
            chararray[str_index] = data[str_index];
        }
        head->stnd.len = str_index;
        return (void*)(tail + str_index + 1);
    }
}

void* dstr_attrs_tobuff(char* data, dstr* head, void* tail){
    assert(tail != NULL);
    if (head == NULL) {
        tail = dstr_attrs_tobuff_unsplit(data, tail);
        return tail;
    } else {
        tail = dstr_attrs_tobuff_split(data, head, tail);
        return tail;
    }
}

void* dstr_attrs_toheap_split(char* data, dstr* head) {
    //this thing only returns null at  this point.
    if (data == NULL){
        head->dstr_proto = proto_from_lvi(SPLIT, HEAP, STANDARD);
        head->stnd.data = NULL;
        return NULL;
    }
    uint32 len = strlen(data) + 1;
    if (len < DSTR_MAX_GERMAN_BYTES) {
        head->dstr_proto = proto_from_lvi(SPLIT, HEAP, GERMAN);
        __dstr_assign_at_german(head, data);
    } else {
        head->dstr_proto = proto_from_lvi(SPLIT, HEAP, STANDARD);
        void* voidptr = malloc(sizeof(char) * len);
        if (voidptr == NULL) {
            printf("cannot perform dstr_attrs_toheap_split malloc.");
            exit(1);
        }
        head->stnd.data = (char*)voidptr;
        head->stnd.len = len - 1;
        strcpy(head->stnd.data, data);
    }
    return NULL;
}

void* dstr_attrs_toheap_unsplit(char* data, void* tail){
    //tail contains a pointer to a dstr on the heap. Therefore, tail is dstr**.
    dstr** heapptr = (dstr**)tail;
    /*NULL case*/
    if (data == NULL){
        void* voidptr = malloc(sizeof(dstr) * (1));
        if (voidptr == NULL) {
            printf("malloc error dstr_attrs_toheap_unsplit");
            exit(1);
        }
        *heapptr = (dstr*)voidptr;
        (*heapptr)->dstr_proto = proto_from_lvi(UNSPLIT, HEAP, STANDARD);
        (*heapptr)->stnd.data = NULL;
        return tail + sizeof(dstr*);
    }
    uint32 len = strlen(data) + 1;
    /*SMALL STRING CASE*/
    if (len < DSTR_MAX_GERMAN_BYTES){
        void* voidptr = malloc(sizeof(dstr) * (1));
        if (voidptr == NULL) {
            printf("malloc error dstr_attrs_toheap_unsplit german impl.");
            exit(1);
        }
        *heapptr = (dstr*)voidptr;
        (*heapptr)->dstr_proto = proto_from_lvi(UNSPLIT, HEAP, GERMAN);
        __dstr_assign_at_german(*heapptr, data);
        return tail + sizeof(dstr*);
    /*LARGE STRING CASE*/
    } else {
        void* voidptr = malloc(sizeof(dstr) * (1) + sizeof(char) * len);
        if (voidptr == NULL) {
            printf("malloc error dstr_attrs_toheap_unsplit german impl.");
            exit(1);
        }
        *heapptr = (dstr*)voidptr;
        (*heapptr)->dstr_proto = proto_from_lvi(UNSPLIT, HEAP, STANDARD);
        (*heapptr)->stnd.data = (char*)(*heapptr + 1);
        strcpy((*heapptr)->stnd.data, data);
        (*heapptr)->stnd.len = len - 1;
        return tail + sizeof(dstr*);
    }
}

void* dstr_attrs_toheap(char* data, dstr* head, void* tail) {
    assert (head != NULL || tail != NULL);
    if (head == NULL) {
        //if no head given, do the unsplit case on the tail.
        void* newtail = dstr_attrs_toheap_unsplit(data, tail);
        return newtail;
    } else {
        //if head is given, do the split case on the head.
        dstr_attrs_toheap_split(data, head);
        return tail;
    }
}

void* dstr_attrs_tobloc_split(char* data, dstr* head, void* tail, blocksize b) {
    assert(b >= PROTO_BLOC_START);
    assert((data == NULL) || (b >= strlen(data) + 1));
    head->dstr_proto = proto_from_lbsize(SPLIT, b);
    head->bloc.data = (char*)(tail);
    if (data == NULL) {
        head->bloc.__len = 0;
    } else {
        head->bloc.__len = strlen(data) + 1;
        strcpy(head->bloc.data, data);
    }
    return (tail + b);
}

void* dstr_attrs_tobloc_unsplit(char* data, void* tail, blocksize b) {
    assert(b >= PROTO_BLOC_START);
    assert((data == NULL) || (b >= strlen(data) + 1 + sizeof(dstr)));
    dstr* head = (dstr*)tail;
    void* newtail = tail +  sizeof(dstr);
    head->dstr_proto = proto_from_lbsize(UNSPLIT, b);
    head->bloc.data = (char*)newtail;
    if (data == NULL) {
        head->bloc.__len = 0;
    } else {
        head->bloc.__len = strlen(data) + 1;
        strcpy(head->bloc.data, data);
    }
    return tail + sizeof(char) * b;
}

void* dstr_attrs_tobloc(char* data, dstr* head, void* tail, blocksize b){
    assert(tail != NULL);
    if (head == NULL) {
        //do the unsplit case.
        void* newtail = dstr_attrs_tobloc_unsplit(data, tail, b);
        return newtail;
    } else {
        //do the split case.
        void* newtail = dstr_attrs_tobloc_split(data, head, tail, b);
        return newtail;
    }
}

dstr dstr_attrs_torefr(char* data) {
    dstr output;
    output.dstr_proto = proto_from_lvi(UNSPLIT, REFERENCE, STANDARD);
    output.stnd.data = data;
    return output;
}

void* dstr_from_attrs(char* data, method m) {
    dstr* dstrtape = (dstr*)m.tail;
    instruction instr = method_instruction(m);
    switch (instr) {
        case(TOREF) : {
            if (m.head != NULL) {
                printf("cannot create reference without head resource.");
                return NULL;
            } else {
                *dstrtape = dstr_attrs_torefr(data);
                return (void*)(m.tail); //return the unused resource. Could be null however, at which point you won't have error checking.
            }
        }
        case(TOHEAP) : {
            return dstr_attrs_toheap(data, dstrtape, m.tail);
        }
        case(TOBUFF) : {
            return dstr_attrs_tobuff(data, dstrtape, m.tail);
        }
        case(TOBLOCK) : {
            return dstr_attrs_tobloc(data, dstrtape, m.tail, method_blocksize(m));
        }
        case(INPLACE) : {
            printf("cannot create dstr from method with instruction %d", instr);
            return NULL;
        }
        case(TONULL) : {
            *dstrtape = DSTRNULL;
            return (void*)(m.tail);
        }
        case(INST_ERROR) : {
            printf("triggered an error for dstr_from_attrs.\n");
            return NULL;
        }
        default : {
            printf("cannot create dstr from method with instruction %d", instr);
            return NULL;
        }
    }
}

    /*CREATE BY COPYING A DSTR*/

void* dstr_copy_tobuff_split(dstr input, dstr* head, void* tail) {
    assert((tail != NULL) && (head != NULL));
    if (dstr_isnull(input)) {
        head->dstr_proto = proto_from_lvi(SPLIT, BUFF, STANDARD);
        head->stnd.data = NULL;
        head->stnd.len = 0;
        return tail;
    } else if (dstr_len(input) + 1 < DSTR_MAX_GERMAN_BYTES) {
        head->dstr_proto = proto_from_lvi(SPLIT, BUFF, GERMAN);
        __dstr_assign_at_german(head, dstr_data(&input));
        return tail;
    } else {
        head->dstr_proto = proto_from_lvi(SPLIT, BUFF, STANDARD);
        head->stnd.data = tail;
        head->stnd.len = dstr_len(input);
        strcpy(head->stnd.data, dstr_data(&input));
        return (void*)(tail + dstr_len(input) + 1);
    }

}

void* dstr_copy_tobuff_unsplit(dstr input, void* tail) {
    assert(tail != NULL);
    if (dstr_isnull(input)) {
        dstr* output = (dstr*)tail;
        output->dstr_proto = proto_from_lvi(UNSPLIT, BUFF, STANDARD);
        output->stnd.data = NULL;
        output->stnd.len = 0;
        return (void*)(output + 1);
    } else if (dstr_len(input) + 1 < DSTR_MAX_GERMAN_BYTES) {
        dstr* output = (dstr*)tail;
        output->dstr_proto = proto_from_lvi(UNSPLIT, BUFF, GERMAN);
        __dstr_assign_at_german(output, dstr_data(&input));
        return (void*)(output + 1);
    } else {
        dstr* output = (dstr*)tail;
        output->dstr_proto = proto_from_lvi(UNSPLIT, BUFF, STANDARD);
        output->stnd.data = (char*)(output + 1);
        output->stnd.len = dstr_len(input);
        strcpy(output->stnd.data, dstr_data(&input));
        return (void*)(output + 1) + sizeof(char) * (dstr_len(input) + 1);
    }
}

void* dstr_copy_tobuff(dstr input, dstr* head, void* tail) {
    assert(tail != NULL);
    if (head == NULL) {
        return dstr_copy_tobuff_unsplit(input, tail);
    } else {
        return dstr_copy_tobuff_split(input, head, tail);
    }
}

void* dstr_copy_toheap_split(dstr input, dstr* head) {
    //still don't have a good return value for this one.
    if (dstr_isnull(input)) {
        head->dstr_proto = proto_from_lvi(SPLIT, HEAP, STANDARD);
        head->stnd.data = NULL;
        return NULL;
    } else if (dstr_len(input) + 1 < DSTR_MAX_GERMAN_BYTES) {
        head->dstr_proto = proto_from_lvi(SPLIT, HEAP, GERMAN);
        __dstr_assign_at_german(head, dstr_data(&input));
        return NULL;
    } else {
        head->dstr_proto = proto_from_lvi(SPLIT, HEAP, STANDARD);
        void* voidptr = malloc(sizeof(char) * (dstr_len(input) + 1));
        if (voidptr == NULL) {
            printf("malloc error dstr_copy_toheap_split");
            exit(1);
        }
        head->stnd.data = (char*)voidptr;
        head->stnd.len = dstr_len(input);
        strcpy(head->stnd.data, dstr_data(&input));
        return NULL;
    }
}

void* dstr_copy_toheap_unsplit(dstr input, void* tail) {
    dstr** heapptrs = (dstr**)tail;
    if (dstr_isnull(input)) {
        void* voidptr = malloc(sizeof(dstr) * (1));
        if (voidptr == NULL) {
            printf("malloc error dstr_copy_toheap_unsplit");
            exit(1);
        }
        *heapptrs = (dstr*)voidptr;
        (*heapptrs)->dstr_proto = proto_from_lvi(UNSPLIT, HEAP, STANDARD);
        (*heapptrs)->stnd.data = NULL;
        return tail + sizeof(dstr*);
    } else if (dstr_len(input) + 1 < DSTR_MAX_GERMAN_BYTES) {
        void* voidptr = malloc(sizeof(dstr) * (1));
        if (voidptr == NULL) {
            printf("malloc error dstr_copy_toheap_unsplit");
            exit(1);
        }
        *heapptrs = (dstr*)voidptr;
        (*heapptrs)->dstr_proto = proto_from_lvi(UNSPLIT, HEAP, GERMAN);
        __dstr_assign_at_german(*heapptrs, dstr_data(&input));
        return tail + sizeof(dstr*);
    } else {
        void* voidptr = malloc(sizeof(dstr) * (1) + sizeof(char) * (dstr_len(input) + 1));
        if (voidptr == NULL) {
            printf("malloc error dstr_copy_toheap_unsplit");
            exit(1);
        }
        *heapptrs = (dstr*)voidptr;
        (*heapptrs)->dstr_proto = proto_from_lvi(UNSPLIT, HEAP, STANDARD);
        (*heapptrs)->stnd.data = (char*)(*heapptrs + 1);
        (*heapptrs)->stnd.len = dstr_len(input);
        strcpy((*heapptrs)->stnd.data, dstr_data(&input));
        return tail + sizeof(dstr*);
    }
}

void* dstr_copy_toheap(dstr input, dstr* head, void* tail) {
    assert((head != NULL) || (tail != NULL));
    if (head == NULL) {
        return dstr_copy_toheap_unsplit(input, tail);
    } else {
        return dstr_copy_toheap_split(input, head);
    }
}

void* dstr_copy_tobloc_split(dstr input, dstr* head, void* tail, blocksize b) {
    assert(b >= PROTO_BLOC_START);
    assert((dstr_len(input) + 1 < b));
    head->dstr_proto = proto_from_lbsize(SPLIT, b);
    head->bloc.data = (char*)tail;
    if (dstr_isnull(input)) {
        head->bloc.__len = 0;
    } else {
        head->bloc.__len = dstr_len(input) + 1;
        strcpy(head->bloc.data, dstr_data(&input));
    }
    return (tail + sizeof(char) * b);
}

void* dstr_copy_tobloc_unsplit(dstr input, void* tail, blocksize b) {
    assert(b >= PROTO_BLOC_START);
    assert((dstr_len(input) + 1 + sizeof(dstr) < b) || (dstr_isnull(input)));
    dstr* head = (dstr*)tail;
    void* newtail = tail + sizeof(dstr);
    head->dstr_proto = proto_from_lbsize(UNSPLIT, b);
    head->bloc.data = (char*)newtail;
    if (dstr_isnull(input)){
        head->bloc.__len = 0;
    } else {
        head->bloc.__len = dstr_len(input) + 1;
        strcpy(head->bloc.data, dstr_data(&input));
    }
    return tail + sizeof(char) * b;
}

void* dstr_copy_tobloc(dstr input, dstr* head, void* tail, blocksize b) {
    assert(tail != NULL);
    if (head == NULL) {
        return dstr_copy_tobloc_unsplit(input, tail, b);
    } else {
        return dstr_copy_tobloc_split(input, head, tail, b);
    }
}

dstr dstr_copy_torefr(dstr input) {
    printf("dstr_copy_torefr NOT IMPLEMENTED\n");
    return DSTRNULL;
}

void* dstr_from_copy(dstr input, method m) {
    printf("dstr_from_copy NOT IMPLEMENTED\n");
    return NULL;
}

    /*CREATE BY CONCATINATING TWO DSTRS*/

//both null = NULL
//one null = copy the other.
//neither null = create a new dstr that puts first then second.

/*case 1: neither input is null.*/
static void* ___cat2_stndimpl_unsafe(variety v, localization l, dstr input1, dstr input2, dstr* head, void* tail) {
    //this is the case where both inputs are not null.
    head->dstr_proto = proto_from_lvi(l, v, STANDARD);
    head->stnd.data = (char*)tail;
    uint32 len1 = dstr_len(input1);
    uint32 len2 = dstr_len(input2);
    char* ptr1 = dstr_data(&input1);
    char* ptr2 = dstr_data(&input2);
    head->stnd.len = len1 + len2;
    strcpy(head->stnd.data, ptr1);
    assert(head->stnd.data[len1] == '\0');
    strcpy(head->stnd.data + len1, ptr2);
    return (void*)(tail + len1 + len2 + 1);
}

static void* ___cat2_germimpl_unsafe(variety v, localization l, dstr input1, dstr input2, dstr* head, void* tail) {
    //this is the case where both inputs are not null.
    head->dstr_proto = proto_from_lvi(l, v, GERMAN);
    char* germptr = head->germ.string; //array decay to pointer
    uint32 len1 = dstr_len(input1);
    uint32 len2 = dstr_len(input2);
    char* ptr1 = dstr_data(&input1);
    char* ptr2 = dstr_data(&input2);
    strcpy(germptr, ptr1);
    assert(germptr[len1] == '\0');
    strcpy(germptr + len1, ptr2);
    return tail;
}

/*three cases: one null, both null, neither null.*/

static void* __cat2_neithernull(variety v, localization l, dstr input1, dstr input2, dstr* head, void* tail) {
    if (dstr_len(input1) + dstr_len(input2) + 1 < DSTR_MAX_GERMAN_BYTES) {
        return ___cat2_germimpl_unsafe(v, l, input1, input2, head, tail);
    } else {
        return ___cat2_stndimpl_unsafe(v, l, input1, input2, head, tail);
    }
}

static void* ___cat2_if_one_is_null(variety v, localization l, dstr input, dstr* head, void* tail){
    void* output = dstr_copy_tobuff(input, head, tail);
    implementation impl = proto_get_implementation(head->dstr_proto);
    head->dstr_proto = proto_from_lvi(l, v, impl); //overwrite the v and l. (may not be a buffer).
    return output;
}

static void* ___cat2_if_both_null(variety v, localization l, dstr* head, void* tail) {
    //this is the case where both inputs are not null.
    head->dstr_proto = proto_from_lvi(l, v, STANDARD);
    head->stnd.data = NULL;
    head->stnd.len = 0;
    return (void*)(tail);
}

static void* _cat2_unsafe(variety v, localization l, dstr input1, dstr input2, dstr* head, void* tail) {
    uint32 swi = 1*(dstr_isnull(input1)) + 2*(dstr_isnull(input2));
    switch(swi) {
        case(0): return __cat2_neithernull(v, l, input1, input2, head, tail);
        case(1): return ___cat2_if_one_is_null(v, l, input2, head, tail);
        case(2): return ___cat2_if_one_is_null(v, l, input1, head, tail);
        case(3): return ___cat2_if_both_null(v, l, head, tail);
        default: printf("error in _cat2_unsafe"); exit(1);
    }
}

/*on buffer.*/
void* dstr_cat2_tobuff_split(dstr input1, dstr input2, dstr* head, void* tail) {
    /*--------conditions--------*/
    assert((tail != NULL) && (head != NULL));
    /*--------operations--------*/
    return _cat2_unsafe(BUFF, SPLIT, input1, input2, head, tail);
}

void* dstr_cat2_tobuff_unsplit(dstr input1, dstr input2, void* tail) {
    assert(tail != NULL);
    dstr* head = (dstr*)tail;
    void* newtail = tail + sizeof(dstr);
    void* output = dstr_cat2_tobuff_split(input1, input2, head, newtail);
    return output;
}

void* dstr_cat2_tobuff(dstr input1, dstr input2, dstr* head, void* tail) {
    assert(tail != NULL);
    if (head == NULL) {
        return dstr_cat2_tobuff_unsplit(input1, input2, tail);
    } else {
        return dstr_cat2_tobuff_split(input1, input2, head, tail);
    }
}

/*HEAP CREATION METHODS*/

void* dstr_cat2_toheap_split(dstr input1, dstr input2, dstr* head) {
    printf("dstr_cat2_toheap_split NOT IMPLEMENTED\n");
    return NULL;
}

void* dstr_cat2_toheap_unsplit(dstr input1, dstr input2, void* tail) {
    printf("dstr_cat2_toheap_unsplit NOT IMPLEMENTED\n");
    return NULL;
}

void* dstr_cat2_toheap(dstr input1, dstr input2, dstr* head, void* tail) {
    printf("dstr_cat2_toheap NOT IMPLEMENTED\n");
    return NULL;
}

void* dstr_cat2_tobloc_split(dstr input1, dstr input2, dstr* head, void* tail, blocksize b) {
    printf("dstr_cat2_tobloc_split NOT IMPLEMENTED\n");
    return NULL;
}

void* dstr_cat2_tobloc_unsplit(dstr input1, dstr input2, void* tail, blocksize b) {
    printf("dstr_cat2_tobloc_unsplit NOT IMPLEMENTED\n");
    return NULL;
}

void* dstr_cat2_tobloc(dstr input1, dstr input2, dstr* head, void* tail, blocksize b) {
    printf("dstr_cat2_tobloc NOT IMPLEMENTED\n");
    return NULL;
}

dstr dstr_cat2_torefr(dstr input1, dstr input2) {
    printf("dstr_cat2_torefr NOT IMPLEMENTED\n");
    return DSTRNULL;
}

void* dstr_from_cat2(dstr input1, dstr input2, method m) {
    printf("dstr_from_cat2 NOT IMPLEMENTED\n");
    return NULL;
}


/*FREE DSTR*/
void dstr_free(dstr* input) {
    //the only thing that a dstr is responsible for memory-wise if
    //if its data are on a heap or if it is itself on the heap.
    //if neither of those are true, then the caller or user is responsible for knowing
    //what to do with the memory.
    if (dstr_isheap(*input) && (dstr_issplit(*input))) {
        free(dstr_data(input));
    } else if (dstr_isheap(*input) && (dstr_isunspl(*input))) {
        free(input);
    } else {
        return;
    }
}