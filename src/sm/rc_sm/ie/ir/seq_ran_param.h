#ifndef SEQUENCE_RAN_PARAMETER_E2SM_H
#define SEQUENCE_RAN_PARAMETER_E2SM_H 

#include <stdbool.h>
#include <stdint.h>

#include "ran_parameter_value_type.h"

typedef struct{
  //RAN Parameter ID
  //Mandatory
  //9.3.8
  // [1 - 4294967295]
  uint32_t ran_param_id;

  // RAN Parameter Value Type
  // 9.3.11
  // Mandatory
  ran_param_val_type_t ran_param_val;

} seq_ran_param_t;

void free_seq_ran_param(seq_ran_param_t* src);

bool eq_seq_ran_param(seq_ran_param_t const* m0, seq_ran_param_t const* m1);

#endif

