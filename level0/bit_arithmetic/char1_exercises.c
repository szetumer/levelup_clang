#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
typedef struct word {char data[8];} word; //for printing out all these enums; can only get 7 chars.
typedef struct proto_1 {
    unsigned char info;
    unsigned char addl[3];
} proto_1;
typedef struct proto_2 {
    unsigned int blocksize;
} proto_2;
typedef union proto {
    proto_1 a;
    proto_2 b;
} proto;
typedef enum variety {REFR, BUFF, HEAP, MUTA} variety;
typedef enum localization {SPLT, CONT, TRPL} localization;
typedef enum implementation {STND, GERM, BLOC} implementation;

//get word
word variety_word(variety v);
word localization_word(localization l);
word implementation_word(implementation i);

//proto getters and setters
variety         proto_get_variety(proto p);
localization    proto_get_localization(proto p);
implementation  proto_get_implementation(proto p);

const unsigned char var_mask, loc_mask, imp_mask_part1, germ_size;
const unsigned int blocksize_mask;
int main(){
    assert(sizeof(variety) == 4);
    assert(sizeof(proto) == 4);
    unsigned char b, result;
    variety v;
    b = 0x07;
    result = b & var_mask;
    printf("%x\n", result);
    //implicit type conversion
    v = (b & var_mask);
    word wrd = variety_word(v);
    //What is that about
    printf("%s", wrd.data);
    return 0;
}

const unsigned char var_mask        = 0x03;
const unsigned char loc_mask        = 0x04;
const unsigned char imp_mask_p1     = 0x08;
const unsigned char germ_size       = 0xF0;
const unsigned int bsize_neg_mask   = 0x07;

word variety_word(variety v){
    word w;
    switch(v){
        case(REFR) : {strcpy(w.data, "REFR"); return w;}
        case(BUFF) : {strcpy(w.data, "BUFF"); return w;}
        case(HEAP) : {strcpy(w.data, "HEAP"); return w;}
        case(MUTA) : {strcpy(w.data, "MUTA"); return w;}
        default : {
            printf("failure to create variety word, failing.");
            exit(1);
        }
    }
}

word localization_word(localization l){
    word w;
    switch(l){
        case(SPLT) : {strcpy(w.data, "SPLT"); return w;}
        case(CONT) : {strcpy(w.data, "CONT"); return w;}
        case(TRPL) : {strcpy(w.data, "TRPL"); return w;}
        default : {
            printf("failure to create localization word, failing.");
            exit(1);
        }
    }
}

word implementation_word(implementation i){
    word w;
    switch(i){
        case(STND) : {strcpy(w.data, "STND"); return w;}
        case(GERM) : {strcpy(w.data, "GERM"); return w;}
        case(BLOC) : {strcpy(w.data, "BLOC"); return w;}
        default : {
            printf("failure to create implementation word, failing.");
            exit(1);
        }
    }
}

variety proto_get_variety(proto p){return (variety)(p.a.info & var_mask);}

localization proto_get_localization(proto p){
    return (localization)(p.a.info & loc_mask);
}