#include "ran_parameter_value_type.h"

#include <assert.h>

void free_ran_param_val_type(ran_param_val_type_t *src)
{
  assert(src != NULL);

  if(src->type == ELEMENT_KEY_FLAG_TRUE_RAN_PARAMETER_VAL_TYPE){
    free_ran_parameter_value(&src->flag_true);

  } else if(src->type == ELEMENT_KEY_FLAG_FALSE_RAN_PARAMETER_VAL_TYPE ){

    free_ran_parameter_value(&src->flag_false);

  } else if(src->type == STRUCTURE_RAN_PARAMETER_VAL_TYPE ){
     free_ran_param_struct(&src->strct);

  } else if(src->type == LIST_RAN_PARAMETER_VAL_TYPE ){
    free_ran_param_list(&src->lst);

  } else {
    assert(0 != 0 && "Not implemented");
  }

}


bool eq_ran_param_val_type(ran_param_val_type_t const* m0, ran_param_val_type_t const* m1)
{
  assert(0!=0 && "Not implemented");


  return false;
}





