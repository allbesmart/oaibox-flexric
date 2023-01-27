#ifndef DECRYPTION_NG_ENB_H
#define DECRYPTION_NG_ENB_H


#ifdef __cplusplus
extern "C" {
#endif

#include "../../../sm/kpm_sm_v2.02/ie/asn/UEID-NG-ENB.h"
#include "../3gpp_derived_ie/ng_enb.h"

ng_enb_t dec_ng_eNB_UE_asn(const UEID_NG_ENB_t * ng_enb_asn);

#ifdef __cplusplus
}
#endif

#endif