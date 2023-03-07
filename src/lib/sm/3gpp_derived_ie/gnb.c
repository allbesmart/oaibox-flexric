#include <assert.h>
#include <stdlib.h>

#include "gnb.h"


void free_gnb_ue_id(gnb_t * src)
{
    assert(src != NULL);

    if (src->gnb_cu_ue_f1ap_lst_len != 0)
        free(src->gnb_cu_ue_f1ap_lst);

    if (src->gnb_cu_cp_ue_e1ap_lst_len != 0)
      free(src->gnb_cu_cp_ue_e1ap_lst);

    if (src->ran_ue_id != NULL)
        free(src->ran_ue_id);

    if (src->ng_ran_node_ue_xnap_id != NULL)
        free(src->ng_ran_node_ue_xnap_id);

    if (src->global_gnb_id != NULL)
        free(src->global_gnb_id);

    if (src->global_ng_ran_node_id != NULL)
        free(src->global_ng_ran_node_id);

}


bool eq_gnb_ue_id(gnb_t const * m0, gnb_t const * m1)
{
    assert(m0 != NULL);
    assert(m1 != NULL);

    // AMF UE NGAP ID
    if (m0->amf_ue_ngap_id != m1->amf_ue_ngap_id){
      assert(0!=0 && "Debug assert");
      return false;
    }

    // GUAMI
    if (eq_guami(&m0->guami, &m1->guami) != true){
      assert(0!=0 && "Debug assert");
      return false;
    }

    // gNB-CU UE F1AP ID List
    if (m0->gnb_cu_ue_f1ap_lst_len != m1->gnb_cu_ue_f1ap_lst_len)
      return false;
   
    for (size_t i = 0; i < m0->gnb_cu_ue_f1ap_lst_len; i++)
    {
        if (m0->gnb_cu_ue_f1ap_lst[i] != m1->gnb_cu_ue_f1ap_lst[i])
          return false;
    }
    
    // gNB-CU-CP UE E1AP
    if (m0->gnb_cu_cp_ue_e1ap_lst_len != m1->gnb_cu_cp_ue_e1ap_lst_len)
      return false;
    
    for (size_t i = 0; i < m0->gnb_cu_cp_ue_e1ap_lst_len; i++)
    {
        if (m0->gnb_cu_cp_ue_e1ap_lst[i] != m1->gnb_cu_cp_ue_e1ap_lst[i])
          return false;
    }
   
    // RAN UE ID
    if (m0->ran_ue_id != NULL && m1->ran_ue_id != NULL && *m0->ran_ue_id != *m1->ran_ue_id)
      return false;
    
    // M-NG-RAN node UE XnAP ID
    if (m0->ng_ran_node_ue_xnap_id != NULL && m1->ng_ran_node_ue_xnap_id != NULL && *m0->ng_ran_node_ue_xnap_id != *m1->ng_ran_node_ue_xnap_id)
      return false;
    
    // Global gNB ID
    if (m0->global_gnb_id != NULL && m1->global_gnb_id != NULL)
    {
      if (eq_global_gnb_id(m0->global_gnb_id, m1->global_gnb_id) != true)
        return false;
    }
    

    // Global NG-RAN Node ID
    if (m0->global_ng_ran_node_id != NULL && m1->global_ng_ran_node_id != NULL)
      if (eq_global_ng_ran_node_id(m0->global_ng_ran_node_id, m0->global_ng_ran_node_id) != true)
        return false;

    return true;
}
