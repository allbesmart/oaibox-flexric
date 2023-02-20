#ifndef DECRYPTION_GLOBAL_NG_ENB_H
#define DECRYPTION_GLOBAL_NG_ENB_H


#ifdef __cplusplus
extern "C" {
#endif

#include "../../../sm/kpm_sm_v2.02/ie/asn/GlobalNgENB-ID.h"
#include "../3gpp_derived_ie/global_ng_enb_id.h"

global_ng_enb_id_t dec_global_ng_enb_asn(const GlobalNgENB_ID_t * global_ng_enb_id_asn);

#ifdef __cplusplus
}
#endif

#endif
