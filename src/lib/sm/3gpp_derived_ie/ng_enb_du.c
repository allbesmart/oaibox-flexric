#include <assert.h>
#include <stdlib.h>

#include "ng_enb_du.h"

void free_ng_enb_du_ue_id(ng_enb_du_t * src)
{
    assert(src != NULL);

    // No memory allocated in the heap
    (void)src;

}

bool eq_ng_enb_du_ue_id(ng_enb_du_t const * m0, ng_enb_du_t const * m1)
{
    assert(m0 != NULL);
    assert(m1 != NULL);

    if (m0->ng_enb_cu_ue_w1ap_id != m1->ng_enb_cu_ue_w1ap_id)
        return false;

    return true;
}
