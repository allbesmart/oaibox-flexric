#include <assert.h>
#include "../../ie/asn/asn_constant.h"

#include "dec_ric_action_def_frm_5.h"
#include "dec_ric_action_def_frm_1.h"


kpm_act_def_format_5_t kpm_dec_action_def_frm_5_asn(const E2SM_KPM_ActionDefinition_Format5_t * act_def_asn)
{
    kpm_act_def_format_5_t act_def = {0};

    act_def.ue_id_lst_len = act_def_asn->matchingUEidList.list.count;
    assert(act_def.ue_id_lst_len >= 2 && act_def.ue_id_lst_len <= maxnoofUEIDPerSub);

    for (size_t i = 0; i<act_def.ue_id_lst_len; i++)
    {

        /* to be filled : UE_id */
    
    }


    act_def.action_def_format_1 = kpm_dec_action_def_frm_1_asn(&act_def_asn->subscriptionInfo);

    return act_def;
}