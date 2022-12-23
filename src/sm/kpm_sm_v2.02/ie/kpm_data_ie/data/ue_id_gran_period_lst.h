#ifndef UE_ID_FOR_GRANULARITY_PERIOD_KPM_V2_H
#define UE_ID_FOR_GRANULARITY_PERIOD_KPM_V2_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>

#include "enum_value.h"
#include "../../../lib/e2sm_common_ie/sm_common_ie/ue_id.h"

typedef enum {
    NONE_MATCHED_UE,
    ONE_OR_MORE_MATCHED_UE,

    END_MATCHED_UE

} matched_ue_e;

typedef struct {
    size_t ue_lst_len;
    ue_id_t *ue_lst;  // 8.3.24

} ue_lst_t;


/* Intermediate structure for  8.2.1.4.2  E2SM-KPM Indication Message Format 2 */

typedef struct {
    matched_ue_e num_matched_ue;
    union {
        enum_value_e no_matched_ue;
        ue_lst_t matched_ue_lst;
    };
    

} ue_id_gran_period_lst_t;


#ifdef __cplusplus
}
#endif

#endif

// done