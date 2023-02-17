#include <assert.h>
#include <stdlib.h>

#include "guami.h"

bool eq_guami(guami_t const * m0, guami_t const * m1)
{
  assert(m0 != NULL);
  assert(m1 != NULL);

  if (eq_plmn(&m0->plmn_id, &m1->plmn_id) != true)
    return false;

  if (m0->amf_region_id != m1->amf_region_id)
    return false;

  // to be solved, encoding problem with bits
  if (m0->amf_set_id != m1->amf_set_id)
    return false;

  if (m0->amf_ptr != m1->amf_ptr)
    return false;

  return true;
}

