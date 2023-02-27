#include "policy_action.h"

#include <assert.h>

void free_policy_action(policy_action_t* src)
{
  assert(src != NULL);

  //  Policy Action ID
  //  Mandatory
  //  9.3.6
  //  [1 - 65535]
  // uint16_t policy_act_id;

  assert(src->policy_act_id > 0);

  // Sequence of RAN Parameters
  // [0- 65535]
  for(size_t i = 0; i < src->sz_seq_ran_param; ++i){
    free_seq_ran_param(&src->seq_ran_param[i]);
  }

  if(src->sz_seq_ran_param > 0)
    free(src->seq_ran_param);

  // RIC Policy decision
  // Optional
  assert(src->pol_dec == NULL && "Not implmented"); 

}

bool eq_policy_action(policy_action_t const* m0, policy_action_t const* m1)
{
  assert(0!=0 && "Not implemented" );

  return false;
}




