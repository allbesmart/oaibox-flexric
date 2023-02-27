#include <assert.h>

#include "dec_gnb_du.h"

gnb_du_t dec_gNB_DU_UE_asn(const UEID_GNB_DU_t * gnb_du_asn)
{
    gnb_du_t gnb_du = {0};

    // gNB CU UE F1AP
    gnb_du.gnb_cu_ue_f1ap = gnb_du_asn->gNB_CU_UE_F1AP_ID;


    // RAN UE ID
    // Optional

    if (gnb_du_asn->ran_UEID->buf != NULL)
    {
        gnb_du.ran_ue_id = calloc(1, sizeof(*gnb_du.ran_ue_id));
        memcpy(gnb_du.ran_ue_id, gnb_du_asn->ran_UEID->buf, 1);
    }

    return gnb_du;
}