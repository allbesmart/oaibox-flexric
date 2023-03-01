#ifndef DECRYPTION_UE_ID_H
#define DECRYPTION_UE_ID_H


#ifdef __cplusplus
extern "C" {
#endif

#include "../../../sm/kpm_sm_v02.03/ie/asn/UEID.h"
#include "../sm_common_ie/ue_id.h"

ue_id_t dec_ue_id_asn(const UEID_t * ue_id_asn);

#ifdef __cplusplus
}
#endif

#endif
