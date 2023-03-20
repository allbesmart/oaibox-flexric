#include <assert.h>
#include <stdlib.h>

#include "gummei.h"

bool eq_gummei(gummei_t const * m0, gummei_t const * m1)
{
    assert(m0 != NULL);
    assert(m1 != NULL);

    if (eq_e2sm_plmn(&m0->plmn_id, &m1->plmn_id) != true)
      return false;

    if (m0->mme_group_id != m1->mme_group_id)
      return false;

    if (m0->mme_code != m1->mme_code)
      return false;


    return true;
}


gummei_t cp_gummei(gummei_t const* src)
{
  assert(src != NULL);

  gummei_t dst = {0}; 

  dst.plmn_id = cp_e2sm_plmn(&src->plmn_id);

  dst.mme_group_id = src->mme_group_id;

  dst.mme_code = src->mme_code;

  return dst;
}

