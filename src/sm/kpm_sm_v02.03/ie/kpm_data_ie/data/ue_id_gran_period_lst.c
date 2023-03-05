#include <assert.h>

#include "ue_id_gran_period_lst.h"

void free_kpm_ue_id_gran_period_lst(ue_id_gran_period_lst_t* src)
{
  assert(src != NULL);

  if (src->matched_ue_lst.ue_lst != NULL)
  {
    for (size_t i = 0; i<src->matched_ue_lst.ue_lst_len; i++)
    {
      free_ue_id(&src->matched_ue_lst.ue_lst[i]);
    }
    
    free(src->matched_ue_lst.ue_lst);
  }

}

bool eq_kpm_ue_id_gran_period_lst(ue_id_gran_period_lst_t const* m0, ue_id_gran_period_lst_t const* m1)
{
  assert(m0 != NULL);
  assert(m1 != NULL);

  if (m0->num_matched_ue != m1->num_matched_ue)
    return false;

  switch (m0->num_matched_ue)
  {
  case NONE_MATCHED_UE:
    if (m0->no_matched_ue != m1->no_matched_ue)
      return false;
    break;

  case ONE_OR_MORE_MATCHED_UE:
    if (m0->matched_ue_lst.ue_lst_len != m1->matched_ue_lst.ue_lst_len)
      return false;

    for (size_t i = 0; i<m0->matched_ue_lst.ue_lst_len; i++)
    {
        if (eq_ue_id(&m0->matched_ue_lst.ue_lst[i], &m1->matched_ue_lst.ue_lst[i]) != true)
          return false;
    }
    break;
  
  default:
    break;
  }


  return true;
}
