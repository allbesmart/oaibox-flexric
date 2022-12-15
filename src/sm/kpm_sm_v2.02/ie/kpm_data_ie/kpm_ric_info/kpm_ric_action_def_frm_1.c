#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "ric_action_def_frm_1.h"

void free_kpm_action_def(act_def_format_1_t* src) 
{
  assert(src != NULL);

  for (size_t i = 0; i<src->meas_info_lst_len; i++)
  {
    for (size_t j = 0; j<src->meas_info_lst[i].label_info_lst_len; j++)
      free_label_info(&src->meas_info_lst[i].label_info_lst[j]);
    free(src->meas_info_lst[i].label_info_lst);
        
    if (src->meas_info_lst[i].type == NAME_MEAS_TYPE)
      free_byte_array(src->meas_info_lst[i].name);
  }
  
  free(src->meas_info_lst);
}