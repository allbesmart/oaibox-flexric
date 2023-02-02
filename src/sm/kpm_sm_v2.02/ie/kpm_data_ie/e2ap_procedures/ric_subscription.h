#ifndef RIC_SUBSCRIPTION_KPM_V2_H
#define RIC_SUBSCRIPTION_KPM_V2_H

#ifdef __cplusplus
extern "C" {
#endif

#include "../kpm_ric_info/kpm_ric_event_trigger_def.h"
#include "../kpm_ric_info/kpm_ric_action_def.h"

typedef struct {

    kpm_event_trigger_def_t kpm_event_trigger_def;
    kpm_act_def_t kpm_act_def;

} kpm_ric_subscription_t;

void free_kpm_subscription_data(kpm_ric_subscription_t* subscription);


#ifdef __cplusplus
}
#endif

#endif

// done