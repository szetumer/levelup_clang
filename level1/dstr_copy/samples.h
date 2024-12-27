#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../proto/dstr.h"
#include "../../proto/base.h"

/*GET THE COPY FUNCTIONS*/
uint32 copy_sample_size;

/*GET INDIVIDUAL SAMPLES*/
typedef struct copy_io {
    dstr*   input;
    dstr*   output;
} copy_io;
typedef copy_io* copy_samples;
copy_samples get_copy_tobuff_split_samples();
copy_samples get_copy_tobuff_unsplit_samples();
copy_samples get_copy_tobuff_samples();
copy_samples get_copy_toheap_split_samples();
copy_samples get_copy_toheap_unsplit_samples();
copy_samples get_copy_toheap_samples();
copy_samples get_copy_tobloc_split_samples();
copy_samples get_copy_tobloc_unsplit_samples();
copy_samples get_copy_tobloc_samples();

/*INITIALIZE RESOURCES*/
dstr*           get_dstr_inputs();
void            free_dstrs(dstr*);
dstr*           get_headbuff();
void*           get_tailbuff();
copy_samples    get_samples_array();
