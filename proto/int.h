#ifndef PROTOINT
#define PROTOINT
#include <stdio.h>
#include <stdlib.h>

typedef int bool;

//these are functions that supplement the rest of the proto functions.
typedef bool (*int_criteria)(int);
typedef bool (*int_relation)(int, int);

#endif