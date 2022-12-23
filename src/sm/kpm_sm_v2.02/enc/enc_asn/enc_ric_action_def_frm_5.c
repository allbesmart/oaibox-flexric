#include <assert.h>
#include "../../ie/asn/asn_constant.h"


#include "enc_ric_action_def_frm_5.h"
#include "enc_ric_action_def_frm_1.h"


E2SM_KPM_ActionDefinition_Format5_t * kpm_enc_action_def_frm_5_asn(const kpm_act_def_format_5_t * act_def_frm_5)
{
    E2SM_KPM_ActionDefinition_Format5_t * act_def_frm_5_asn = calloc(1, sizeof(E2SM_KPM_ActionDefinition_Format5_t));
    assert (act_def_frm_5_asn != NULL && "Memory exhausted" );

    assert(act_def_frm_5->ue_id_lst_len >= 2 && act_def_frm_5->ue_id_lst_len <= maxnoofUEIDPerSub);

    for (size_t i = 0; i < act_def_frm_5->ue_id_lst_len; i++)
    {

        /* to be filled : UE_id */

    }


    act_def_frm_5_asn->subscriptionInfo = *kpm_enc_action_def_frm_1_asn(&act_def_frm_5->action_def_format_1);

    return &act_def_frm_5_asn;

}