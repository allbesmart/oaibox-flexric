#ifndef KPM_V2_RIC_INDICATION_HEADER_H
#define KPM_V2_RIC_INDICATION_HEADER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdlib.h>
#include "../../../../util/byte_array.h"

typedef struct {
  uint32_t collectStartTime;
  byte_array_t *fileformat_version;  /* OPTIONAL */
  byte_array_t *sender_name;         /* OPTIONAL */
  byte_array_t *sender_type;         /* OPTIONAL */
  byte_array_t *vendor_name;         /* OPTIONAL */
} kpm_ric_ind_hdr_t;

// when you are changing the test for ind_hdr, take a look at the pointers !!!

void                free_kpm_ind_hdr(kpm_ric_ind_hdr_t* src);
kpm_ric_ind_hdr_t   cp_kpm_ind_hdr(kpm_ric_ind_hdr_t const* src);
bool                eq_kpm_ind_hdr(kpm_ric_ind_hdr_t const* hdr0, kpm_ric_ind_hdr_t const* hdr1);


#ifdef __cplusplus
}
#endif

#endif