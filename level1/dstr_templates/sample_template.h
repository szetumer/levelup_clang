#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../proto/dstr.h"
#include "../../proto/base.h"

/*GET THE COPY FUNCTIONS*/
uint32 cat2_sample_size;

/*GET INDIVIDUAL SAMPLES*/
typedef struct cat2_io {
    dstr*   input1;
    dstr*   input2;
    dstr*   output;
} cat2_io;
typedef cat2_io* cat2_samples;
cat2_samples get_cat2_tobuff_split_samples();
cat2_samples get_cat2_tobuff_unsplit_samples();
cat2_samples get_cat2_tobuff_samples();
cat2_samples get_cat2_toheap_split_samples();
cat2_samples get_cat2_toheap_unsplit_samples();
cat2_samples get_cat2_toheap_samples();
cat2_samples get_cat2_tobloc_split_samples();
cat2_samples get_cat2_tobloc_unsplit_samples();
cat2_samples get_cat2_tobloc_samples();

/*INITIALIZE RESOURCES*/
dstr*           get_dstr_inputs();
void            free_dstrs(dstr*);
dstr*           get_headbuff();
void*           get_tailbuff();
cat2_samples    get_samples_array();
