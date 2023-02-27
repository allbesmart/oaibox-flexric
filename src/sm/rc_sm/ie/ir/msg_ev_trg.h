#ifndef MESSAGE_EVENT_TRIGGER_FORMAT_1_E2SM_H
#define MESSAGE_EVENT_TRIGGER_FORMAT_1_E2SM_H 

#include <stdint.h>

#include "../../../../lib/sm/3gpp_derived_ie/rrc_msg_id.h"
#include "network_interface_e2rc.h" 
#include "ev_trigger_ue_info.h"
#include "logical_or.h"


typedef enum{

  INCOMING_E2RC_MSG_DIR ,
  OUTGOING_E2RC_MSG_DIR ,
  END_E2RC_MSG_DIR 

} e2rc_msg_dir_e;


typedef enum{

  NETWORK_INTERFACE_MSG_TYPE_EV_TRG,

  RRC_MSG_MSG_TYPE_EV_TRG,

  END_MSG_MSG_TYPE_EV_TRG,

} msg_type_ev_trg_e;


typedef struct{
  // Event Trigger Condition ID
  // Mandatory
  // 9.3.21
  // [1- 65535]
  uint16_t ev_trigger_cond_id;

  // CHOICE Message Type
  // Mandatory
  msg_type_ev_trg_e msg_type;
  union{
    // 
    network_interface_e2rc_t net;

    // 9.3.35
    rrc_msg_id_t rrc_msg;
  };

  //Message Direction
  //Optinonal
  e2rc_msg_dir_e* msg_dir;

  //  Associated UE Info
  //  Optional
  //  9.3.26
  ev_trigger_ue_info_t* assoc_ue_info;

  // Logical OR
  // Optional
  // 9.3.25
  logical_or_e* log_or;


} msg_ev_trg_t;


void free_msg_ev_trg(msg_ev_trg_t* src);

bool eq_msg_ev_trg(msg_ev_trg_t const* m0, msg_ev_trg_t const* m1);

//{
//  assert(src != NULL);
//}


#endif

