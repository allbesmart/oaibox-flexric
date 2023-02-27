#ifndef ENCRYPTION_GNB_CU_UP_H
#define ENCRYPTION_GNB_CU_UP_H


#ifdef __cplusplus
extern "C" {
#endif

#include "../../../sm/kpm_sm_v2.02/ie/asn/UEID-GNB-CU-UP.h"
#include "../3gpp_derived_ie/gnb_cu_up.h"

UEID_GNB_CU_UP_t * enc_gNB_CU_UP_UE_asn(const gnb_cu_up_t * gnb_cu_up);

#ifdef __cplusplus
}
#endif

#endif