#ifndef KPM_V2_RIC_INDICATION_MESSAGE_H
#define KPM_V2_RIC_INDICATION_MESSAGE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "kpm_ric_ind_msg_frm_1.h"

typedef enum {
    FORMAT_1_RIC_IND_MSG_KPM,
    FORMAT_2_RIC_IND_MSG_KPM,
    FORMAT_3_RIC_IND_MSG_KPM,

    END_RIC_IND_MSG,
} kpm_ric_ind_msg_e;

typedef struct
{
    kpm_ric_ind_msg_e type;
    union {
        kpm_ind_msg_format_1_t frm_1;
        // ind_msg_format_2_t frm_2;
        // ind_msg_format_3_t frm_3;
    };
    
    
} kpm_ric_ind_msg_t;
/*
ask Mikel: format 1 and 3 should be implemented?
format 2 is a bit complicated, as for action_def_3
*/

#ifdef __cplusplus
}
#endif

#endif