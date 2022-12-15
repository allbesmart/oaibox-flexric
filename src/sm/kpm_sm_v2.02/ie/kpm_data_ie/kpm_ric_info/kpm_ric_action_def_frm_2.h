#ifndef KPM_V2_ACTION_DEFINITION_FORMAT_2_H
#define KPM_V2_ACTION_DEFINITION_FORMAT_2_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stdint.h>

#include "../data/ue_id.h"
#include "kpm_ric_action_def_frm_1.h"

typedef struct {
    ue_id_t ue_id; // maybe it should be pointer
    kpm_act_def_format_1_t action_def_format_1;

} kpm_act_def_format_2_t;

#ifdef __cplusplus
}
#endif

#endif