#ifndef KPM_V2_MEASUREMENT_INFORMATIOIN_FORMAT_3_LIST_H
#define KPM_V2_MEASUREMENT_INFORMATIOIN_FORMAT_3_LIST_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdlib.h>

#include "meas_type.h"
#include "bin_range_def.h"
#include "matching_cond_format_3_lst.h"


typedef struct {
    meas_type_t meas_type;

    size_t matching_cond_lst_len;
    matching_condition_format_3_lst_t *matching_cond_lst;;

    bin_range_def_t bin_range_def;

} meas_info_format_3_lst_t;


#ifdef __cplusplus
}
#endif

#endif