#include "seq_ran_param.h"

#include <assert.h>

void free_seq_ran_param(seq_ran_param_t* src)
{
  assert(src != NULL);

  //RAN Parameter ID
  //Mandatory
  //9.3.8
  // [1 - 4294967295]
  // uint32_t ran_param_id;
  assert(src->ran_param_id > 0); 

  // RAN Parameter Value Type
  // 9.3.11
  // Mandatory
  free_ran_param_val_type(&src->ran_param_val);
  
  ran_param_val_type_t ran_param_val;
}

bool eq_seq_ran_param(seq_ran_param_t const* m0, seq_ran_param_t const* m1)
{
  assert(0!=0 && "Not implemented");

  return false;
}

