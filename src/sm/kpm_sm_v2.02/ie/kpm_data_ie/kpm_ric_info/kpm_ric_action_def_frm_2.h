#ifndef ACTION_DEFINITION_FORMAT_2_KPM_V2_H
#define ACTION_DEFINITION_FORMAT_2_KPM_V2_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stdint.h>

#include "../../../../lib/e2sm_common_ie/sm_common_ie/ue_id.h"
#include "kpm_ric_action_def_frm_1.h"

//  8.2.1.2.2  E2SM-KPM Action Definition Format 2

typedef struct {
    ue_id_t ue_id;  // 8.3.24
    kpm_act_def_format_1_t action_def_format_1;  // 8.2.1.2.1

} kpm_act_def_format_2_t;

#ifdef __cplusplus
}
#endif

#endif

// done