#ifndef DECRYPTION_GNB_H
#define DECRYPTION_GNB_H


#ifdef __cplusplus
extern "C" {
#endif

#include "../../../sm/kpm_sm_v02.03/ie/asn/UEID-GNB.h"
#include "../3gpp_derived_ie/gnb.h"

gnb_e2sm_t dec_gNB_UE_asn(const UEID_GNB_t * gnb_asn);

#ifdef __cplusplus
}
#endif

#endif
