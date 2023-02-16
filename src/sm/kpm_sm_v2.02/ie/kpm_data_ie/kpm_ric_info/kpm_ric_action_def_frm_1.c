#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "kpm_ric_action_def_frm_1.h"

void free_kpm_action_def_frm_1(kpm_act_def_format_1_t* src) 
{
  assert(src != NULL);

  // Measurement Information
  for (size_t i = 0; i<src->meas_info_lst_len; i++)
  {
    for (size_t j = 0; j<src->meas_info_lst[i].label_info_lst_len; j++)
      free_label_info(&src->meas_info_lst[i].label_info_lst[j]);
    free(src->meas_info_lst[i].label_info_lst);
        
    if (src->meas_info_lst[i].meas_type.type == NAME_MEAS_TYPE)
      free_byte_array(src->meas_info_lst[i].meas_type.name);
  }
  
  free(src->meas_info_lst);
  
  
  // Cell Global ID
  if (src->cell_global_id != NULL)
    free(src->cell_global_id);

  
  // Measurement Bin Range
  if (src->meas_bin_info_lst != NULL)
    assert(false && "Not yet implemented");

}

bool eq_kpm_action_def_frm_1(kpm_act_def_format_1_t const * m0, kpm_act_def_format_1_t const * m1)
{
  assert(m0 != NULL);
  assert(m1 != NULL);

  if (m0->meas_info_lst_len != m1->meas_info_lst_len)
    return false;

  for (size_t i = 0; i < m0->meas_info_lst_len; i++)
  {
    // Meas Type

    if (m0->meas_info_lst[i].meas_type.type != m1->meas_info_lst[i].meas_type.type)
      return false;
    if (m0->meas_info_lst[i].meas_type.type == NAME_MEAS_TYPE)
    {
      if (eq_byte_array(&m0->meas_info_lst[i].meas_type.name, &m1->meas_info_lst[i].meas_type.name) != true)
        return false;
    }
    else if (m0->meas_info_lst[i].meas_type.type == ID_MEAS_TYPE)
    {
      if (m0->meas_info_lst[i].meas_type.id != m1->meas_info_lst[i].meas_type.id)
        return false;
    }


    // Label Info

    if (m0->meas_info_lst[i].label_info_lst_len != m1->meas_info_lst[i].label_info_lst_len)
      return false;
    
    for (size_t j = 0; j < m0->meas_info_lst[i].label_info_lst_len; j++)
    {
      if (eq_label_info(&m0->meas_info_lst[i].label_info_lst[j], &m1->meas_info_lst[i].label_info_lst[j]) != true)
        return false;
    }
  }

  // Granularity Period
  if (m0->gran_period_ms != m1->gran_period_ms)
    return false;

  // Cell Global ID
  if (m0->cell_global_id != NULL && m1->cell_global_id != NULL)
  {
    if (m0->cell_global_id->type != m1->cell_global_id->type)
      return false;

    switch (m0->cell_global_id->type)
    {
    case NR_CGI_RAT_TYPE:
      if (eq_plmn(&m0->cell_global_id->nr_cgi.plmn_id, &m1->cell_global_id->nr_cgi.plmn_id) != true)
        return false;

      if (m0->cell_global_id->nr_cgi.nr_cell_id != m1->cell_global_id->nr_cgi.nr_cell_id)
        return false;
      break;

    case EUTRA_CGI_RAT_TYPE:
      if (eq_plmn(&m0->cell_global_id->eutra.plmn_id, &m1->cell_global_id->eutra.plmn_id) != true)
        return false;

      if (m0->cell_global_id->eutra.eutra_cell_id != m1->cell_global_id->eutra.eutra_cell_id)
        return false;
      break;
    
    default:
      assert(false && "Unknown Cell Global ID Type");
    }

  }

  // Measurement Bin Range Information
  assert(m0->meas_bin_range_info_lst_len == 0 && "Not yet implemented");
  assert(m1->meas_bin_range_info_lst_len == 0 && "Not yet implemented");


  return true;
}
