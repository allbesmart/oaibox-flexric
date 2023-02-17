#include <assert.h>
#include <stdlib.h>

#include "ng_enb.h"

void free_ng_enb_ue_id(ng_enb_t * src)
{
    assert(src != NULL);

    if (src->ng_enb_cu_ue_w1ap_id != NULL)
        free(src->ng_enb_cu_ue_w1ap_id);

    if (src->ng_ran_node_ue_xnap_id != NULL)
      free(src->ng_ran_node_ue_xnap_id);

    if (src->global_ng_enb_id != NULL)
          free(src->global_ng_enb_id);

    if (src->global_ng_ran_node_id != NULL)
          free(src->global_ng_ran_node_id);

}

bool eq_ng_enb_ue_id(ng_enb_t const * m0, ng_enb_t const * m1)
{

    // AMF UE NGAP ID
    if (m0->amf_ue_ngap_id != m1->amf_ue_ngap_id)
      return false;
    
    // GUAMI
    if (eq_guami(&m0->guami, &m1->guami) != true)
      return false;
    
    // 6.2.3.22
    // C-if CU DU separated
    // ng-eNB-CU UE W1AP ID
    if (m0->ng_enb_cu_ue_w1ap_id != NULL && m1->ng_enb_cu_ue_w1ap_id != NULL && *m0->ng_enb_cu_ue_w1ap_id != *m1->ng_enb_cu_ue_w1ap_id)
      return false;
    
    // 6.2.3.19
    // C- ifDCSetup
    // M-NG-RAN node UE XnAP ID
    if (m0->ng_ran_node_ue_xnap_id != NULL && m1->ng_ran_node_ue_xnap_id != NULL && *m0->ng_ran_node_ue_xnap_id != *m1->ng_ran_node_ue_xnap_id)
      return false;
    
    // Global gNB ID
    if (m0->global_ng_enb_id != NULL && m1->global_ng_enb_id != NULL)
      assert(false && "Equivalency of Global NG eNB ID not yet implemented");

    // Global NG-RAN Node ID
    if (m0->global_ng_ran_node_id != NULL && m1->global_ng_ran_node_id != NULL)
      assert(false && "Equivalency of Global NG RAN Node ID not yet implemented");


    return true;
}
