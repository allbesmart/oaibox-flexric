#include <assert.h>

#include "on_ric_subscription.h"
#include "fill_kpm_event_trigger_frm_1.h"
#include "fill_kpm_action_def_frm_1.h"


void fill_kpm_subscription_data(kpm_ric_subscription_t * subscription, const int ric_style_type, const char* cmd)
{
    assert(subscription != NULL);
    assert(cmd != NULL);

    switch (ric_style_type)
    {
    case 1:
        subscription->kpm_event_trigger_def.type = FORMAT_1_RIC_EVENT_TRIGGER;
        fill_kpm_event_trigger_frm_1(&subscription->kpm_event_trigger_def.kpm_ric_event_trigger_format_1, &cmd);
        break;
    
    default:
        assert(false && "Unknown Event Trigger Type");
    }


    switch (ric_style_type)
    {
    case 1:
        subscription->kpm_act_def.type = FORMAT_1_ACTION_DEFINITION;
        fill_kpm_action_def_frm_1(&subscription->kpm_act_def.frm_1);
        break;

    // case 2:
    //     subscription->kpm_act_def.type = FORMAT_2_ACTION_DEFINITION;
    //     fill_kpm_action_def_frm_2(&subscription->kpm_act_def.frm_2);
    //     break;

    // case 3:
    //     subscription->kpm_act_def.type = FORMAT_3_ACTION_DEFINITION;
    //     fill_kpm_action_def_frm_3(&subscription->kpm_act_def.frm_3);
    //     break;

    // case 4:
    //     subscription->kpm_act_def.type = FORMAT_4_ACTION_DEFINITION;
    //     fill_kpm_action_def_frm_4(&subscription->kpm_act_def.frm_4);
    //     break;

    // case 5:
    //     subscription->kpm_act_def.type = FORMAT_5_ACTION_DEFINITION;
    //     fill_kpm_action_def_frm_5(&subscription->kpm_act_def.frm_5);
    //     break;
    
    default:
        assert(false && "Unknown Action Definition Type");
    }


}