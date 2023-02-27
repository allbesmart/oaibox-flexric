#include "policy_cond.h"

#include <assert.h>

void free_policy_cond(policy_cond_t* src)
{
  assert(src != NULL);

  // Policy Action Definition
  // Mandatory
  // 9.3.20
  free_policy_action(&src->pol_act);

  // Policy Condition Definition
  // Optional
  // 9.3.29
  assert(src->pol == NULL && "Not implemented");

}




bool eq_policy_cond(policy_cond_t const* m0, policy_cond_t const* m1)
{

  assert(0!=0 && "Not implemented");


}

