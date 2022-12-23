#ifndef RIC_INDICATION_HEADER_FORMAT_1_KPM_V2_H
#define RIC_INDICATION_HEADER_FORMAT_1_KPM_V2_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "../../../../util/byte_array.h"

// 8.2.1.3.1  E2SM-KPM Indication Header Format 1

typedef struct {
    uint32_t collectStartTime;  // 8.3.12
    byte_array_t *fileformat_version;  /* OPTIONAL */
    byte_array_t *sender_name;         /* OPTIONAL */
    byte_array_t *sender_type;         /* OPTIONAL */
    byte_array_t *vendor_name;         /* OPTIONAL */


} kpm_ric_ind_hdr_format_1_t;

#ifdef __cplusplus
}
#endif

#endif

// done