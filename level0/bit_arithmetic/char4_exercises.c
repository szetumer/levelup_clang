#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum variety {
    REFR,
    BUFF,
    HEAP,
    BLOC
} variety;


typedef unsigned char bits[4];
bits b0 = {0x00, 0x00, 0x00, 0x00};
bits b1 = {0x01, 0x00, 0x00, 0x00};
bits b2 = {0x02, 0x00, 0x00, 0x00};
bits b3 = {0x03, 0x00, 0x00, 0x00};
bits b4 = {0x04, 0x00, 0x00, 0x00};
bits b5 = {0x05, 0x00, 0x00, 0x00};
bits b6 = {0x06, 0x00, 0x00, 0x00};
bits b7 = {0x07, 0x00, 0x00, 0x00};
bits b8 = {0x08, 0x00, 0x00, 0x00};
bits b9 = {0x09, 0x00, 0x00, 0x00};
bits b10 = {0x0A, 0x00, 0x00, 0x00};
bits b11 = {0x0B, 0x00, 0x00, 0x00};
bits b12 = {0x0C, 0x00, 0x00, 0x00};
bits b13 = {0x0D, 0x00, 0x00, 0x00};
bits b14 = {0x0E, 0x00, 0x00, 0x00};
bits b15 = {0x0F, 0x00, 0x00, 0x00};
bits b16 = {0x10, 0x00, 0x00, 0x00};
bits b17 = {0x11, 0x00, 0x00, 0x00};

typedef unsigned char bytemask;
bytemask GETVARIETY = 0x03;
bytemask GETLOCALIZATION = 0x04;
bytemask GETIMPLEMENATION_PART1 = 0x08;
bytemask GETGERMANSIZE = 0xF0;


void printbits(bits);
void printvariety(variety);
variety get_variety(bits);




int main(void){
    printbits(b1);
    return 0;
}

void printbits(bits b){
    for(int i = 0; i < 4; i++) {
        printf("byte %d: 0x%02X\n", i, b[i]);
    }
}

void printvariety(variety v){
    switch(v){
        case(REFR) : {printf("REFR"); return;}
        case(BUFF) : {printf("BUFF"); return;}
        case(HEAP) : {printf("HEAP"); return;}
        case(BLOC) : {printf("BLOC"); return;}
    }
    return;
}

variety get_variety(bits b){
    variety v = (variety)(b[0] & GETVARIETY);
    return v;
}