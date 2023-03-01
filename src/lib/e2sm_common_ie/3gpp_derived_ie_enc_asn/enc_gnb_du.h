#ifndef ENCRYPTION_GNB_DU_H
#define ENCRYPTION_GNB_DU_H


#ifdef __cplusplus
extern "C" {
#endif

#include "../../../sm/kpm_sm_v02.03/ie/asn/UEID-GNB-DU.h"
#include "../3gpp_derived_ie/gnb_du.h"

UEID_GNB_DU_t * enc_gNB_DU_UE_asn(const gnb_du_t * gnb_du);

#ifdef __cplusplus
}
#endif

#endif
