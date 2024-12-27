#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../proto/dstr.h"
#include "../../proto/base.h"

char**  get_charstar_inputs();
void    free_inputs(char**);
void*   get_tailbuff();
dstr**   get_ptrs_to_dstrs();
/*GET THE ATTR FUNCTIONS*/

/*dstr_attrs_to<impl>*/
int attrs_sample_size;
typedef struct attrs_io {
    char*   charstar_input;
    dstr*   expected_dstr;
    char*   expected_data;
    uint32  expected_len;
} attrs_io;
typedef attrs_io* attrs_samples;
attrs_samples get_attrs_tobuff_unsplit_samples();
attrs_samples get_attrs_tobuff_split_samples();
attrs_samples get_attrs_tobuff_samples();
attrs_samples get_attrs_toheap_unsplit_samples();
attrs_samples get_attrs_toheap_split_samples();
attrs_samples get_attrs_toheap_samples();
attrs_samples get_attrs_tobloc_unsplit_samples();
attrs_samples get_attrs_tobloc_split_samples();
attrs_samples get_attrs_tobloc_samples();
attrs_samples get_attrs_toref_samples();