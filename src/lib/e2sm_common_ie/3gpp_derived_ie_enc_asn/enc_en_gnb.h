#ifndef ENCRYPTION_EN_GNB_H
#define ENCRYPTION_EN_GNB_H


#ifdef __cplusplus
extern "C" {
#endif

#include "../../../sm/kpm_sm_v2.02/ie/asn/UEID-EN-GNB.h"
#include "../3gpp_derived_ie/en_gnb.h"

UEID_EN_GNB_t * enc_en_gNB_UE_asn(const en_gnb_t * en_gnb);

#ifdef __cplusplus
}
#endif

#endif