#include "ran_param_test_struct.h"
#include "ran_param_test.h"

#include <assert.h>

void free_ran_param_test_strct(ran_param_test_strct_t* src)
{
  assert(src != NULL);

  // [1- 65535]
  assert(src->sz_strct > 0 && src->sz_strct <  65535 +1);
  // RAN Parameter Testing
  // 9.3.30
  for(size_t i = 0; i < src->sz_strct; ++i) {
    free_ran_param_test(&src->ran_param_test[i]);
  }

  free(src->ran_param_test);

}

bool eq_ran_param_test_strct(ran_param_test_strct_t const* m0, ran_param_test_strct_t const* m1)
{
  if(m0 == m1)
    return true;

  if(m0 == NULL || m1 == NULL)
    return false;

  if(m0->sz_strct != m1->sz_strct)
    return false;

  for(size_t i = 0; i < m0->sz_strct; ++i){
    if(eq_ran_param_test(&m0->ran_param_test[i], &m1->ran_param_test[i]) == false)
      return false;
  }

  return true;
}

