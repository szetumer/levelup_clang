#ifndef PROTODSTR
#define PROTODSTR
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "base.h"
//all proto objects maximize flexibility by exposing patterns of memory allocation.

typedef struct dstr_stnd {
    proto_attrs        __impl;
    uint32              len;
    char*               data;
} dstr_stnd;

typedef struct dstr_germ {
    proto_attrs        __impl;
    char                string[12];
} dstr_germ;

typedef struct dstr_bloc {
    proto_attrs        __impl;
    uint32             __len; //length of string plus one because null string = zero behind curtain.
    char*              data;
} dstr_bloc;

typedef union dstr {
    dstr_stnd   stnd;
    dstr_germ   germ;
    dstr_bloc   bloc;
    proto       dstr_proto; //gives access to all the proto methods without casting.
} dstr;

const dstr DSTRNULL;
const uint32 DSTR_MAX_GERMAN_BYTES;

void check_dstrs(dstr tocheck);

/*PROPERTIES*/
/*proto-properties*/
variety         dstr_variety(dstr);
implementation  dstr_implementation(dstr);
localization    dstr_localization(dstr);
/*attrs-properties*/
char*           dstr_data(dstr* pinput);

/*boolean properties*/
/*implementations*/
int dstr_isgerm(dstr);
int dstr_isbloc(dstr);
int dstr_isstnd(dstr);
/*localizations*/
int dstr_isunspl(dstr);
int dstr_issplit(dstr);
int dstr_isnonlo(dstr);
/*varieties*/
int dstr_isheap(dstr);
int dstr_isbuff(dstr);
int dstr_isrefr(dstr);
/*other properties*/
int dstr_isnull(dstr);
int dstr_iserr(dstr);

/*length and size properties*/
uint32  dstr_len(dstr);
uint32  dstr_blocksize(dstr);
uint32  dstr_datasize(dstr);
uint32  dstr_tailsize(dstr);
uint32  dstr_totalsize(dstr);

char    dstr_nth(dstr, uint32 nth, char defaultval);
char*   dstr_nthindex(dstr*, uint32 nth);

/*RELATIONSHIPS*/
int dstr_eq(dstr input1, dstr input2);
int dstr_eq_charstr(dstr input1, char* input2);

/*CREATION METHODS*/
    /*CREATE WITH A CHARSTAR (ie, from dstrs attribute)*/

/*dstr to buffer*/
void*   dstr_attrs_tobuff_split(char* data, dstr* head, void* tail);
void*   dstr_attrs_tobuff_unsplit(char* data, void* tail);
void*   dstr_attrs_tobuff(char* data, dstr* head, void* tail);

/*dstr to heap*/
void*   dstr_attrs_toheap_split(char* data, dstr* head); //call dstr_free on it.
void*   dstr_attrs_toheap_unsplit(char* data, void* tail); //free the tail value.
void*   dstr_attrs_toheap(char* data, dstr* head, void* tail); //either split or unsplit.

/*dstr to block*/
void*   dstr_attrs_tobloc_split(char* data, dstr* head, void* tail, blocksize b);
void*   dstr_attrs_tobloc_unsplit(char* data, void* tail, blocksize b);
void*   dstr_attrs_tobloc(char* data, dstr* head, void* tail, blocksize b);

/*dstr to refr*/
dstr   dstr_attrs_torefr(char* data);

/*dstr from attrs*/
void*   dstr_from_attrs(char* data, method m);

    /*CREATE BY COPYING A DSTR*/
/*dstr to buff*/
void*   dstr_copy_tobuff_split(dstr input, dstr* head, void* tail);
void*   dstr_copy_tobuff_unsplit(dstr input, void* tail);
void*   dstr_copy_tobuff(dstr input, dstr* head, void* tail);

/*dstr to heap*/
void*   dstr_copy_toheap_split(dstr input, dstr* head);
void*   dstr_copy_toheap_unsplit(dstr input, void* tail);
void*   dstr_copy_toheap(dstr input, dstr* head, void* tail);

/*dstr to block*/
void*   dstr_copy_tobloc_split(dstr input, dstr* head, void* tail, blocksize b);
void*   dstr_copy_tobloc_unsplit(dstr input, void* tail, blocksize b);
void*   dstr_copy_tobloc(dstr input, dstr* head, void* tail, blocksize b);

/*dstr to refr*/
dstr    dstr_copy_torefr(dstr input);

/*dstr from dstr*/
void*   dstr_from_copy(dstr input, method m);

    /*CREATE BY CONCATINATING TWO DSTRS*/
/*dstr to buff*/
void*   dstr_cat2_tobuff_split(dstr input1, dstr input2, dstr* head, void* tail);
void*   dstr_cat2_tobuff_unsplit(dstr input1, dstr input2, void* tail);
void*   dstr_cat2_tobuff(dstr input1, dstr input2, dstr* head, void* tail);

/*dstr to heap*/
void*   dstr_cat2_toheap_split(dstr input1, dstr input2, dstr* head);
void*   dstr_cat2_toheap_unsplit(dstr input1, dstr input2, void* tail);
void*   dstr_cat2_toheap(dstr input1, dstr input2, dstr* head, void* tail);

/*dstr to block*/
void*   dstr_cat2_tobloc_split(dstr input1, dstr input2, dstr* head, void* tail, blocksize b);
void*   dstr_cat2_tobloc_unsplit(dstr input1, dstr input2, void* tail, blocksize b);
void*   dstr_cat2_tobloc(dstr input1, dstr input2, dstr* head, void* tail, blocksize b);

/*dstr inplace*/
void*   dstr_cat2_inplace(dstr input1, dstr input2);

/*dstr from concatination*/
void*   dstr_from_cat2(dstr input1, dstr input2, method m);

    /*CREATE BY SLICING A LARGER STRING*/
/*dstr to buff*/
void*   dstr_slice_tobuff_split(dstr input, uint32 start, uint32 end, dstr* head, void* tail);
void*   dstr_slice_tobuff_unsplit(dstr input, uint32 start, uint32 end, void* tail);
void*   dstr_slice_tobuff(dstr input, uint32 start, uint32 end, dstr* head, void* tail);

/*dstr to heap*/
void*   dstr_slice_toheap_split(dstr input, uint32 start, uint32 end, dstr* head);
void*   dstr_slice_toheap_unsplit(dstr input, uint32 start, uint32 end, void* tail);
void*   dstr_slice_toheap(dstr input, uint32 start, uint32 end, dstr* head, void* tail);

/*dstr to block*/
void*   dstr_slice_tobloc_split(dstr input, uint32 start, uint32 end, dstr* head, void* tail, blocksize b);
void*   dstr_slice_tobloc_unsplit(dstr input, uint32 start, uint32 end, void* tail, blocksize b);
void*   dstr_slice_tobloc(dstr input, uint32 start, uint32 end, dstr* head, void* tail, blocksize b);

/*dstr to inplace*/ 
void*   dstr_slice_inplace(dstr input, uint32 start, uint32 end);

/*dstr to refr*/
dstr    dstr_slice_torefr(dstr input, uint32 start, uint32 end);

/*dstr from slice*/
void*   dstr_from_slice(dstr input, uint32 start, uint32 end, method m);

/*OPERATIONS*/
void dstr_free(dstr* input);
void dstr_stnd_printf(dstr_stnd, int);
void dstr_german_printf(dstr_germ, int);
void dstr_null_printf(dstr, int);
void dstr_printf(dstr, int);

//utitlities
dstr_stnd* dstr_get_five_samples();
dstr_stnd* dstr_get_ten_samples();

#endif