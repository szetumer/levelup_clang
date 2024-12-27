#ifndef UTILS
#define UTILS
#include <stdio.h>
#include <stdlib.h>
#include <libcalg-1.0/libcalg/slist.h>
#include "../../proto/ints.h"
#include "../../proto/base.h"
#include "../../proto/strs.h"
#include "../../proto/str.h"

SListEntry*     ints_to_sll(ints);
ints            ints_from_sll_tonew(SListEntry*);
void*           ints_from_sll_tobuff(void*, SListEntry*);
SListEntry**    remove_nthfromlast_leet19(SListEntry**, int n);

#endif