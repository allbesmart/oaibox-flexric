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

ran_function_name_t cp_kpm_ran_function_name(ran_function_name_t const * src)
{
  assert(src != NULL);

  ran_function_name_t dst = {0};

  dst.description = copy_byte_array(src->description);

  dst.short_name = copy_byte_array(src->short_name);

  dst.E2SM_OID = copy_byte_array(src->E2SM_OID);

  if (src->instance != NULL)
  {
    dst.instance = calloc(1, sizeof(*dst.instance));
    *dst.instance = *src->instance;
  }


  return dst;
}
