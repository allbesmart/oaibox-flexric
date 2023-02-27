#ifndef RAN_PARAMETER_STRUCT_E2RC_h
#define RAN_PARAMETER_STRUCT_E2RC_h 

#include <stdbool.h>
#include <stdlib.h>

typedef struct{

  // [1-65535]
  size_t sz_ran_param_struct;
  struct ran_param_test_s* ran_param_struct;

} ran_param_struct_t;

void free_ran_param_struct(ran_param_struct_t* src);

bool eq_ran_param_struct(ran_param_struct_t const* m0, ran_param_struct_t const* m1);

#endif

