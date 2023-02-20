#include <assert.h>
#include <stddef.h>

#include "global_gnb_id.h"

bool eq_global_gnb_id(global_gnb_id_t const * m0, global_gnb_id_t const * m1)
{
    assert(m0 != NULL);
    assert(m1 != NULL);

    if (eq_plmn(&m0->plmn_id, &m1->plmn_id) != true)
      return false;

    if (m0->type != m1->type)
      return false;

    switch (m0->type)
    {
    case GNB_TYPE_ID:
        if (m0->gnb_id != m1->gnb_id)
          return false;
        break;
    
    default:
        assert(false && "Unknown gNB ID Type");
    }

    return true;
}
