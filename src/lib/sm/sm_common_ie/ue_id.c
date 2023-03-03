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
      free_gnb_ue_id(&src->gnb);
      break;
    }

    case GNB_DU_UE_ID:
    {
      free_gnb_du_ue_id(&src->gnb_du);
      break;
    }

    case GNB_CU_UP_UE_ID:
    {
      free_gnb_cu_up_ue_id(&src->gnb_cu_up);
      break;
    }

    case NG_ENB_UE_ID:
    {
      free_ng_enb_ue_id(&src->ng_enb);
      break;
    }

    case NG_ENB_DU_UE_ID:
    {
      free_ng_enb_du_ue_id(&src->ng_enb_du);
      break;
    }

    case EN_GNB_UE_ID:
    {
      free_en_gnb_ue_id(&src->en_gnb);
      break;
    }

    case ENB_UE_ID:
    {
      free_enb_ue_id(&src->enb);
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

    if (m0->type != m1->type){
      assert(0!=0 && "Debug assert");
      return false;
    }

    switch (m0->type)
    {
    case GNB_UE_ID:
    {
      if (eq_gnb_ue_id(&m0->gnb, &m1->gnb) != true){

        assert(0!=0 && "Debug assert");
        return false;
      }
  
      break;
    }

    case GNB_DU_UE_ID:
    {
      if (eq_gnb_du_ue_id(&m0->gnb_du, &m1->gnb_du) != true)
        return false;

      break;
    }

    case GNB_CU_UP_UE_ID:
    {
      if (eq_gnb_cu_up_ue_id(&m0->gnb_cu_up, &m1->gnb_cu_up) != true)
        return false;

      break;
    }

    case NG_ENB_UE_ID:
    {
      if (eq_ng_enb_ue_id(&m0->ng_enb, &m1->ng_enb) != true)
        return false;

      break;
    }

    case NG_ENB_DU_UE_ID:
    {
      if (eq_ng_enb_du_ue_id(&m0->ng_enb_du, &m1->ng_enb_du) != true)
        return false;

      break;
    }

    case EN_GNB_UE_ID:
    {
      if (eq_en_gnb_ue_id(&m0->en_gnb, &m1->en_gnb) != true)
        return false;

      break;
    }

    case ENB_UE_ID:
    {
      if (eq_enb_ue_id(&m0->enb, &m1->enb) != true)
        return false;

      break;
    }

    default:
      assert(false && "Unknown UE ID Type");
    }

    return true;
}
