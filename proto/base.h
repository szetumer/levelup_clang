#ifndef PROTOBASE
#define PROTOBASE
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//protobase is heap-free - no allocations necessary. We accomplish this by
//using messages of fixed length.
typedef uint32_t uint32;
typedef uint64_t uint64;
typedef uint32_t proto_attrs;
typedef uint32_t private_inst;
typedef uint32_t blocksize;
typedef uint32_t inst_or_bsize;
typedef void* buff;

/*INSTRUCTIONS TO CREATE PROTO OBJECTS.*/
typedef enum instruction {
    //to block is contained in a number.
    INST_ERROR,
    TOREF,
    TOHEAP,
    TOBUFF,
    INPLACE,
    TONULL,
    TOBLOCK
} instruction;

instruction blocksize_to_instruction(blocksize b);
instruction instruction_from_blocksize(blocksize b);
blocksize   instruction_to_blocksize(instruction i);

void instruction_printf(instruction inst);

typedef struct method {
    void*           head;
    void*           tail;
    private_inst    inst;
} method;

instruction method_instruction(method m);
blocksize   method_blocksize(method m);
method      method_with_blocksize(void* head, void* tail, blocksize b);
method      method_with_instruction(void* head, void* tail, instruction i);
void        method_printf(method m);

/*
LOCALIZATION OF PROTO OBJECTS
*/
typedef enum localization {
    UNSPLIT, //0
    SPLIT, //1
    NONLOCAL, //2
    NULL_LOCALIZATION, //3
    LOCALIZATION_ERROR //4
} localization;

typedef enum implementation {
    STANDARD, //0
    GERMAN, //1
    BLOCK_IMPLEMENTION, // >=16
    NULL_IMPLEMENTATION, //10
    IMPLEMENTATION_ERROR //3
} implementation;

/*IMPLEMENTATION OF PROTO OBJECTS*/
typedef enum variety {
    VARIETY_ERROR, //0
    REFERENCE, //1
    BUFF, //2, 3, 4, 5,
    HEAP, //6, 7, 8, 9
    NULL_VARIETY, //10
    BLOCK //16, and above
} variety;

void    localization_printf(localization l);
void    implementation_printf(implementation i);            
void    variety_printf(variety v);    

typedef struct proto {
    proto_attrs    __attrs;
} proto;

/*CONSTANTS*/
// buff, then heap, then constants, then blocs
const uint32  PROTO_REFR_START;
const uint32  PROTO_BUFF_START;
const uint32  PROTO_HEAP_START;
const uint32  PROTO_CONS_START;
const uint32  PROTO_BLOC_START;
const proto   PROTONULL;
const proto   PROTOERROR;

/*PROPERTIES*/
//get properties
implementation  proto_get_implementation(proto input);
variety         proto_get_variety(proto input);
localization    proto_get_localization(proto input);
blocksize       proto_get_blocksize(proto input);

//bool properties
int proto_is_split(proto input);
int proto_is_unsplit(proto input);
int proto_is_blockimpl(proto input);
int proto_is_refr(proto input);
int proto_is_heap(proto input);
int proto_is_buff(proto input);
int proto_is_german(proto input);
int proto_is_standard(proto input);
int proto_is_bloc(proto input);

/*OPERATIONS*/
void proto_printf(proto input);

/*INITIALIZERS*/
proto proto_from_lvi(localization l, variety v, implementation i);
proto proto_from_lbsize(localization, blocksize n);

#endif