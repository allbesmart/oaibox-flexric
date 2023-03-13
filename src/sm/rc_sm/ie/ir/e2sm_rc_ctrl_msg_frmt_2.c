#include "e2sm_rc_ctrl_msg_frmt_2.h"

#include <assert.h>

void free_e2sm_rc_ctrl_msg_frmt_2( e2sm_rc_ctrl_msg_frmt_2_t* src)
{
  assert(src != NULL);  

  // Sequence of Control Styles
  // for Multiple Actions
  // [1 - 63]  
  assert(src->sz_seq_ctrl_sma > 0 && src->sz_seq_ctrl_sma < 64);

  for(size_t i = 0; i < src->sz_seq_ctrl_sma; ++i){
    free_seq_ctrl_sma(&src->action[i]);
  }
  
  assert(src->action != NULL);
  free(src->action);
}

bool eq_e2sm_rc_ctrl_msg_frmt_2( e2sm_rc_ctrl_msg_frmt_2_t const* m0,  e2sm_rc_ctrl_msg_frmt_2_t const* m1)
{
  if(m0 == m1)
    return true;

  if(m0 == NULL || m1 == NULL)
    return false;

  // Sequence of Control Styles
  // for Multiple Actions
  // [1 - 63]  
  assert(m0->sz_seq_ctrl_sma > 0 && m0->sz_seq_ctrl_sma < 64);
  assert(m1->sz_seq_ctrl_sma > 0 && m1->sz_seq_ctrl_sma < 64);

  if(m0->sz_seq_ctrl_sma != m1->sz_seq_ctrl_sma)
    return false;

  for(size_t i = 0; i < m0->sz_seq_ctrl_sma; ++i){
    if(eq_seq_ctrl_sma(&m0->action[i], &m1->action[i]) == false)
      return false;
  }

  return true;
}


