#include <assert.h>

#include "kpm_data_ie.h"

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



void free_kpm_subscription_data(kpm_ric_subscription_t* subscription)
{
    assert(subscription != NULL);

    
    // Event Trigger - nothing to free
    free_kpm_event_trigger_def(&subscription->kpm_event_trigger_def);

    // Action Definition
    free_kpm_action_def(&subscription->kpm_act_def);

}
