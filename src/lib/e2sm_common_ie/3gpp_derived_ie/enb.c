#include <assert.h>
#include <stdlib.h>

#include "enb.h"

void free_enb_ue_id(enb_t * src)
{
    assert(src != NULL);

    if (src->enb_ue_x2ap_id != NULL)
        free(src->enb_ue_x2ap_id);

    if (src->enb_ue_x2ap_id_extension != NULL)
      free(src->enb_ue_x2ap_id_extension);

    if (src->global_enb_id != NULL)
      free(src->global_enb_id);

}

bool eq_enb_ue_id(enb_t const * m0, enb_t const * m1)
{
    assert(m0 != NULL);
    assert(m1 != NULL);

    // 6.2.3.26
    // Mandatory
    // MME UE S1AP ID
    if (m0->mme_ue_s1ap_id != m1->mme_ue_s1ap_id)
      return false;

    // 6.2.3.18
    // Mandatory
    // GUMMEI
    if (eq_gummei(&m0->gummei, &m1->gummei) != true)
      return false;

    // 6.2.3.23
    // C-ifDCSetup
    // MeNB UE X2AP ID
    if (m0->enb_ue_x2ap_id != NULL && m1->enb_ue_x2ap_id != NULL && *m0->enb_ue_x2ap_id != *m1->enb_ue_x2ap_id)
      return false;

    // 6.2.3.24
    // C-ifDCSetup
    // MeNB UE X2AP ID Extension
    if (m0->enb_ue_x2ap_id_extension != NULL && m1->enb_ue_x2ap_id_extension != NULL && *m0->enb_ue_x2ap_id_extension != *m1->enb_ue_x2ap_id_extension)
      return false;

    // 6.2.3.9
    // C-ifDCSetup
    // Global eNB ID
    if (eq_global_enb_id(m0->global_enb_id, m1->global_enb_id) != true)
      return false;


    return true;
}
