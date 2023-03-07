#include "e2sm_rc_ind_msg_frmt_4.h"

#include <assert.h>

void free_e2sm_rc_ind_msg_frmt_4(e2sm_rc_ind_msg_frmt_4_t* src)
{
  assert(src != NULL);

  //Sequence of UE Information
  // [0-65535]
  assert(src->sz_seq_ue_info < 65535+1);

  for(size_t i = 0; i < src->sz_seq_ue_info; ++i){
    free_seq_ue_info(&src->seq_ue_info[i]);
  }

  if(src->seq_ue_info != NULL){
    assert(src->sz_seq_ue_info >0);
    free(src->seq_ue_info);
  }

  // Sequence of Cell Information
  // [0-65535]
  for(size_t i = 0; i <  src->sz_seq_cell_info_2; ++i){
    free_seq_cell_info_2(&src->seq_cell_info_2[i]);
  }

  if(src->seq_cell_info_2 != NULL){
    assert(src->sz_seq_cell_info_2 > 0);
    free(src->seq_cell_info_2);
  }

}


bool eq_e2sm_rc_ind_msg_frmt_4( e2sm_rc_ind_msg_frmt_4_t const* m0,  e2sm_rc_ind_msg_frmt_4_t const* m1)
{
  if(m0 == m1)
    return true;

  if(m0 == NULL || m1 == NULL)
    return false;

  //Sequence of UE Information
  // [0-65535]
  assert(m0->sz_seq_ue_info < 65535+1);
  assert(m1->sz_seq_ue_info < 65535+1);

  if(m0->sz_seq_ue_info != m1->sz_seq_ue_info)
    return false;

  for(size_t i = 0; i < m0->sz_seq_ue_info; ++i){
    if(eq_seq_ue_info(&m0->seq_ue_info[i], &m1->seq_ue_info[i]) == false)
      return false;
  }

  // Sequence of Cell Information
  // [0-65535]
  assert(m0->sz_seq_cell_info_2 < 65535+1);
  assert(m1->sz_seq_cell_info_2 < 65535+1);

  for(size_t i = 0; i < m0->sz_seq_cell_info_2; ++i){
    if(eq_seq_cell_info_2(&m0->seq_cell_info_2[i], &m1->seq_cell_info_2[i] ) == false)
      return false;
  }

  return true;
}

