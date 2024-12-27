#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../proto/base.h"

/*Sample Functions:*/
buff    get_buffer();
method* get_methods();
uint32  protos_sample_size;
proto*  get_protos();

/*TEST PROTO_GET_IMPLEMENTATION FUNCTION*/
//pgi = prot_get_implementation
uint32 lvi_sample_size;
typedef struct lvi_io{
    localization    l_input;
    variety         v_input;
    implementation  i_input;
    proto           output;
    localization    l_output;
    variety         v_output;
    implementation  i_output;
} lvi_io;
typedef lvi_io* lvi_samples;
lvi_samples get_lvi_samples();

//lbsize = localization and block size.
uint32 lbsize_sample_size;
typedef struct lbsize_io {
    localization    l_input;
    blocksize       bsize_input;
    proto           output;
    localization    l_output;
    blocksize       bsize_output;
} lbsize_io;
typedef lbsize_io* lbsize_samples;
lbsize_samples get_lbsize_samples();
