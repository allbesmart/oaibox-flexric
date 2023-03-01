#ifndef MEASUREMENT_BIN_RANGE_INFO_LIST_KPM_V2_H
#define MEASUREMENT_BIN_RANGE_INFO_LIST_KPM_V2_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdlib.h>
#include "meas_type.h"
#include "bin_range_def.h"

/* Intermediate structure for  8.2.1.2.1  E2SM-KPM Action Definition Format 1 */
typedef struct {
    meas_type_t meas_type;
    bin_range_def_t bin_range_def;  // 8.3.26
    
} meas_bin_range_info_lst_t;



#ifdef __cplusplus
}
#endif

#endif

// done