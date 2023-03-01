#include "e2sm_rc_act_def_frmt_4.h"

#include <assert.h>

void free_e2sm_rc_act_def_frmt_4(e2sm_rc_act_def_frmt_4_t* src)
{
  assert(src != NULL);

  // Sequence of Insert Styles for
  // Multiple Actions
  // [1-4]
  assert(src->sz_seq_ins_style > 0 && src->sz_seq_ins_style < 5);

  for(size_t i = 0; i < src->sz_seq_ins_style ; ++i){
    free_seq_ins_style(&src->seq_ins_style[i]);
  }
 
  assert(src->seq_ins_style != NULL);
  free(src->seq_ins_style);

  // UE ID
  // Optional
  // 9.3.10
  assert(src->ue_id == NULL && "Not implemented"); 

}

bool eq_e2sm_rc_act_def_frmt_4(e2sm_rc_act_def_frmt_4_t const* m0, e2sm_rc_act_def_frmt_4_t const* m1)
{
  if(m0 == m1)
    return true;

  if(m0 == NULL || m1 == NULL)
    return false;

  // Sequence of Insert Styles for
  // Multiple Actions
  // [1-4]
  assert(m0->sz_seq_ins_style > 0 && m0->sz_seq_ins_style < 5);
  assert(m1->sz_seq_ins_style > 0 && m1->sz_seq_ins_style < 5);

  if(m0->sz_seq_ins_style != m1->sz_seq_ins_style )
    return false;

  for(size_t i = 0; i < m0->sz_seq_ins_style; ++i){
    if(eq_seq_ins_style(&m0->seq_ins_style[i], &m1->seq_ins_style[i] ) == false)
      return false;
  }

  // UE ID
  // Optional
  // 9.3.10
  assert(m0->ue_id == NULL && "Not implemented"); 
  assert(m1->ue_id == NULL && "Not implemented"); 

  return true;
}

