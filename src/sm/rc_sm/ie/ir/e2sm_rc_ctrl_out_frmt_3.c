#include "e2sm_rc_ctrl_out_frmt_3.h"

#include <assert.h>
#include <stdlib.h>

void free_e2sm_rc_ctrl_out_frmt_3( e2sm_rc_ctrl_out_frmt_3_t* src)
{
  assert(src != NULL);

  assert(src->sz_seq_ran_param < 256);

  for(size_t i = 0; i < src->sz_seq_ran_param; ++i){
    free_seq_ran_param(&src->ran_param[i]);
  }

  if(src->ran_param != NULL)
    free(src->ran_param);
}

bool eq_e2sm_rc_ctrl_out_frmt_3( e2sm_rc_ctrl_out_frmt_3_t const* m0,  e2sm_rc_ctrl_out_frmt_3_t const* m1)
{
  if(m0 == m1)
    return true;

  if(m0 == NULL || m1 == NULL)
    return false;

  //  Sequence of RAN Parameters
  //  [0-255]
  assert(m0->sz_seq_ran_param < 256);
  assert(m1->sz_seq_ran_param < 256);

  if(m0->sz_seq_ran_param != m1->sz_seq_ran_param)
    return false;

  for(size_t i = 0; i < m0->sz_seq_ran_param; ++i){
    if(eq_seq_ran_param(&m0->ran_param[i], &m1->ran_param[i]) == false)
      return false;
  }

  return true;
}

