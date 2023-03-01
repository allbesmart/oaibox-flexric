#include "lst_ran_param.h"

#include <assert.h>
#include <stdlib.h>

void free_lst_ran_param(lst_ran_param_t* src)
{
  assert(src != NULL);

  // RAN Parameter ID
  // Mandatory
  // 9.3.8
  //1.. 4294967295
  // uint32_t ran_param_id;

  // RAN Parameter Structure
  // Mandatory
  // 9.3.12
  free_ran_param_struct(&src->ran_param_struct);

}

bool eq_lst_ran_param(lst_ran_param_t const* m0, lst_ran_param_t const* m1)
{
  if(m0 == m1)
    return true;

  if(m0 == NULL || m1 == NULL)
    return false;

  if(m0->ran_param_id != m1->ran_param_id)
    return false;

  if(eq_ran_param_struct(&m0->ran_param_struct, &m1->ran_param_struct) == false)
    return false;

  return true;
}


