#include <assert.h>

#include "ric_subscription.h"

void free_kpm_subscription_data(kpm_ric_subscription_t* subscription)
{
    assert(subscription != NULL);

    
    // Event Trigger - nothing to free


    // Action Definition
    switch (subscription->kpm_act_def.type)
    {
    case FORMAT_1_ACTION_DEFINITION:
        free_kpm_action_def_frm_1(&subscription->kpm_act_def.frm_1);
        break;

    // case FORMAT_2_ACTION_DEFINITION:
    //     free_kpm_action_def_frm_2(&subscription->kpm_act_def.frm_2);
    //     break;

    // case FORMAT_3_ACTION_DEFINITION:
    //     free_kpm_action_def_frm_3(&subscription->kpm_act_def.frm_3);
    //     break;

    // case FORMAT_4_ACTION_DEFINITION:
    //     free_kpm_action_def_frm_4(&subscription->kpm_act_def.frm_4);
    //     break;

    // case FORMAT_5_ACTION_DEFINITION:
    //     free_kpm_action_def_frm_5(&subscription->kpm_act_def.frm_5);
    //     break;
    
    default:
        assert(false && "Unknown Action Definition Type");
    }



}