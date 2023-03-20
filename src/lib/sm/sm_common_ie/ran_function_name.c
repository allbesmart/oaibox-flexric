#include <assert.h>
#include <stdlib.h>

#include "ran_function_name.h"

void free_kpm_ran_function_name(ran_function_name_t* src)
{
    assert(src != NULL);

    free_byte_array(src->name);

    free_byte_array(src->oid);

    free_byte_array(src->description);

    if (src->instance != NULL)
      free(src->instance);

}

bool eq_kpm_ran_function_name(ran_function_name_t const * m0, ran_function_name_t const * m1)
{
  assert(m0 != NULL);
  assert(m1 != NULL);

  if (eq_byte_array(&m0->description, &m1->description) != true)
    return false;

  if (eq_byte_array(&m0->name, &m1->name) != true)
    return false;

  if (eq_byte_array(&m0->oid, &m1->oid) != true)
    return false;

  if ((m0->instance != NULL || m0->instance != NULL) && *m0->instance != *m1->instance)
    return false;

  return true;
}
