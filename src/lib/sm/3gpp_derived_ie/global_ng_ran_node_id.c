#include <assert.h>
#include <stddef.h>

#include "global_ng_ran_node_id.h"

bool eq_global_ng_ran_node_id(global_ng_ran_node_id_t const * m0, global_ng_ran_node_id_t const * m1)
{
    assert(m0 != NULL);
    assert(m1 != NULL);

    if (m0->type != m1->type)
      return false;

    switch (m0->type)
    {
    case GNB_GLOBAL_TYPE_ID:
        if (eq_global_gnb_id(&m0->global_gnb_id, &m1->global_gnb_id) != true)
          return false;
        break;
    
    case NG_ENB_GLOBAL_TYPE_ID:
        if (eq_global_ng_enb_id(&m0->global_ng_enb_id, &m1->global_ng_enb_id) != true)
          return false;
        break;

    default:
        assert(false && "Unknown Global NG eNB ID Type");
    }

    return true;
}
