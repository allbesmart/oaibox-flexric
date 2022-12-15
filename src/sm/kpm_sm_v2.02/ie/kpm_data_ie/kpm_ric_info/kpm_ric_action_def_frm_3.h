#ifndef KPM_V2_ACTION_DEFINITION_FORMAT_3_H
#define KPM_V2_ACTION_DEFINITION_FORMAT_3_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stdint.h>

#include "../data/meas_info_frm_3_lst.h"

typedef struct {
    size_t meas_info_lst_len;  // [1, 65535]
    meas_info_format_3_lst_t *meas_info_lst;

    uint32_t gran_period_ms;  // 8.3.8 [0, 4294967295]

    cell_global_id_t* cell_global_id; /* OPTIONAL - 8.3.20 */

} kpm_act_def_format_3_t;





#ifdef __cplusplus
}
#endif

#endif

// add for cell global at the end, when you see where you are going to define it

