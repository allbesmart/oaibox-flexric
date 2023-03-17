#ifndef KPM_V2_03_INFORMATION_ELEMENTS_H
#define KPM_V2_03_INFORMATION_ELEMENTS_H

#include "kpm_data_ie/kpm_ric_info/kpm_ran_function_def.h"
#include "kpm_data_ie/kpm_ric_info/kpm_ric_event_trigger_def.h"
#include "kpm_data_ie/kpm_ric_info/kpm_ric_action_def.h"
#include "kpm_data_ie/kpm_ric_info/kpm_ric_ind_hdr.h"
#include "kpm_data_ie/kpm_ric_info/kpm_ric_ind_msg.h"


// RIC INDICATION
typedef struct {

    kpm_ind_hdr_t kpm_ind_hdr;
    kpm_ind_msg_t kpm_ind_msg;

} kpm_ric_indication_t;

void free_kpm_ind_data(kpm_ric_indication_t* ind);

kpm_ric_indication_t cp_kpm_ind_data(kpm_ric_indication_t const* src);

bool eq_kpm_ind_data(kpm_ric_indication_t const* ind0, kpm_ric_indication_t const* ind1);


// RIC SUBSCRIPTION
typedef struct {

    kpm_event_trigger_def_t kpm_event_trigger_def;
    kpm_act_def_t kpm_act_def;

} kpm_ric_subscription_t;

void free_kpm_subscription_data(kpm_ric_subscription_t* subscription);

kpm_ric_subscription_t cp_kpm_subscription_data(kpm_ric_subscription_t const* src);

bool eq_kpm_subscription_data(kpm_ric_subscription_t const* m0, kpm_ric_subscription_t const* m1);

// RIC SERVICE UPDATE
typedef struct {

    kpm_ran_function_def_t kpm_ran_function_def;

} kpm_ric_service_update_t;


// E2 SETUP
typedef struct {

    kpm_ran_function_def_t kpm_ran_function_def;

} kpm_e2_setup_t;


#endif
