#ifndef ON_RIC_SUBSCRIPTION_KPM_V2_H
#define ON_RIC_SUBSCRIPTION_KPM_V2_H

#include "../ie/kpm_data_ie/e2ap_procedures/ric_subscription.h"

void fill_kpm_subscription_data(kpm_ric_subscription_t * subscription, const int ric_style_type, const char* cmd);


#endif
