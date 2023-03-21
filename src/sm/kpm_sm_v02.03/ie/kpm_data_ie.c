#include <assert.h>

#include "kpm_data_ie.h"

/* KPM RIC INDICATION DATA */

void free_kpm_ind_data(kpm_ric_indication_t* ind) 
{
  assert(ind != NULL);
  
  free_kpm_ind_hdr(&ind->kpm_ind_hdr);

  
  free_kpm_ind_msg(&ind->kpm_ind_msg);

  
}

kpm_ric_indication_t cp_kpm_ind_data(kpm_ric_indication_t const* src) 
{

  assert(src != NULL);
  kpm_ric_indication_t ret = {0};
  
  ret.kpm_ind_hdr = cp_kpm_ind_hdr(&src->kpm_ind_hdr);

  ret.kpm_ind_msg = cp_kpm_ind_msg(&src->kpm_ind_msg);

  return ret;
}


bool eq_kpm_ind_data(kpm_ric_indication_t const* ind0, kpm_ric_indication_t const* ind1)
{
  assert(ind0 != NULL);
  assert(ind1 != NULL);

  if (ind0 == ind1) return true;

  if(ind0 == NULL || ind1 == NULL)
    return false;

  // Indication Header
  if (eq_kpm_ind_hdr(&ind0->kpm_ind_hdr, &ind1->kpm_ind_hdr) != true)
    return false;


  // Indication Message
  if (eq_kpm_ind_msg(&ind0->kpm_ind_msg, &ind1->kpm_ind_msg) != true)
    return false;


  return true;
}


/* KPM RIC SUBSCRIPTION DATA */

void free_kpm_subscription_data(kpm_ric_subscription_t* subscription)
{
  assert(subscription != NULL);

    
  // Event Trigger - nothing to free
  free_kpm_event_trigger_def(&subscription->kpm_event_trigger_def);

  // Action Definition
  free_kpm_action_def(&subscription->kpm_act_def);

}

kpm_ric_subscription_t cp_kpm_subscription_data(kpm_ric_subscription_t const* src)
{
  assert(src != NULL);

  kpm_ric_subscription_t ret = {0};

  // Event Trigger
  ret.kpm_event_trigger_def = cp_kpm_event_trigger_def(&src->kpm_event_trigger_def);

  // Action Definition
  ret.kpm_act_def = cp_kpm_action_def(&src->kpm_act_def);

  return ret;
}

bool eq_kpm_subscription_data(kpm_ric_subscription_t const* m0, kpm_ric_subscription_t const* m1)
{
  assert(m0 != NULL);
  assert(m1 != NULL);

  if (m0 == m1) return true;

  if(m0 == NULL || m1 == NULL)
    return false;

  // Event Trigger
  if(eq_kpm_event_trigger_def(&m0->kpm_event_trigger_def, &m1->kpm_event_trigger_def) != true)
    return false;

  // Action Definition
  if(eq_kpm_action_def(&m0->kpm_act_def, &m1->kpm_act_def) != true)
    return false;


  return true;
}


/* E2 SETUP */

void free_kpm_e2_setup(kpm_e2_setup_t * e2_setup)
{
  assert(e2_setup != NULL);

  free_kpm_ran_function_def(&e2_setup->kpm_ran_function_def);
}

kpm_e2_setup_t cp_kpm_e2_setup(kpm_e2_setup_t const* src)
{
  assert(src != NULL);

  kpm_e2_setup_t dst = {0};

  dst.kpm_ran_function_def = cp_kpm_ran_function_def(&src->kpm_ran_function_def);

  return dst;
}

bool eq_kpm_e2_setup(kpm_e2_setup_t const * m0, kpm_e2_setup_t const * m1)
{
  assert(m0 != NULL);
  assert(m1 != NULL);

  if (eq_kpm_ran_function_def(&m0->kpm_ran_function_def, &m1->kpm_ran_function_def) != true)
    return false;


  return true;
}
