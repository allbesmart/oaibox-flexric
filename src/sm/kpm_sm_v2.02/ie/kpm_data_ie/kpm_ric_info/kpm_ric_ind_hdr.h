#ifndef RIC_INDICATION_HEADER_KPM_V2_H
#define RIC_INDICATION_HEADER_KPM_V2_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdlib.h>
#include "../../../../util/byte_array.h"

typedef enum {
  FORMAT_1_INDICATION_HEADER = 1,

  END_INDICATION_HEADER

} format_ind_hdr_e;

// 8.2.1.3    RIC INDICATION HEADER IE
// 8.2.1.3.1  E2SM-KPM Indication Header Format 1

typedef struct {
  uint32_t collectStartTime;  // 8.3.12
  byte_array_t *fileformat_version;  /* OPTIONAL */
  byte_array_t *sender_name;         /* OPTIONAL */
  byte_array_t *sender_type;         /* OPTIONAL */
  byte_array_t *vendor_name;         /* OPTIONAL */

} kpm_ind_hdr_t;


void                free_kpm_ind_hdr(kpm_ind_hdr_t* src);
kpm_ind_hdr_t   cp_kpm_ind_hdr(kpm_ind_hdr_t const* src);
bool                eq_kpm_ind_hdr(kpm_ind_hdr_t const* hdr0, kpm_ind_hdr_t const* hdr1);


#ifdef __cplusplus
}
#endif

#endif

// done