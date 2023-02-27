#ifndef RAN_PARAMETER_VALUE_TYPE_E2SM_H
#define RAN_PARAMETER_VALUE_TYPE_E2SM_H

#include <stdbool.h>

#include "ran_param_list.h"
#include "ran_param_struct.h"
#include "ran_parameter_value.h"

typedef enum{

  ELEMENT_KEY_FLAG_TRUE_RAN_PARAMETER_VAL_TYPE,
  ELEMENT_KEY_FLAG_FALSE_RAN_PARAMETER_VAL_TYPE, 
  STRUCTURE_RAN_PARAMETER_VAL_TYPE,
  LIST_RAN_PARAMETER_VAL_TYPE,

  END_RAN_PARAMETER_VAL_TYPE   
} ran_parameter_val_type_e ;


 // 9.3.11
typedef struct{

  ran_parameter_val_type_e type;
  union{
    ran_parameter_value_t flag_true;
    ran_parameter_value_t flag_false;
    ran_param_struct_t strct;
    ran_param_list_t lst;
  };

} ran_param_val_type_t ;

void free_ran_param_val_type(ran_param_val_type_t *src);

bool eq_ran_param_val_type(ran_param_val_type_t const* m0, ran_param_val_type_t const* m1);

#endif

