#include "e2sm_rc_ctrl_hdr_frmt_2.h"

#include <assert.h>
#include <stdlib.h>

void free_e2sm_rc_ctrl_hdr_frmt_2( e2sm_rc_ctrl_hdr_frmt_2_t* src)
{
  assert(src != NULL);

 // UE ID
 // Optional
 // 9.3.10
  if(src->ue_id != NULL){
    free_ue_id_e2sm(src->ue_id);
    free(src->ue_id);
  }

  // RIC Control decision
  // Optional
  if(src->ric_ctrl_dec != NULL){
    free(src->ric_ctrl_dec);
  }

}
     
bool eq_e2sm_rc_ctrl_hdr_frmt_2( e2sm_rc_ctrl_hdr_frmt_2_t const* m0, e2sm_rc_ctrl_hdr_frmt_2_t const* m1)
{
  if(m0 == m1)
    return true;

  if(m0 == NULL || m1 == NULL)
    return false;

  if(eq_ue_id_e2sm(m0->ue_id, m1->ue_id) == false)
    return false;

  if(m0->ric_ctrl_dec != m1->ric_ctrl_dec){
    if(m0->ue_id == NULL || m1->ue_id == NULL)
      return false;

    if(*m0->ric_ctrl_dec != *m1->ric_ctrl_dec)
      return false;
  }

  return true;
}

