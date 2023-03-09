#ifndef ENCRYPTION_GNB_H
#define ENCRYPTION_GNB_H


#ifdef __cplusplus
extern "C" {
#endif

#include "../../../sm/kpm_sm_v02.03/ie/asn/UEID-GNB.h"
#include "../3gpp_derived_ie/gnb.h"

UEID_GNB_t * enc_gNB_UE_asn(const gnb_e2sm_t * gnb);

#ifdef __cplusplus
}
#endif

#endif
