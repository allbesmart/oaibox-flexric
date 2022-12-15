#ifndef KPM_V2_MEASUREMENT_BIN_RANGE_INFO_LIST_H
#define KPM_V2_MEASUREMENT_BIN_RANGE_INFO_LIST_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdlib.h>
#include "meas_type.h"
#include "bin_range_def.h"

typedef struct {
    meas_type_t meas_type;
    bin_range_def_t bin_range_def;
    
} meas_bin_range_info_lst_t;



#ifdef __cplusplus
}
#endif

#endif