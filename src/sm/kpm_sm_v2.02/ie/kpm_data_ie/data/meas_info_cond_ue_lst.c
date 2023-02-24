#include <assert.h>

#include "meas_info_cond_ue_lst.h"

void free_kpm_meas_info_cond_ue(meas_info_cond_ue_lst_t* src)
{
  assert(src != NULL);

  // Measurement Type
  if (src->meas_type.type ==  NAME_MEAS_TYPE)
    free_byte_array(src->meas_type.name);

  // Matching Condition Format 3
  // [1, 32768]
  for (size_t i = 0; i<src->matching_cond_lst_len; i++)
    free_matching_cond_frm_3(&src->matching_cond_lst[i]);
  free(src->matching_cond_lst);
  
  // List of matched UE IDs
  // Optional [0, 65535]
  if (src->ue_id_matched_lst != NULL)
  {
    for (size_t i = 0; i<src->ue_id_matched_lst_len; i++)
      free_ue_id(&src->ue_id_matched_lst[i]);
  }
  free(src->ue_id_matched_lst);

  // Sequence of Matched UE IDs for Granularity Periods
  // not yet implemented in ASN.1

}


bool eq_kpm_meas_info_cond_ue(meas_info_cond_ue_lst_t const* m0, meas_info_cond_ue_lst_t const* m1)
{
  assert(m0 != NULL);
  assert(m1 != NULL);

  // Measurement Type
  if (eq_meas_type(&m0->meas_type, &m1->meas_type) != true)
    return false;

  // Matching Condition Format 3
  // [1, 32768]
  if (m0->matching_cond_lst_len != m1->matching_cond_lst_len)
    return false;

  for (size_t i = 0; i<m0->matching_cond_lst_len; i++)
  {
    if (eq_matching_cond_frm_3(&m0->matching_cond_lst[i], &m1->matching_cond_lst[i]) != true)
      return false;
  }

  // List of matched UE IDs
  // Optional [0, 65535]
  if (m0->ue_id_matched_lst_len != m1->ue_id_matched_lst_len)
    return false;

  if (m0->ue_id_matched_lst != NULL || m1->ue_id_matched_lst != NULL)
  {
    for (size_t i = 0; i<m0->ue_id_matched_lst_len; i++)
    {
      if (eq_ue_id(&m0->ue_id_matched_lst[i], &m1->ue_id_matched_lst[i]) != true)
        return false;
    }
  }

  // Sequence of Matched UE IDs for Granularity Periods
  // not yet implemented in ASN.1

  return true;
}
