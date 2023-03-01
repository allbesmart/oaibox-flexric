#include "e2sm_rc_act_def_frmt_2.h"

#include <assert.h>
#include <stdlib.h>

void free_e2sm_rc_act_def_frmt_2(e2sm_rc_act_def_frmt_2_t* src)
{
  assert(src != NULL);

  for(size_t i = 0; i < src->sz_policy_cond; ++i){
    free_policy_cond(&src->policy_cond[i]); 
  }
  
  assert(src->policy_cond != NULL);
  free(src->policy_cond);

}

bool eq_e2sm_rc_act_def_frmt_2(e2sm_rc_act_def_frmt_2_t const* m0, e2sm_rc_act_def_frmt_2_t const* m1)
{
  if(m0 == m1)
    return true;

  if(m0 == NULL || m1 == NULL)
    return false;

  // Sequence of Policy Conditions
  // [1 - 65535]
  assert(m0->sz_policy_cond > 0 && m0->sz_policy_cond <  65535 +1);
  assert(m1->sz_policy_cond > 0 && m1->sz_policy_cond <  65535 +1);

  if(m0->sz_policy_cond != m1->sz_policy_cond)
    return false;

  for(size_t i = 0; i < m0->sz_policy_cond; ++i){
    if(eq_policy_cond(&m0->policy_cond[i], &m1->policy_cond[i]) == false )
      return false;
  }

  return true;
}

