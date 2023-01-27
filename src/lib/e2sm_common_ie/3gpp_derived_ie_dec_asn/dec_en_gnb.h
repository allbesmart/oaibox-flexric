#ifndef DECRYPTION_EN_GNB_H
#define DECRYPTION_EN_GNB_H


#ifdef __cplusplus
extern "C" {
#endif

#include "../../../sm/kpm_sm_v2.02/ie/asn/UEID-EN-GNB.h"
#include "../3gpp_derived_ie/en_gnb.h"

en_gnb_t dec_en_gNB_UE_asn(const UEID_EN_GNB_t * en_gnb_asn);

#ifdef __cplusplus
}
#endif

#endif