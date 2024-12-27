#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "base.h"

/*
Goal: to create a language that compiles with a c compiler.
    - it's lack of compiling would roughly translate to the program not being able to gen code from it.
- that produces meaningful output for testing. So that you can test it generically.
- that can be transformed with a code generator into code given inputs.
*/

/*
Method 1:
*/
//We try to get a generic style thing to function as well as possible
//using pointers everywhere
typedef void* Type;
typedef unsigned int    proto_size_func(FixedArrayKind*);
typedef                 Type array_nth(FixedArrayKind*, unsigned int n);

typedef struct FixedArrayKind {
    item_type_name      char[32];
    unsigned int        item_memsize;
    array_type_name     char[32];
    proto_size_func     get_array_memsize;
    proto_size_func     get_array_datasize;
} FixedArrayKind;


/*
Method 2:
*/
//We try to get something that is like stacking
//So like objects would have t : T : ArrayKind : Type
//And each time you ran the system with our code generator, it
//would peel off one of those layers.
typedef void* L0Var;
typedef L0Var array_nth(*L0Vars);
typedef unsigned int array_len(*L0Vars);

typedef struct L0Vars {
    L0Var               item_type0;
    proto_size_func     array_memsize0;
    proto_size_func     array_datasize0;
    array_nth           array_nth1;
    array_len           array_len1;                
} L0Vars;

//then the first round of processing would take all of the things with zero away and knock everything else down 1.