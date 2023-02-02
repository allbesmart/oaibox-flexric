#ifndef RIC_INDICATION_KPM_V2_H
#define RIC_INDICATION_KPM_V2_H

#ifdef __cplusplus
extern "C" {
#endif

#include "../kpm_ric_info/kpm_ric_ind_hdr.h"
#include "../kpm_ric_info/kpm_ric_ind_msg.h"

typedef struct {

    kpm_ind_hdr_t kpm_ind_hdr;
    kpm_ind_msg_t kpm_ind_msg;

} kpm_ric_indication_t;

#ifdef __cplusplus
}
#endif

#endif

void free_kpm_ind_data(kpm_ric_indication_t* ind);

kpm_ric_indication_t cp_kpm_ind_data(kpm_ric_indication_t const* src);

bool eq_kpm_ind_data(kpm_ric_indication_t const* ind0, kpm_ric_indication_t const* ind1);

// done