#include <assert.h>
#include <stdlib.h>

#include "en_gnb.h"

void free_en_gnb_ue_id(en_gnb_t * src)
{
    assert(src != NULL);

    if (src->enb_ue_x2ap_id_extension != NULL)
        free(src->enb_ue_x2ap_id_extension);

    if (src->gnb_cu_ue_f1ap_lst != NULL)
      free(src->gnb_cu_ue_f1ap_lst);

    if (src->gnb_cu_cp_ue_e1ap_lst_len != 0)
      free(src->gnb_cu_cp_ue_e1ap_lst);

    if (src->ran_ue_id != NULL)
      free(src->ran_ue_id);  

}

bool eq_en_gnb_ue_id(en_gnb_t const * m0, en_gnb_t const * m1)
{
    assert(m0 != NULL);
    assert(m1 != NULL);

    // 6.2.3.23
    // Mandatory
    // MeNB UE X2AP ID
    if (m0->enb_ue_x2ap_id != m1->enb_ue_x2ap_id)
      return false;

    // 6.2.3.24
    // OPTIONAL
    // MeNB UE X2AP ID Extension
    if (m0->enb_ue_x2ap_id_extension != NULL && m1->enb_ue_x2ap_id_extension != NULL && *m0->enb_ue_x2ap_id_extension != *m1->enb_ue_x2ap_id_extension)
      return false;

    // 6.2.3.9
    // Mandatory
    // Global eNB ID
    if (eq_global_enb_id(&m0->global_enb_id, &m1->global_enb_id) != true)
      return false;

    // 6.2.3.21
    // gNB-CU UE F1AP ID
    // C-ifCUDUseparated
    if (m0->gnb_cu_ue_f1ap_lst != NULL && m1->gnb_cu_ue_f1ap_lst != NULL && *m0->gnb_cu_ue_f1ap_lst != *m1->gnb_cu_ue_f1ap_lst)
      return false;

    // gNB-CU-CP UE E1AP ID List
    // C-ifCPUPseparated 
    if (m0->gnb_cu_cp_ue_e1ap_lst_len != m1->gnb_cu_cp_ue_e1ap_lst_len)
        return false;

    for (size_t i = 0; i < m0->gnb_cu_cp_ue_e1ap_lst_len; i++)
    {
        if (m0->gnb_cu_cp_ue_e1ap_lst[i] != m1->gnb_cu_cp_ue_e1ap_lst[i])
          return false;
    }

    // RAN UE ID
    // Optional
    // 6.2.3.25
    if (m0->ran_ue_id != NULL && m1->ran_ue_id != NULL && *m0->ran_ue_id != *m1->ran_ue_id)
        return false;


    return true;
}
