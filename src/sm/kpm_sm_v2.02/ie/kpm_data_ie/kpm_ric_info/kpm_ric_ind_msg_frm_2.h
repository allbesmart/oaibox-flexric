#ifndef RIC_INDICATION_MESSAGE_FORMAT_2_KPM_V2_H
#define RIC_INDICATION_MESSAGE_FORMAT_2_KPM_V2_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include "../data/meas_data_lst.h"
#include "../data/meas_info_cond_ue_lst.h"


//  8.2.1.4.2  E2SM-KPM Indication Message Format 2

typedef struct {
    size_t                    meas_data_lst_len; // [1, 65535]
    meas_data_lst_t          *meas_data_lst;

    size_t                    meas_info_cond_ue_lst_len;  // [1, 65535]
    meas_info_cond_ue_lst_t  *meas_info_cond_ue_lst;

    uint32_t                 *gran_period_ms;  // 8.3.8  -  OPTIONAL

} kpm_ind_msg_format_2_t;

#ifdef __cplusplus
}
#endif

#endif

// done