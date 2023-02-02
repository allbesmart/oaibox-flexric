#include <assert.h>

#include "fill_ind_hdr_frm_1.h"

void fill_kpm_ind_hdr_frm_1(kpm_ric_ind_hdr_format_1_t * hdr)
{
    assert(hdr != NULL);

    
    int64_t t = time_now_us();
    hdr->collectStartTime = t / 1000000; // needs to be truncated to 32 bits to arrive to a resolution of seconds
    hdr->fileformat_version->buf = NULL;

    hdr->sender_name->buf = calloc(strlen("My OAI-CU") + 1, sizeof(char));
    memcpy(hdr->sender_name->buf, "My OAI-CU", strlen("My OAI-CU"));
    hdr->sender_name->len = strlen("My OAI-CU");
    
    hdr->sender_type->buf = calloc(strlen("CU") + 1, sizeof(char));
    memcpy(hdr->sender_type->buf, "CU", strlen("CU"));
    hdr->sender_type->len = strlen("CU");

    hdr->vendor_name->buf = calloc(strlen("OAI") + 1, sizeof(char));
    memcpy(hdr->vendor_name->buf, "OAI", strlen("OAI"));
    hdr->vendor_name->len = strlen("OAI");


}