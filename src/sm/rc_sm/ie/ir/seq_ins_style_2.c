#include "seq_ins_style_2.h"

#include <assert.h>

void free_seq_ins_style_2(seq_ins_style_2_t* src)
{
  assert(src != NULL);

  // Indicated Insert Style
  // Mandatory
  // 9.3.3
  // 6.2.2.2.
  // INTEGER
  // uint32_t ind_ins_style;

  // Sequence of Insert Indication Actions
  // [1-63]
  assert(src->sz_seq_ins_ind_act_2 > 0 && src->sz_seq_ins_ind_act_2 < 64); 
  for(size_t i = 0; i < src->sz_seq_ins_ind_act_2; ++i){
    free_seq_ins_ind_act_2(&src->seq_ins_ind_act[i]);
  }

  assert(src->seq_ins_ind_act != NULL);
  free(src->seq_ins_ind_act);
}

bool eq_seq_ins_style_2(seq_ins_style_2_t const* m0, seq_ins_style_2_t const* m1)
{
  if(m0 == m1)
    return true;

  if(m0 == NULL || m1 == NULL)
    return false;

  // Indicated Insert Style
  // Mandatory
  // 9.3.3
  // 6.2.2.2.
  // INTEGER
  if(m0->ind_ins_style != m1->ind_ins_style)
    return false;

  // Sequence of Insert Indication Actions
  // [1-63]
  assert(m0->sz_seq_ins_ind_act_2 > 0 && m0->sz_seq_ins_ind_act_2 < 64);
  assert(m1->sz_seq_ins_ind_act_2 > 0 && m1->sz_seq_ins_ind_act_2 < 64);

  for(size_t i = 0; i < m0->sz_seq_ins_ind_act_2; ++i){
    if(eq_seq_ins_ind_act_2(&m0->seq_ins_ind_act[i], &m1->seq_ins_ind_act[i]) == false)
      return false;
  }

  return true;
}

