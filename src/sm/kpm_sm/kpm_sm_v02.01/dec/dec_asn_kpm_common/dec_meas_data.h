#ifndef DECODE_MEASUREMENT_DATA_FORMAT_1_KPM_V2_01_H
#define DECODE_MEASUREMENT_DATA_FORMAT_1_KPM_V2_01_H

#ifdef __cplusplus
extern "C" {
#endif

#include "../../ie/asn/MeasurementData.h"
#include "../../ie/kpm_data_ie/data/meas_data_lst.h"

meas_data_lst_t * kpm_dec_meas_data_asn(const MeasurementData_t meas_data_asn, const size_t meas_data_len);

#ifdef __cplusplus
}
#endif

#endif