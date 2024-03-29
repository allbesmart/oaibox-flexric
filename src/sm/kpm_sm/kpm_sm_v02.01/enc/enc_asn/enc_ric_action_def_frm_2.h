#ifndef ENCRYPTION_ASN_ACTION_DEFINITION_FORMAT_2_KPM_V2_01_H
#define ENCRYPTION_ASN_ACTION_DEFINITION_FORMAT_2_KPM_V2_01_H

#ifdef __cplusplus
extern "C" {
#endif

#include "../../ie/asn/E2SM-KPM-ActionDefinition-Format2.h"
#include "../../ie/kpm_data_ie/kpm_ric_info/kpm_ric_action_def_frm_2.h"



E2SM_KPM_ActionDefinition_Format2_t * kpm_enc_action_def_frm_2_asn(const kpm_act_def_format_2_t * act_def_frm_2);


#ifdef __cplusplus
}
#endif

#endif