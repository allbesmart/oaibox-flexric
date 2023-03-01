#include "seq_ins_style_multiple_action.h"

#include <assert.h>
#include <stdlib.h>


void free_seq_ins_style(seq_ins_style_t* src)
{
  assert(src != NULL);

  // Requested Insert Style
  // Mandatory
  // 9.3.3
  // 6.2.2.2. in E2 SM common 
  // Integer
  // uint32_t req_insert_style;

  // Sequence of Insert Indication
  // Action Definition
  // [1-63]
  assert(src->sz_seq_ins_ind_act_def > 0 && src->sz_seq_ins_ind_act_def < 64); 

  size_t sz_seq_ins_ind_act_def;
  for(size_t i = 0; i < src-> sz_seq_ins_ind_act_def; ++i){
    free_seq_ins_ind_act_def(&src->seq_ins_ind_act_def[i]) ;
  }

  free(src->seq_ins_ind_act_def);
}

bool eq_seq_ins_style(seq_ins_style_t const* m0, seq_ins_style_t const* m1)
{
  if(m0 == m1)
    return true;

  if(m0 == NULL || m1 == NULL)
    return false;

  // Requested Insert Style
  // Mandatory
  // 9.3.3
  // 6.2.2.2. in E2 SM common 
  // Integer
  if(m0->req_insert_style != m1->req_insert_style)
    return false;

  // Sequence of Insert Indication
  // Action Definition
  // [1-63]
  assert(m0->sz_seq_ins_ind_act_def > 0 && m0->sz_seq_ins_ind_act_def < 64);
  assert(m1->sz_seq_ins_ind_act_def > 0 && m1->sz_seq_ins_ind_act_def < 64);

  if(m0->sz_seq_ins_ind_act_def != m1->sz_seq_ins_ind_act_def)
    return false;

  for(size_t i = 0; i < m0->sz_seq_ins_ind_act_def; ++i){
    if(eq_seq_ins_ind_act_def(&m0->seq_ins_ind_act_def[i], &m1->seq_ins_ind_act_def[i]) == false)
      return false;
  }

  return true;
}

