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
  assert(0!=0 && "Not implemented");

}




