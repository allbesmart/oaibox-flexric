#ifndef KPM_V2_RIC_INDICATION_MESSAGE_FORMAT_1_H
#define KPM_V2_RIC_INDICATION_MESSAGE_FORMAT_1_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include "../data/meas_data_lst.h"
#include "../data/meas_info_lst.h"


typedef struct {
    size_t                    MeasData_len; // 1..
    meas_data_lst_t          *MeasData;

    size_t                    MeasInfo_len; 
    meas_info_lst_t          *MeasInfo;    // OPTIONAL, MeasInfo_len can be zero

    unsigned long            *granulPeriod;	/* OPTIONAL */

} kpm_ind_msg_format_1_t;

void                free_kpm_ind_msg(kpm_ind_msg_format_1_t* src);
kpm_ind_msg_format_1_t  cp_kpm_ind_msg(kpm_ind_msg_format_1_t const* src);
bool                eq_kpm_ind_msg(kpm_ind_msg_format_1_t const* m0, kpm_ind_msg_format_1_t const* m1);

#ifdef __cplusplus
}
#endif

#endif