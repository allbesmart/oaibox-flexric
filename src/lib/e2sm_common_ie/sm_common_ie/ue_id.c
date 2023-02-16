#include <assert.h>
#include <stdlib.h>

#include "ue_id.h"

void free_ue_id(ue_id_t * src)
{
    assert(src != NULL);

    switch (src->type)
    {
    case GNB_UE_ID:
    {
      if (src->gnb.gnb_cu_ue_f1ap_lst_len != 0)
        free(src->gnb.gnb_cu_ue_f1ap_lst);

      if (src->gnb.gnb_cu_cp_ue_e1ap_lst_len != 0)
        free(src->gnb.gnb_cu_cp_ue_e1ap_lst);

      if (src->gnb.ran_ue_id != NULL)
          free(src->gnb.ran_ue_id);

      if (src->gnb.ng_ran_node_ue_xnap_id != NULL)
          free(src->gnb.ng_ran_node_ue_xnap_id);

      if (src->gnb.global_gnb_id != NULL)
          free(src->gnb.global_gnb_id);

      if (src->gnb.global_ng_ran_node_id != NULL)
          free(src->gnb.global_ng_ran_node_id);

      break;
    }

    case GNB_DU_UE_ID:
    {
      if (src->gnb_du.ran_ue_id != NULL)
        free(src->gnb_du.ran_ue_id);

      break;
    }

    case GNB_CU_UP_UE_ID:
    {
      if (src->gnb_cu_up.ran_ue_id != NULL)
        free(src->gnb_cu_up.ran_ue_id);

      break;
    }

    case NG_ENB_UE_ID:
    {
      if (src->ng_enb.ng_enb_cu_ue_w1ap_id != NULL)
        free(src->ng_enb.ng_enb_cu_ue_w1ap_id);

      if (src->ng_enb.ng_ran_node_ue_xnap_id != NULL)
        free(src->ng_enb.ng_ran_node_ue_xnap_id);

      if (src->ng_enb.global_ng_enb_id != NULL)
            free(src->ng_enb.global_ng_enb_id);

      if (src->ng_enb.global_ng_ran_node_id != NULL)
            free(src->ng_enb.global_ng_ran_node_id);
      
      break;
    }

    case NG_ENB_DU_UE_ID:
    {
      // No memory allocated in the heap
      (void)src->ng_enb_du;
      break;
    }

    case EN_GNB_UE_ID:
    {
      if (src->en_gnb.enb_ue_x2ap_id_extension != NULL)
        free(src->en_gnb.enb_ue_x2ap_id_extension);

      if (src->en_gnb.gnb_cu_ue_f1ap_lst != NULL)
        free(src->en_gnb.gnb_cu_ue_f1ap_lst);

      if (src->en_gnb.gnb_cu_cp_ue_e1ap_lst_len != 0)
        free(src->en_gnb.gnb_cu_cp_ue_e1ap_lst);

      if (src->en_gnb.ran_ue_id != NULL)
        free(src->en_gnb.ran_ue_id);      

      break;
    }

    case ENB_UE_ID:
    {
      if (src->enb.enb_ue_x2ap_id != NULL)
        free(src->enb.enb_ue_x2ap_id);

      if (src->enb.enb_ue_x2ap_id_extension != NULL)
        free(src->enb.enb_ue_x2ap_id_extension);

      if (src->enb.global_enb_id != NULL)
        free(src->enb.global_enb_id);

      break;
    }

    default:
      assert(false && "Unknown UE ID Type");
    }



}

bool eq_ue_id(ue_id_t const * m0, ue_id_t const * m1)
{
    assert(m0 != NULL);
    assert(m1 != NULL);

    if (m0->type != m1->type)
      return false;

    switch (m0->type)
    {
    case GNB_UE_ID:
    {
        // AMF UE NGAP ID
        if (m0->gnb.amf_ue_ngap_id != m1->gnb.amf_ue_ngap_id)
          return false;

        // GUAMI => to add in guami.h/c
        if (eq_plmn(&m0->gnb.guami.plmn_id, &m1->gnb.guami.plmn_id) != true)
          return false;

        if (m0->gnb.guami.amf_region_id != m1->gnb.guami.amf_region_id)
          return false;

        // to be solved, encoding problem with bits
        // if (m0->gnb.guami.amf_set_id != m1->gnb.guami.amf_set_id)
        //   return false;

        // if (m0->gnb.guami.amf_ptr != m1->gnb.guami.amf_ptr)
        //   return false;

        // gNB-CU UE F1AP ID List
        if (m0->gnb.gnb_cu_ue_f1ap_lst_len != m1->gnb.gnb_cu_ue_f1ap_lst_len)
          return false;

        for (size_t i = 0; i < m0->gnb.gnb_cu_ue_f1ap_lst_len; i++)
        {
            if (m0->gnb.gnb_cu_ue_f1ap_lst[i] != m1->gnb.gnb_cu_ue_f1ap_lst[i])
              return false;
        }


        // gNB-CU-CP UE E1AP
        if (m0->gnb.gnb_cu_cp_ue_e1ap_lst_len != m1->gnb.gnb_cu_cp_ue_e1ap_lst_len)
          return false;

        for (size_t i = 0; i < m0->gnb.gnb_cu_cp_ue_e1ap_lst_len; i++)
        {
            if (m0->gnb.gnb_cu_cp_ue_e1ap_lst[i] != m1->gnb.gnb_cu_cp_ue_e1ap_lst[i])
              return false;
        }

        // RAN UE ID
        if (*m0->gnb.ran_ue_id != *m1->gnb.ran_ue_id)
          return false;

        // M-NG-RAN node UE XnAP ID
        if (*m0->gnb.ng_ran_node_ue_xnap_id != *m1->gnb.ng_ran_node_ue_xnap_id)
          return false;

        // Global gNB ID
        if (m0->gnb.global_gnb_id != NULL && m1->gnb.global_gnb_id != NULL)
          assert(false && "Equivalency of Global gNB ID not yet implemented");
    
        // Global NG-RAN Node ID
        if (m0->gnb.global_ng_ran_node_id != NULL && m1->gnb.global_ng_ran_node_id != NULL)
          assert(false && "Equivalency of Global NG RAN Node ID not yet implemented");
    

        break;
    }

    case GNB_DU_UE_ID:
    {
      // gNB DU UE F1AP
      if (m0->gnb_du.gnb_cu_ue_f1ap != m1->gnb_du.gnb_cu_ue_f1ap)
        return false;

      // RAN UE ID
      if (*m0->gnb_du.ran_ue_id != *m1->gnb_du.ran_ue_id)
        return false;

      break;
    }

    case GNB_CU_UP_UE_ID:
    {
      // gNB CU CP UE E1AP
      if (m0->gnb_cu_up.gnb_cu_cp_ue_e1ap != m1->gnb_cu_up.gnb_cu_cp_ue_e1ap)
        return false;

      // RAN UE ID
      if (*m0->gnb_cu_up.ran_ue_id != *m1->gnb_cu_up.ran_ue_id)
        return false;

      break;
    }

    case NG_ENB_UE_ID:
    {
      // AMF UE NGAP ID
      if (m0->ng_enb.amf_ue_ngap_id != m1->ng_enb.amf_ue_ngap_id)
        return false;

      // GUAMI => to add in guami.h/c
      if (eq_plmn(&m0->ng_enb.guami.plmn_id, &m1->ng_enb.guami.plmn_id) != true)
        return false;

      if (m0->ng_enb.guami.amf_region_id != m1->ng_enb.guami.amf_region_id)
        return false;

      // to be solved, encoding problem with bits
      // if (m0->ng_enb.guami.amf_set_id != m1->ng_enb.guami.amf_set_id)
      //   return false;

      // if (m0->ng_enb.guami.amf_ptr != m1->ng_enb.guami.amf_ptr)
      //   return false;

      // 6.2.3.22
      // C-if CU DU separated
      // ng-eNB-CU UE W1AP ID
      if (*m0->ng_enb.ng_enb_cu_ue_w1ap_id != *m1->ng_enb.ng_enb_cu_ue_w1ap_id)
        return false;

      // 6.2.3.19
      // C- ifDCSetup
      // M-NG-RAN node UE XnAP ID
      if (*m0->ng_enb.ng_ran_node_ue_xnap_id != *m1->ng_enb.ng_ran_node_ue_xnap_id)
        return false;

      // Global gNB ID
      if (m0->ng_enb.global_ng_enb_id != NULL && m1->ng_enb.global_ng_enb_id != NULL)
        assert(false && "Equivalency of Global NG eNB ID not yet implemented");
    
      // Global NG-RAN Node ID
      if (m0->ng_enb.global_ng_ran_node_id != NULL && m1->ng_enb.global_ng_ran_node_id != NULL)
        assert(false && "Equivalency of Global NG RAN Node ID not yet implemented");

      break;
    }

    case NG_ENB_DU_UE_ID:
    {
      if (m0->ng_enb_du.ng_enb_cu_ue_w1ap_id != m1->ng_enb_du.ng_enb_cu_ue_w1ap_id)
        return false;

      break;
    }

    case EN_GNB_UE_ID:
    {
      // 6.2.3.23
      // Mandatory
      // MeNB UE X2AP ID
      if (m0->en_gnb.enb_ue_x2ap_id != m1->en_gnb.enb_ue_x2ap_id)
        return false;

      // 6.2.3.24
      // OPTIONAL
      // MeNB UE X2AP ID Extension
      if (*m0->en_gnb.enb_ue_x2ap_id_extension != *m1->en_gnb.enb_ue_x2ap_id_extension)
        return false;

      // 6.2.3.9
      // Mandatory
      // Global eNB ID
      if (eq_plmn(&m0->en_gnb.global_enb_id.plmn_id, &m1->en_gnb.global_enb_id.plmn_id) != true)
        return false;

      if (m0->en_gnb.global_enb_id.type != m1->en_gnb.global_enb_id.type)
        return false;

      switch (m0->en_gnb.global_enb_id.type)
      {
      case MACRO_ENB_TYPE_ID:
        if (m0->en_gnb.global_enb_id.macro_enb_id != m1->en_gnb.global_enb_id.macro_enb_id)
          return false;
        break;

      case HOME_ENB_TYPE_ID:
        if (m0->en_gnb.global_enb_id.home_enb_id != m1->en_gnb.global_enb_id.home_enb_id)
          return false;
        break;

      case SHORT_MACRO_ENB_TYPE_ID:
        if (m0->en_gnb.global_enb_id.short_macro_enb_id != m1->en_gnb.global_enb_id.short_macro_enb_id)
          return false;
        break;

      case LONG_MACRO_ENB_TYPE_ID:
        if (m0->en_gnb.global_enb_id.long_macro_enb_id != m1->en_gnb.global_enb_id.long_macro_enb_id)
          return false;
        break;
      
      default:
        assert(false && "Unknown eNB Type");
      }


      // 6.2.3.21
      // gNB-CU UE F1AP ID
      // C-ifCUDUseparated
      if (*m0->en_gnb.gnb_cu_ue_f1ap_lst != *m1->en_gnb.gnb_cu_ue_f1ap_lst)
        return false;

      // gNB-CU-CP UE E1AP ID List
      // C-ifCPUPseparated 
      if (m0->en_gnb.gnb_cu_cp_ue_e1ap_lst_len != m1->en_gnb.gnb_cu_cp_ue_e1ap_lst_len)
          return false;

      for (size_t i = 0; i < m0->en_gnb.gnb_cu_cp_ue_e1ap_lst_len; i++)
      {
          if (m0->en_gnb.gnb_cu_cp_ue_e1ap_lst[i] != m1->en_gnb.gnb_cu_cp_ue_e1ap_lst[i])
            return false;
      }

      // RAN UE ID
      // Optional
      // 6.2.3.25
      if (*m0->en_gnb.ran_ue_id != *m1->en_gnb.ran_ue_id)
          return false;


      break;
    }

    case ENB_UE_ID:
    {
      // 6.2.3.26
      // Mandatory
      // MME UE S1AP ID
      if (m0->enb.mme_ue_s1ap_id != m1->enb.mme_ue_s1ap_id)
        return false;

      // 6.2.3.18
      // Mandatory
      // GUMMEI
      if (eq_plmn(&m0->enb.gummei.plmn_id, &m1->enb.gummei.plmn_id) != true)
        return false;

      if (m0->enb.gummei.mme_group_id != m1->enb.gummei.mme_group_id)
        return false;

      if (m0->enb.gummei.mme_code != m1->enb.gummei.mme_code)
        return false;

      // 6.2.3.23
      // C-ifDCSetup
      // MeNB UE X2AP ID
      if (*m0->enb.enb_ue_x2ap_id != *m1->enb.enb_ue_x2ap_id)
        return false;

      // 6.2.3.24
      // C-ifDCSetup
      // MeNB UE X2AP ID Extension
      if (*m0->enb.enb_ue_x2ap_id_extension != *m1->enb.enb_ue_x2ap_id_extension)
        return false;

      // 6.2.3.9
      // C-ifDCSetup
      // Global eNB ID

      if (eq_plmn(&m0->enb.global_enb_id->plmn_id, &m1->enb.global_enb_id->plmn_id) != true)
        return false;

      if (m0->enb.global_enb_id->type != m1->enb.global_enb_id->type)
        return false;

      switch (m0->enb.global_enb_id->type)
      {
      case MACRO_ENB_TYPE_ID:
        if (m0->enb.global_enb_id->macro_enb_id != m1->enb.global_enb_id->macro_enb_id)
          return false;
        break;

      case HOME_ENB_TYPE_ID:
        if (m0->enb.global_enb_id->home_enb_id != m1->enb.global_enb_id->home_enb_id)
          return false;
        break;

      case SHORT_MACRO_ENB_TYPE_ID:
        if (m0->enb.global_enb_id->short_macro_enb_id != m1->enb.global_enb_id->short_macro_enb_id)
          return false;
        break;

      case LONG_MACRO_ENB_TYPE_ID:
        if (m0->enb.global_enb_id->long_macro_enb_id != m1->enb.global_enb_id->long_macro_enb_id)
          return false;
        break;
      
      default:
        assert(false && "Unknown eNB Type");
      }

      break;
    }

    default:
      assert(false && "Unknown UE ID Type");
    }

    return true;
}
