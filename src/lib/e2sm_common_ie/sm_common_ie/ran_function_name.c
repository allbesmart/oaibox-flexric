#include <assert.h>
#include <stdlib.h>

#include "ran_function_name.h"

void free_kpm_ran_function_name(ran_function_name_t* src)
{
    assert(src != NULL);

    free_byte_array(src->description);
    free_byte_array(src->E2SM_OID);
    free_byte_array(src->short_name);

    if (src->instance != NULL)
      free(src->instance);

}

bool eq_kpm_ran_function_name(ran_function_name_t const * m0, ran_function_name_t const * m1)
{
  assert(m0 != NULL);
  assert(m1 != NULL);

  if (eq_byte_array(&m0->description, &m1->description) != true)
    return false;

  if (eq_byte_array(&m0->short_name, &m1->short_name) != true)
    return false;

  if (eq_byte_array(&m0->E2SM_OID, &m1->E2SM_OID) != true)
    return false;

  if ((m0->instance != NULL || m0->instance != NULL) && *m0->instance != *m1->instance)
    return false;

  return true;
}
