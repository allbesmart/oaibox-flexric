#include <assert.h>

#include "../../../sm/kpm_sm_v2.02/ie/asn/asn_constant.h"
#include "../../../sm/kpm_sm_v2.02/ie/asn/UEID-GNB-CU-CP-E1AP-ID-List.h"

#include "dec_en_gnb.h"
#include "dec_global_enb_id.h"

en_gnb_t dec_en_gNB_UE_asn(const UEID_EN_GNB_t * en_gnb_asn)
{
    en_gnb_t en_gnb = {0};

    // Mandatory
    // MeNB UE X2AP ID
    en_gnb.enb_ue_x2ap_id = en_gnb_asn->m_eNB_UE_X2AP_ID;

    // OPTIONAL
    // MeNB UE X2AP ID Extension
    if (en_gnb_asn->m_eNB_UE_X2AP_ID_Extension != NULL)
    {
        en_gnb.enb_ue_x2ap_id_extension = calloc(1, sizeof(*en_gnb.enb_ue_x2ap_id_extension));
        en_gnb.enb_ue_x2ap_id_extension = en_gnb_asn->m_eNB_UE_X2AP_ID_Extension;
    }


    // Mandatory
    // Global eNB ID

    en_gnb.global_enb_id = *dec_global_enb_id_asn(&en_gnb_asn->globalENB_ID);


    // gNB-CU UE F1AP ID
    // C-ifCUDUseparated 
    if (en_gnb_asn->gNB_CU_UE_F1AP_ID != NULL)
    {
        en_gnb.gnb_cu_ue_f1ap_lst = calloc(1, sizeof(*en_gnb.gnb_cu_ue_f1ap_lst));
        en_gnb.gnb_cu_ue_f1ap_lst = en_gnb_asn->gNB_CU_UE_F1AP_ID;
    }


    // gNB-CU-CP UE E1AP ID List
    // C-ifCPUPseparated 

    if (en_gnb_asn->gNB_CU_CP_UE_E1AP_ID_List->list.count != 0)
    {
        assert(en_gnb_asn->gNB_CU_CP_UE_E1AP_ID_List->list.count >= 1 && en_gnb_asn->gNB_CU_CP_UE_E1AP_ID_List->list.count <= maxE1APid);
        en_gnb.gnb_cu_cp_ue_e1ap_lst_len = en_gnb_asn->gNB_CU_CP_UE_E1AP_ID_List->list.count;
        en_gnb.gnb_cu_cp_ue_e1ap_lst = calloc(1, sizeof(*en_gnb.gnb_cu_cp_ue_e1ap_lst));

        for (size_t i = 0; i < en_gnb.gnb_cu_cp_ue_e1ap_lst_len; i++)
        {
            en_gnb.gnb_cu_cp_ue_e1ap_lst[i] = en_gnb_asn->gNB_CU_CP_UE_E1AP_ID_List->list.array[i];
        }
    }
    else
    {
        en_gnb.gnb_cu_cp_ue_e1ap_lst_len = 0;
    }


    // RAN UE ID
    // Optional

    if (en_gnb_asn->ran_UEID->buf != NULL)
    {
        en_gnb.ran_ue_id = calloc(1, sizeof(*en_gnb.ran_ue_id));
        en_gnb.ran_ue_id = en_gnb_asn->ran_UEID->buf;
    }


    return en_gnb;
}