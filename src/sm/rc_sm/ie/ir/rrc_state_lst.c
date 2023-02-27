#include "rrc_state_lst.h"

#include <assert.h>

void free_rrc_state_lst( rrc_state_lst_t* src)
{
  assert(src != NULL);

  // 9.3.37
  // [1 - 8]
  assert(src->sz_rrc_state > 0 && src->sz_rrc_state < 9 && "Out of range"); 

  for(size_t i = 0; i < src->sz_rrc_state; ++i){
    free_rrc_state(&src->state_chng_to[i] );
  }

  free(src->state_chng_to);
}


bool eq_rrc_state_lst(rrc_state_lst_t const* m0, rrc_state_lst_t const* m1)
{
  if(m0 == m1)
    return true;

  if(m0 == NULL || m1 == NULL)
    return false;

  // 9.3.37
  // [1 - 8]
  if(m0->sz_rrc_state != m1->sz_rrc_state)
    return false;

  for(size_t i = 0; i < m0->sz_rrc_state; ++i){
    if(eq_rrc_state(&m0->state_chng_to[i], &m1->state_chng_to[i]) == false)
      return false;
  }

  return true;
}

