#include "ran_param_list.h"
#include "ran_param_test.h"

#include <assert.h>



void free_ran_param_list(ran_param_list_t* src)
{
  assert(src != NULL);

  // [1- 65535]
  assert(src->sz_lst > 0 && src->sz_lst < 65536);

  for(size_t i  = 0; i < src->sz_lst; ++i){
    free_ran_param_test(&src->ran_param_test[i]);
  }

  assert(src->ran_param_test != NULL);
  free(src->ran_param_test);
}


bool eq_ran_param_list(ran_param_list_t const* m0, ran_param_list_t const* m1)
{
  if(m0 == m1)
    return true;

  if(m0 == NULL || m1 == NULL)
    return false;

  if(m0->sz_lst != m1->sz_lst)
    return false;

  for(size_t i = 0; i < m0->sz_lst; ++i){
    if(eq_ran_param_test(&m0->ran_param_test[i], &m1->ran_param_test[i]  )  == false)
      return false;
  }

  return true;
}


