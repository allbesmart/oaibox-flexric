#include <assert.h>
#include <stddef.h>

#include "global_ng_enb_id.h"

bool eq_global_ng_enb_id(global_ng_enb_id_t const * m0, global_ng_enb_id_t const * m1)
{
    assert(m0 != NULL);
    assert(m1 != NULL);

    if (eq_plmn(&m0->plmn_id, &m1->plmn_id) != true)
      return false;

    if (m0->type != m1->type)
      return false;

    switch (m0->type)
    {
    case MACRO_NG_ENB_TYPE_ID:
        if (m0->macro_ng_enb_id != m1->macro_ng_enb_id)
          return false;
        break;

    case SHORT_MACRO_NG_ENB_TYPE_ID:
        if (m0->short_macro_ng_enb_id != m1->short_macro_ng_enb_id)
          return false;
        break;

    case LONG_MACRO_NG_ENB_TYPE_ID:
        if (m0->long_macro_ng_enb_id != m1->long_macro_ng_enb_id)
          return false;
        break;
    
    default:
        assert(false && "Unknown Global NG eNB ID Type");
    }

    return true;
}
