#include <assert.h>

#include "e2sm_rc_ev_trg_frmt_1.h"

void free_e2sm_rc_ev_trg_frmt_1(e2sm_rc_ev_trg_frmt_1_t* src)
{
  assert(src != NULL);

  // [1 - 65535]
  
  assert(src->sz_msg_ev_trg > 0 && src->sz_msg_ev_trg < 65535 + 1);
  for(size_t i = 0; i < src->sz_msg_ev_trg; ++i){
    free_msg_ev_trg(&src->msg_ev_trg[i]);
  }

  assert(src->msg_ev_trg != NULL);
  free(src->msg_ev_trg);

  // Global Associated UE Info
  // Optional
  // 9.3.26
  assert(src->global_assoc_ue_info == NULL && "Not implemented");
}





