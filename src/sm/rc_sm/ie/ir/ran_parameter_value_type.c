#include "ran_parameter_value_type.h"

#include "ran_parameter_value.h"
#include "ran_param_struct.h"
#include "ran_param_list.h"

#include <assert.h>
#include <stdlib.h>

void free_ran_param_val_type(ran_param_val_type_t *src)
{
  assert(src != NULL);

  if(src->type == ELEMENT_KEY_FLAG_TRUE_RAN_PARAMETER_VAL_TYPE){
    free_ran_parameter_value(src->flag_true);
    free(src->flag_true);
  } else if(src->type == ELEMENT_KEY_FLAG_FALSE_RAN_PARAMETER_VAL_TYPE ){
    free_ran_parameter_value(src->flag_false);
    free(src->flag_false);
  } else if(src->type == STRUCTURE_RAN_PARAMETER_VAL_TYPE ){
    free_ran_param_struct(src->strct);
    free(src->strct);
  } else if(src->type == LIST_RAN_PARAMETER_VAL_TYPE ){
    free_ran_param_list(src->lst);
    free(src->lst);
  } else {
    assert(0 != 0 && "Not implemented");
  }

}

bool eq_ran_param_val_type(ran_param_val_type_t const* m0, ran_param_val_type_t const* m1)
{
  if(m0 == m1)
    return true;

  if(m0 == NULL || m1 == NULL)
    return false;

  if(m0->type != m1->type)
    return false;

  if(m0->type == ELEMENT_KEY_FLAG_TRUE_RAN_PARAMETER_VAL_TYPE){
    if(eq_ran_parameter_value(m0->flag_true, m1->flag_true) == false)
      return false;
  } else if(m0->type == ELEMENT_KEY_FLAG_FALSE_RAN_PARAMETER_VAL_TYPE ){
    if(eq_ran_parameter_value(m0->flag_false, m1->flag_false) == false)
      return false;
  }else if(m0->type == STRUCTURE_RAN_PARAMETER_VAL_TYPE){
    if(eq_ran_param_struct(m0->strct, m1->strct) == false)
      return false;
  }else if(m0->type == LIST_RAN_PARAMETER_VAL_TYPE){
    if(eq_ran_param_list(m0->lst, m1->lst) == false)
      return false;
  } else {
    assert(0!=0 && "Unknown type");
  }

  return true;
}

