#include <assert.h>
#include <stdlib.h>

#include "gummei.h"

bool eq_gummei(gummei_t const * m0, gummei_t const * m1)
{
    assert(m0 != NULL);
    assert(m1 != NULL);

    if (eq_plmn(&m0->plmn_id, &m1->plmn_id) != true)
      return false;

    if (m0->mme_group_id != m1->mme_group_id)
      return false;

    if (m0->mme_code != m1->mme_code)
      return false;


    return true;
}
