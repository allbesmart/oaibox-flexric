#ifndef RAN_PARAMETER_LIST_E2RC_H
#define RAN_PARAMETER_LIST_E2RC_H 

#include <stdbool.h>
#include <stdlib.h>

typedef struct{

  // [1- 65535]
  size_t sz_lst;
  struct ran_param_test_s* ran_param_test;

} ran_param_list_t;

void free_ran_param_list(ran_param_list_t* src);

bool eq_ran_param_list(ran_param_list_t const* m0, ran_param_list_t const* m1);

#endif

