#include <assert.h>

#include "kpm_ric_ind_msg_frm_2.h"

void free_kpm_ind_msg_frm_2(kpm_ind_msg_format_2_t* src)
{
  assert(src != NULL);

  // Measurement Data  move this
  // [1, 65535]
  for (size_t i = 0; i<src->meas_data_lst_len; i++)
  {
    free(src->meas_data_lst[i].meas_record_lst);

    if (src->meas_data_lst[i].incomplete_flag != NULL)
      free(src->meas_data_lst[i].incomplete_flag);
  }
  free(src->meas_data_lst);

  // Measurement Information Condition UE List
  // [1, 65535]
  for (size_t i = 0; i<src->meas_info_cond_ue_lst_len; i++)
    free_kpm_meas_info_cond_ue(&src->meas_info_cond_ue_lst[i]);
  free(src->meas_info_cond_ue_lst);

  // Granularity Period - OPTIONAL
  if (src->gran_period_ms != NULL)
    free(src->gran_period_ms);

}

bool eq_kpm_ind_msg_frm_2(kpm_ind_msg_format_2_t const* m0, kpm_ind_msg_format_2_t const* m1)
{
  assert(m0 != NULL);
  assert(m1 != NULL);

  // Measurement Data
  // [1, 65535]
  if (m0->meas_data_lst_len != m1->meas_data_lst_len)
    return false;

  for (size_t i = 0; i<m0->meas_data_lst_len; i++)
  {
    if (eq_meas_data_lst(&m0->meas_data_lst[i], &m1->meas_data_lst[i]) != true)
      return false;
  }

  // Measurement Information Condition UE List
  // [1, 65535]
  if (m0->meas_info_cond_ue_lst_len != m1->meas_info_cond_ue_lst_len)
    return false;

  for (size_t i = 0; i<m0->meas_info_cond_ue_lst_len; i++)
  {
    if (eq_kpm_meas_info_cond_ue(&m0->meas_info_cond_ue_lst[i], &m1->meas_info_cond_ue_lst[i]) != true)
      return false;
  }

  // Granularity Period - OPTIONAL
  if ((m0->gran_period_ms != NULL || m1->gran_period_ms != NULL) && *m0->gran_period_ms != *m1->gran_period_ms)
    return false;


  return true;
}
