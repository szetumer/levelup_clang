#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "base.h"

/*INSTRUCTION FUNCTIONS*/
void
instruction_printf(instruction inst){
    switch(inst){
        case(INST_ERROR): printf("INST_ERROR"); return;
        case(TOREF): printf("TOREF"); return;
        case(TOHEAP): printf("TOHEAP"); return;
        case(TOBUFF): printf("TOBUFF"); return;
        case(TOBLOCK): printf("TOBLOCK"); return;
        case(INPLACE): printf("INPLACE"); return;
        default: printf("errorr in instruction printf."); exit(1);
    }
}

/*METHOD FUNCTIONS*/
instruction
method_instruction(method m){
    switch(m.inst){
        case(0): return INST_ERROR;
        case(3): return TOREF;
        case(4): return TOHEAP;
        case(5): return TOHEAP;
        case(6): return TOBUFF;
        case(7): return TOBUFF;
        default: return TOBLOCK;
        }
    }

blocksize
method_blocksize(method m){
    switch((int)(m.inst < 8)){
        case(1): return 0;
        case(0): return (m.inst - (m.inst % 2));
        default: printf("method_get_blocksize error."); exit(1);
    }
}

method
method_with_blocksize(void* head, void* tail, blocksize n){
    switch((int)(n < 8)){
        case(1) : printf("blocksize cannot be less than 8"); exit(1);
        case(0) : {
            switch((int)(head==NULL)){ //when it is unsplit, it's even, when it's split, it's odd.
                case(1) : {private_inst inst = (n - (n % 2)); return (method){.head = head, .tail = tail, .inst = inst};}
                case(0) : {private_inst inst = (n - (n % 2) + 1); return (method){.head = head, .tail = tail, .inst = inst};}
                default: {printf("error in method with blocksize"); exit(1);}
            }
        }
        default : {printf("error: method_with_blocksize"); exit(1);}
    }
}

method
method_with_instruction(void* head, void* tail, instruction inst){
    uint32 is_split = (uint32)(head != NULL);
    uint32 private_instruction_base_value;
    switch(inst){ //all instructions are at less than 8 values. value 2 doesn't have any existence here..
        case(TOREF) : private_instruction_base_value = 3; break;
        case(TOHEAP) : private_instruction_base_value = 4 + is_split; break;
        case(TOBUFF) : private_instruction_base_value = 6 + is_split; break;
        case(INST_ERROR) : private_instruction_base_value = 0; break;
        case(TOBLOCK) : {printf("cannot create method with toblock instruction"); exit(1);}
        case(INPLACE) : private_instruction_base_value = 1; break;
        default : {printf("error in method_with_insturction function."); exit(1);}
    }
    return (method){.head = head, .tail = tail, .inst = private_instruction_base_value};
}

void
method_printf(method m){
    printf("head: %p; tail: %p; instructions:", m.head, m.tail);
    instruction inst = method_instruction(m);
    instruction_printf(inst);
}

/*PROTO OBJECT*/
//constants
const uint32  PROTO_BUFF_START = 2;
const uint32  PROTO_HEAP_START = 6;
const uint32  PROTO_CONS_START = 10;
const uint32  PROTO_BLOC_START = 16;
const proto   PROTOERROR = (proto){.__attrs = 0};
const proto   PROTONULL = (proto){.__attrs = 10};

instruction blocksize_to_instruction(blocksize b) {
    if (b < PROTO_BLOC_START) {
        printf("cannot provide blocksize smaller than %d", PROTO_BLOC_START);
        exit(1);
    }
    return (instruction)(b -  b % 2);
}

instruction instruction_from_blocksize(blocksize b) {
    if (b < PROTO_BLOC_START) {
        printf("cannot provide blocksize smaller than %d", PROTO_BLOC_START);
        exit(1);
    }
    return (instruction)(b -  b % 2);
}

blocksize instruction_to_blocksize(instruction i) {
    if (i < PROTO_BLOC_START) {
        return 0;
    }
    return (uint32)i;
}

//operations
void
localization_printf(localization l){
    switch(l){
        case UNSPLIT: printf("unsp"); return;
        case SPLIT: printf("spli"); return;
        case NONLOCAL : printf("none"); return;
        case NULL_LOCALIZATION : printf("null"); return;
        case LOCALIZATION_ERROR: printf("LERR"); return;
        default: printf("ERROR IN PRINTING LOCALIZATION"); return;
    }
}

void
variety_printf(variety v){
    switch(v) {
        case VARIETY_ERROR: printf("VERR"); return;
        case REFERENCE: printf("refr"); return;
        case HEAP: printf("heap"); return;
        case BUFF: printf("buff"); return;
        case NULL_VARIETY: printf("null"); return;
        case BLOCK: printf("bloc"); return;
        default: printf("ERROR IN PRINTING VARIETY"); return;
    }
}

void
implementation_printf(implementation i){
    switch(i){
        case IMPLEMENTATION_ERROR: printf("IERR"); return;
        case STANDARD: printf("stnd"); return;
        case GERMAN: printf("germ"); return;
        case NULL_IMPLEMENTATION: printf("null"); return;
        case BLOCK_IMPLEMENTION: printf("bloc"); return;
        default: printf("ERROR IN PRINTING IMPLEMENTATION"); return;
    }
}

//getters
variety
proto_get_variety(proto input) {
    switch(input.__attrs) {
        case(0):  return VARIETY_ERROR;
        case(1):  return REFERENCE;
        case(2):  return BUFF;
        case(3):  return BUFF;
        case(4):  return BUFF;
        case(5):  return BUFF;
        case(6):  return HEAP;
        case(7):  return HEAP;
        case(8):  return HEAP;
        case(9):  return HEAP;
        case(10): return NULL_VARIETY;
        default: {if (input.__attrs >= PROTO_BLOC_START) {return BLOCK;}
            else {return VARIETY_ERROR;}
        }
    }
}

implementation
proto_get_implementation(proto input){
    switch(input.__attrs){
        case(0): return IMPLEMENTATION_ERROR;
        case(1): return STANDARD;
        case(2): return STANDARD;
        case(3): return STANDARD;
        case(4): return GERMAN;
        case(5): return GERMAN;
        case(6): return STANDARD;
        case(7): return STANDARD;
        case(8): return GERMAN;
        case(9): return GERMAN;
        case(10):return NULL_IMPLEMENTATION;
        default: {if (input.__attrs >= PROTO_BLOC_START) {return BLOCK_IMPLEMENTION;}
            else {return IMPLEMENTATION_ERROR;}
        }
    }
}

blocksize
proto_get_blocksize(proto input){
    switch((int)(input.__attrs < PROTO_BLOC_START)) {
        case (1): return 0;
        case (0): return (input.__attrs - (input.__attrs % 2));
        default: printf("proto_get_blocksize failed."); exit(1);
    }
}

localization
proto_get_localization(proto input){
    proto_attrs attrs = input.__attrs;
    int is_refr         = (attrs == 1) ? 1 : 0;
    int is_null         = (attrs == 10) ? 2 : 0;
    int is_buff_or_heap = ((attrs >= PROTO_BUFF_START) && (attrs < PROTO_CONS_START)) ? 3 : 0;
    int is_block        = (attrs >= PROTO_BLOC_START) ? 4 : 0;
    switch(is_refr + is_null + is_buff_or_heap + is_block){
        case (0): return LOCALIZATION_ERROR;
        case (1): return NONLOCAL;
        case (2): return NULL_LOCALIZATION;
        case (3): return (attrs % 2 == 0) ? UNSPLIT : SPLIT;
        case (4): return (attrs % 2 == 0) ? UNSPLIT : SPLIT;
        default: return LOCALIZATION_ERROR;
    }
}

/*PROPERTIES*/
//varieties
int proto_is_refr(proto input){return ((input.__attrs == PROTO_REFR_START));}

int proto_is_buff(proto input){return ((input.__attrs >= PROTO_BUFF_START) && (input.__attrs < PROTO_HEAP_START));}

int proto_is_heap(proto input){return ((input.__attrs >= PROTO_HEAP_START) && (input.__attrs < PROTO_CONS_START));}

int proto_is_cons(proto input){return ((input.__attrs >= PROTO_CONS_START) && (input.__attrs < PROTO_BLOC_START));}

int proto_is_bloc(proto input){return ((input.__attrs >= PROTO_BLOC_START));}

int proto_is_null(proto input){return ((input.__attrs == 10));}

//localizations
int proto_is_split(proto input){return proto_get_localization(input) == SPLIT;}

int proto_is_unsplit(proto input){return proto_get_localization(input) == UNSPLIT;}

int proto_is_nonlocal(proto input){return proto_get_localization(input) == NONLOCAL;}

//implementation
int proto_is_german(proto input){return (proto_get_implementation(input) == GERMAN);}

int proto_is_blockimpl(proto input){return (proto_get_implementation(input) == BLOCK_IMPLEMENTION);}

int proto_is_standard(proto input){return (proto_get_implementation(input) == STANDARD);}

//operations
void
proto_printf(proto input){
    switch(input.__attrs){
        case(0): printf("l: LERR; v: VERR; i: IERR;"); return;
        case(1): printf("l: none; v: refr; i: stnd;"); return;
        case(2): printf("l: unsp; v: buff; i: stnd;"); return;
        case(3): printf("l: spli: v: buff; i: stnd;"); return;
        case(4): printf("l: unsp; v: buff; i: germ;"); return;
        case(5): printf("l: spli; v: buff; i: germ;"); return;
        case(6): printf("l: unsp; v: heap; i: stnd;"); return;
        case(7): printf("l: spli; v: heap; i: stnd;"); return;
        case(8): printf("l: unsp; v: heap; i: germ;"); return;
        case(9): printf("l: spli; v: heap; i: germ;"); return;
        case(10):printf("l: null; v: null; i: null;"); return;
        case(11):printf("l: LERR; v: VERR; i: IERR;"); return; //extra spot
        case(12):printf("l: LERR; v: VERR; i: IERR;"); return; //extra spot
        case(13):printf("l: LERR; v: VERR; i: IERR;"); return; //extra spot
        case(14):printf("l: LERR; v: VERR; i: IERR;"); return; //extra spot
        case(15):printf("l: LERR; v: VERR; i: IERR;"); return; //extra spot
        default: {
            if(input.__attrs % 2 == 0) {
                printf("l: unsp; v: bloc; blocksize: ");
                printf("%d", proto_get_blocksize(input));
                printf(";");
                return;
            } else {
                printf("l: spli; v: bloc; blocksize: ");
                printf("%d", proto_get_blocksize(input));
                printf(";");
                return;
            }
        }
    }
}

//creation methods
proto proto_from_lvi(localization l, variety v, implementation i) {
    if ((l == LOCALIZATION_ERROR) || (v == VARIETY_ERROR) || (i == IMPLEMENTATION_ERROR)) {
        return PROTOERROR;
    }
    switch(v){
        case(REFERENCE): {
            if (l != NONLOCAL) {return PROTOERROR;} else {return (proto){.__attrs = 1};}
        }
        case(BUFF): {
            if ((l <= 1) && (i <= 1)){
                return (proto){.__attrs = 2 + (uint32)l + 2 * ((uint32)i)};
            } else {return PROTOERROR;}
        }
        case(HEAP): {
            if ((l <= 1) && (i <= 1)){
                return (proto){.__attrs = 6 + (uint32)l + 2 * ((uint32)i)};
            } else {return PROTOERROR;}
        }
        case(NULL_VARIETY): {
            if ((l == NULL_LOCALIZATION) && (i == NULL_IMPLEMENTATION)){
                return PROTONULL;
            } else {return PROTOERROR;}
        }
        case(BLOCK): {
            printf("you can't implement a block with lvi. use lblocksize\n");
            return PROTOERROR;
        }
        default : return PROTOERROR;
    }
    return PROTONULL;
}

proto proto_from_lbsize(localization l, blocksize bsize){
    if ((l == LOCALIZATION_ERROR) || (bsize < PROTO_BLOC_START)) {return PROTOERROR;}
    switch(l){
        case(UNSPLIT): return (proto){.__attrs = bsize - bsize % 2};
        case(SPLIT): return (proto){.__attrs = bsize - bsize % 2 + 1};
        default: return PROTOERROR;
    }
}