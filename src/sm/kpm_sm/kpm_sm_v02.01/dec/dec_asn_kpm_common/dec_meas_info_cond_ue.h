#ifndef DECODE_MEASUREMENT_INFO_COND_UE_KPM_V2_01_H
#define DECODE_MEASUREMENT_INFO_COND_UE_KPM_V2_01_H

#ifdef __cplusplus
extern "C" {
#endif

#include "../../ie/asn/MeasurementCondUEidList.h"
#include "../../ie/kpm_data_ie/data/meas_info_cond_ue_lst.h"

meas_info_cond_ue_lst_t * kpm_dec_meas_info_cond_ue_asn(const MeasurementCondUEidList_t meas_cond_ue_asn, const size_t meas_cond_ue_len);

#ifdef __cplusplus
}
#endif

#endif