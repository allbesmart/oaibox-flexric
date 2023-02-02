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