#include <assert.h>

#include "../../../util/conversions.h"
#include "../../../sm/kpm_sm_v2.02/ie/asn/asn_constant.h"
#include "../../../sm/kpm_sm_v2.02/ie/asn/asn_SEQUENCE_OF.h"
#include "../../../sm/kpm_sm_v2.02/ie/asn/UEID-GNB-CU-F1AP-ID-List.h"
#include "../../../sm/kpm_sm_v2.02/ie/asn/UEID-GNB-CU-CP-E1AP-ID-List.h"

#include "enc_global_gnb_id.h"
#include "enc_global_ng_ran.h"



#include "enc_gnb.h"

UEID_GNB_t * enc_gNB_UE_asn(const gnb_t * gnb)
{
    UEID_GNB_t * gnb_asn = calloc(1, sizeof(UEID_GNB_t));
    assert(gnb_asn != NULL && "Memory exhausted");


    // AMF UE NGAP ID
    gnb_asn->amf_UE_NGAP_ID.buf = calloc(8, sizeof(uint8_t));
    assert(gnb_asn->amf_UE_NGAP_ID.buf != NULL && "Memory exhausted");

// Do not pass the ownership of the data one is pointer, the other no
    //gnb_asn->amf_UE_NGAP_ID.buf = gnb->amf_ue_ngap_id;
    memcpy(gnb_asn->amf_UE_NGAP_ID.buf, &gnb->amf_ue_ngap_id, 8);
    gnb_asn->amf_UE_NGAP_ID.size = 8;


    // GUAMI


    MCC_MNC_TO_PLMNID(gnb->guami.plmn_id.mcc, gnb->guami.plmn_id.mnc, gnb->guami.plmn_id.mnc_digit_len, &gnb_asn->guami.pLMNIdentity);

    AMF_REGION_TO_BIT_STRING(gnb->guami.amf_region_id, &gnb_asn->guami.aMFRegionID);

    AMF_SETID_TO_BIT_STRING(gnb->guami.amf_set_id, &gnb_asn->guami.aMFSetID);

    AMF_POINTER_TO_BIT_STRING(gnb->guami.amf_ptr, &gnb_asn->guami.aMFPointer);


    // gNB-CU UE F1AP ID List
    // C-ifCUDUseparated 

    if (gnb->gnb_cu_ue_f1ap_lst != NULL)
    {
        assert(gnb->gnb_cu_ue_f1ap_lst_len >=1 && gnb->gnb_cu_ue_f1ap_lst_len <= maxF1APid);

        for (size_t i = 0; i < gnb->gnb_cu_ue_f1ap_lst_len; i++)
        {
            UEID_GNB_CU_F1AP_ID_List_t * f1_item = calloc(1, sizeof(UEID_GNB_CU_F1AP_ID_List_t));
            f1_item = gnb->gnb_cu_ue_f1ap_lst[i];
            int rc1 = ASN_SEQUENCE_ADD(&gnb_asn->gNB_CU_UE_F1AP_ID_List->list, f1_item);
            assert(rc1 == 0);
        }
    }


    //gNB-CU-CP UE E1AP ID List
    //C-ifCPUPseparated 

    if (gnb->gnb_cu_cp_ue_e1ap_lst != NULL)
    {
        assert(gnb->gnb_cu_cp_ue_e1ap_lst_len >= 1 && gnb->gnb_cu_cp_ue_e1ap_lst_len <= maxE1APid);

        for (size_t i = 0; i < gnb->gnb_cu_cp_ue_e1ap_lst_len; i++)
        {
            UEID_GNB_CU_CP_E1AP_ID_List_t * e1_item = calloc(1, sizeof(UEID_GNB_CU_CP_E1AP_ID_List_t));
            e1_item = gnb->gnb_cu_cp_ue_e1ap_lst[i];
            int rc1 = ASN_SEQUENCE_ADD(&gnb_asn->gNB_CU_CP_UE_E1AP_ID_List->list, e1_item);
            assert(rc1 == 0);
        }

    }

    // RAN UE ID
    // Optional

    if (gnb->ran_ue_id != NULL)
    {
        gnb_asn->ran_UEID->buf = calloc(8, sizeof(*gnb_asn->ran_UEID->buf));
        gnb_asn->ran_UEID->buf = gnb->ran_ue_id;
        gnb_asn->ran_UEID->size = sizeof(gnb->ran_ue_id);
    }
    


    //  M-NG-RAN node UE XnAP ID
    // C- ifDCSetup

    if (gnb->ng_ran_node_ue_xnap_id != NULL)
    {
        gnb_asn->m_NG_RAN_UE_XnAP_ID = calloc(1, sizeof(*gnb_asn->m_NG_RAN_UE_XnAP_ID));
        gnb_asn->m_NG_RAN_UE_XnAP_ID = gnb->ng_ran_node_ue_xnap_id;
    }


    // Global gNB ID
    // 6.2.3.3
    // Optional

    gnb_asn->globalGNB_ID = enc_global_gnb_id_asn(&gnb->global_gnb_id);


    // Global NG-RAN Node ID
    // C-ifDCSetup
    gnb_asn->globalNG_RANNode_ID = enc_global_ng_ran_asn(&gnb->global_ng_ran_node_id);


    return gnb_asn;
}
