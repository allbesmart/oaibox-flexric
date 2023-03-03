#include <assert.h>
#include <stdlib.h>

#include "gnb_cu_up.h"

void free_gnb_cu_up_ue_id(gnb_cu_up_t * src)
{
    assert(src != NULL);

    if (src->ran_ue_id != NULL)
        free(src->ran_ue_id);

}

bool eq_gnb_cu_up_ue_id(gnb_cu_up_t const * m0, gnb_cu_up_t const * m1)
{
    assert(m0 != NULL);
    assert(m1 != NULL);

    // gNB CU CP UE E1AP
    if (m0->gnb_cu_cp_ue_e1ap != m1->gnb_cu_cp_ue_e1ap)
      return false;

    // RAN UE ID
    if (m0->ran_ue_id != NULL && m1->ran_ue_id != NULL && *m0->ran_ue_id != *m1->ran_ue_id)
      return false;

    return true;
}
