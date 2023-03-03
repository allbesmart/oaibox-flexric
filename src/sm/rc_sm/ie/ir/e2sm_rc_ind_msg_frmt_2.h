#ifndef E2SM_RC_INDICATION_MSG_FORMAT_2_H
#define E2SM_RC_INDICATION_MSG_FORMAT_2_H

#include "seq_ue_id.h"

#include <stdlib.h>

//9.2.1.4.2
typedef struct{
  //Sequence of UE Identifier
  //[1-65535]
  size_t sz_seq_ue_id;
  seq_ue_id_t* seq_ue_id;

} e2sm_rc_ind_msg_frmt_2_t;

#endif

