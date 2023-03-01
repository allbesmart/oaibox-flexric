#ifndef DECRYPTION_ENB_H
#define DECRYPTION_ENB_H


#ifdef __cplusplus
extern "C" {
#endif

#include "../../../sm/kpm_sm_v02.03/ie/asn/UEID-ENB.h"
#include "../3gpp_derived_ie/enb.h"

enb_t dec_eNB_UE_asn(const UEID_ENB_t * enb_asn);

#ifdef __cplusplus
}
#endif

#endif
