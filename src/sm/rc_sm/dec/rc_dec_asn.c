/*
 * Licensed to the OpenAirInterface (OAI) Software Alliance under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The OpenAirInterface Software Alliance licenses this file to You under
 * the OAI Public License, Version 1.1  (the "License"); you may not use this file
 * except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.openairinterface.org/?page_id=698
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *-------------------------------------------------------------------------------
 * For more information about the OpenAirInterface (OAI) Software Alliance:
 *      contact@openairinterface.org
 */

#include "rc_dec_asn.h"

#include <assert.h>

#include "../../../util/alg_ds/alg/defer.h"

#include "../ie/ir/ran_param_struct.h"

#include "../ie/asn/RANParameter-Testing-Item.h"
#include "../ie/asn/E2SM-RC-EventTrigger.h"
#include "../ie/asn/E2SM-RC-EventTrigger-Format1.h"
#include "../ie/asn/E2SM-RC-EventTrigger-Format2.h"
#include "../ie/asn/E2SM-RC-EventTrigger-Format3.h"
#include "../ie/asn/E2SM-RC-EventTrigger-Format4.h"
#include "../ie/asn/E2SM-RC-EventTrigger-Format5.h"

#include "../ie/asn/E2SM-RC-EventTrigger-Format1-Item.h"
#include "../ie/asn/E2SM-RC-EventTrigger-Format3-Item.h"
#include "../ie/asn/E2SM-RC-EventTrigger-Format4-Item.h"
#include "../ie/asn/TriggerType-Choice-RRCstate.h"
#include "../ie/asn/TriggerType-Choice-RRCstate-Item.h"
#include "../ie/asn/TriggerType-Choice-UEID.h"
#include "../ie/asn/TriggerType-Choice.h"
#include "../ie/asn/TriggerType-Choice-L2state.h"
#include "../ie/asn/RANParameter-Testing-LIST.h"
#include "../ie/asn/RANParameter-Testing-Item-Choice-Structure.h" 
#include "../ie/asn/RANParameter-Testing-STRUCTURE.h"

#include "../ie/asn/RANParameter-Testing-Item-Choice-ElementTrue.h"
#include "../ie/asn/RANParameter-Testing-Item-Choice-ElementFalse.h"

#include "../ie/asn/RANParameter-Testing-Item-Choice-List.h"
#include "../ie/asn/RANParameter-Value.h"

#include "../ie/asn/MessageType-Choice-NI.h"
#include "../ie/asn/MessageType-Choice-RRC.h"

#include "../ie/asn/RIC-PolicyAction-RANParameter-Item.h"

#include "../ie/asn/E2SM-RC-ActionDefinition.h"
#include "../ie/asn/E2SM-RC-ActionDefinition-Format1.h"
#include "../ie/asn/E2SM-RC-ActionDefinition-Format1-Item.h"

#include "../ie/asn/E2SM-RC-ActionDefinition-Format2.h"
#include "../ie/asn/E2SM-RC-ActionDefinition-Format2-Item.h"

#include "../ie/asn/E2SM-RC-ActionDefinition-Format3.h"
#include "../ie/asn/E2SM-RC-ActionDefinition-Format3-Item.h"

#include "../ie/asn/E2SM-RC-ActionDefinition-Format4.h"
#include "../ie/asn/E2SM-RC-ActionDefinition-Format4-Style-Item.h"
#include "../ie/asn/E2SM-RC-ActionDefinition-Format4-Indication-Item.h"
#include "../ie/asn/E2SM-RC-ActionDefinition-Format4-RANP-Item.h"

#include "../ie/asn/RANParameter-ValueType-Choice-ElementTrue.h"
#include "../ie/asn/RANParameter-ValueType-Choice-ElementFalse.h"


#include "../ie/asn/RANParameter-ValueType-Choice-Structure.h"
#include "../ie/asn/RANParameter-STRUCTURE.h"
#include "../ie/asn/RANParameter-STRUCTURE-Item.h"
#include "../ie/asn/RANParameter-ValueType-Choice-ElementTrue.h"
#include "../ie/asn/RANParameter-ValueType-Choice-ElementFalse.h"
#include "../ie/asn/RANParameter-ValueType-Choice-Structure.h"
#include "../ie/asn/RANParameter-Testing-Item-Choice-List.h"
#include "../ie/asn/RANParameter-ValueType-Choice-List.h"
#include "../ie/asn/RANParameter-LIST.h"

#include "../ie/asn/E2SM-RC-IndicationHeader.h"
#include "../ie/asn/E2SM-RC-IndicationHeader-Format1.h"
#include "../ie/asn/E2SM-RC-IndicationHeader-Format2.h"
#include "../ie/asn/E2SM-RC-IndicationHeader-Format3.h"

#include "../ie/asn/E2SM-RC-IndicationMessage.h"
#include "../ie/asn/E2SM-RC-IndicationMessage-Format1.h"

#include "../ie/asn/E2SM-RC-IndicationMessage-Format1-Item.h"

#include "../ie/asn/E2SM-RC-IndicationMessage-Format2.h"
#include "../ie/asn/E2SM-RC-IndicationMessage-Format2-Item.h"
#include "../ie/asn/E2SM-RC-IndicationMessage-Format2-RANParameter-Item.h"

#include "../ie/asn/E2SM-RC-IndicationMessage-Format3.h"
#include "../ie/asn/E2SM-RC-IndicationMessage-Format3-Item.h"

#include "../ie/asn/E2SM-RC-IndicationMessage-Format4.h"
#include "../ie/asn/E2SM-RC-IndicationMessage-Format4-ItemUE.h"
#include "../ie/asn/E2SM-RC-IndicationMessage-Format4-ItemCell.h"

#include "../ie/asn/E2SM-RC-IndicationMessage-Format5.h"
#include "../ie/asn/E2SM-RC-IndicationMessage-Format5-Item.h"

#include "../ie/asn/E2SM-RC-IndicationMessage-Format6.h"

#include "../ie/asn/E2SM-RC-IndicationMessage-Format6-Style-Item.h"
#include "../ie/asn/E2SM-RC-IndicationMessage-Format6-Indication-Item.h"
#include "../ie/asn/E2SM-RC-IndicationMessage-Format6-RANP-Item.h"

#include "../ie/asn/E2SM-RC-CallProcessID.h"

#include "../ie/asn/E2SM-RC-CallProcessID-Format1.h"
#include "../ie/asn/E2SM-RC-ControlHeader.h"

#include "../ie/asn/E2SM-RC-ControlHeader-Format1.h"
#include "../ie/asn/E2SM-RC-ControlHeader-Format2.h"
#include "../ie/asn/E2SM-RC-ControlMessage.h"
#include "../ie/asn/E2SM-RC-ControlMessage-Format1.h"
#include "../ie/asn/E2SM-RC-ControlMessage-Format1-Item.h"
#include "../ie/asn/E2SM-RC-ControlMessage-Format2.h"
#include "../ie/asn/E2SM-RC-ControlMessage-Format2-Style-Item.h"
#include "../ie/asn/E2SM-RC-ControlMessage-Format2-ControlAction-Item.h"

#include "../ie/asn/E2SM-RC-ControlOutcome.h"
#include "../ie/asn/E2SM-RC-ControlOutcome-Format1.h"
#include "../ie/asn/E2SM-RC-ControlOutcome-Format2.h"
#include "../ie/asn/E2SM-RC-ControlOutcome-Format3.h"
#include "../ie/asn/E2SM-RC-ControlOutcome-Format1-Item.h"

#include "../ie/asn/E2SM-RC-ControlOutcome-Format2-Style-Item.h"

#include "../ie/asn/E2SM-RC-ControlOutcome-Format2-ControlOutcome-Item.h"
#include "../ie/asn/E2SM-RC-ControlOutcome-Format3-Item.h"



#include "../ie/asn/E2SM-RC-ControlOutcome-Format2-RANP-Item.h"

#include "../ie/asn/RANParameter-LIST.h"

#include "../ie/ir/ran_param_list.h"

#include "../../../lib/sm/dec_asn_sm_common/dec_ue_id.h" 
#include "../../../lib/sm/dec_asn_sm_common/dec_cell_global_id.h"


#include <string.h>
#include <stdlib.h>




static inline
byte_array_t copy_ostring_to_ba(OCTET_STRING_t os)
{
  byte_array_t ba = {.len = os.size}; 
  ba.buf = malloc(ba.len);
  assert(ba.buf != NULL && "Memory exhausyed");
  memcpy(ba.buf, os.buf, ba.len );
  return ba;
}

static inline
OCTET_STRING_t copy_ba_to_ostring(byte_array_t ba)
{
  OCTET_STRING_t os = { .size = ba.len }; 
  os.buf = malloc(ba.len);
  memcpy(os.buf, ba.buf, ba.len);
  return os;
}

static inline
byte_array_t copy_bit_string_to_ba(BIT_STRING_t bs)
{
  assert(bs.bits_unused == 0);
  byte_array_t ba = {0}; 
  ba.len = bs.size;
  ba.buf = calloc(ba.len, sizeof(uint8_t) );
  assert(ba.buf != NULL && "Memory exhausted");
  memcpy(ba.buf, bs.buf, ba.len);
  return ba;
}

static inline
BIT_STRING_t	copy_ba_to_bit_string(byte_array_t ba)
{
  BIT_STRING_t bs;
  memset(&bs, 0, sizeof(BIT_STRING_t));
  
  bs.buf = calloc(1, ba.len);
  memcpy(bs.buf, ba.buf, ba.len);
  bs.size = ba.len;
  bs.bits_unused = 0; // FixME

  return bs;
}




static
network_interface_e2rc_t cp_msg_type_ni(MessageType_Choice_NI_t const* src)
{
  assert(src != NULL);

  network_interface_e2rc_t dst = {0}; 

  // NI Type
  // Mandatory
  // 9.3.32
  if(src->nI_Type ==InterfaceType_nG	 ){
    dst.ni_type =  NG_NETWORK_INTERFACE_TYPE; 
  } else if (src->nI_Type == InterfaceType_xn){
    dst.ni_type =  XN_NETWORK_INTERFACE_TYPE;
  }else if (src->nI_Type == InterfaceType_f1   ){
    dst.ni_type = F1_NETWORK_INTERFACE_TYPE;
  }else if ( src->nI_Type == InterfaceType_e1){
    dst.ni_type = E1_NETWORK_INTERFACE_TYPE;
  }else if ( src->nI_Type == InterfaceType_s1){
    dst.ni_type = S1_NETWORK_INTERFACE_TYPE;
  }else if (src->nI_Type == InterfaceType_x2 ){
    dst.ni_type = X2_NETWORK_INTERFACE_TYPE ; 
  }else if (src->nI_Type == InterfaceType_w1) {
    dst.ni_type = W1_NETWORK_INTERFACE_TYPE;
  } else {
    assert(0 != 0 && "Unknown type"); 
  }

  // NI Identifier
  // Optional
  // 9.3.33
  assert(src->nI_Identifier == NULL && "Not implemented");

  // NI Message
  // Optional
  // 9.3.34
  assert(src->nI_Message == NULL && "Not implemented"); 

  return dst;
}


static
lte_rrc_class_e  cp_rrc_msg_type_lte( RRCclass_LTE_t   src)
{
  lte_rrc_class_e  dst = {0}; 

  if(src == RRCclass_LTE_bCCH_BCH){
    dst = BCCH_BCH_LTE_RRC_CLASS;	
  } else if(src ==RRCclass_LTE_bCCH_BCH_MBMS	){
    dst = BCCH_BCH_MBMS_LTE_RRC_CLASS ;
  }else if(src ==RRCclass_LTE_bCCH_DL_SCH	){
    dst = BCCH_DL_SCH_LTE_RRC_CLASS ;
  }else if(src ==RRCclass_LTE_bCCH_DL_SCH_BR	){
    dst = BCCH_DL_SCH_BR_LTE_RRC_CLASS ;
  }else if(src ==RRCclass_LTE_bCCH_DL_SCH_MBMS	){
    dst = BCCH_DL_SCH_MBMS_LTE_RRC_CLASS ;
  }else if(src ==RRCclass_LTE_mCCH	){
    dst = MCCH_LTE_RRC_CLASS ;
  }else if(src ==RRCclass_LTE_pCCH	){
    dst = PCCH_LTE_RRC_CLASS ;
  }else if(src ==RRCclass_LTE_dL_CCCH	){
    dst = DL_CCCH_LTE_RRC_CLASS ;
  }else if(src ==RRCclass_LTE_dL_DCCH){
    dst = 	 DL_DCCH_LTE_RRC_CLASS;
  }else if(src ==RRCclass_LTE_uL_CCCH	){
    dst = UL_CCCH_LTE_RRC_CLASS ;
  }else if(src ==RRCclass_LTE_uL_DCCH	){
    dst = UL_DCCH_LTE_RRC_CLASS ;
  }else if(src ==RRCclass_LTE_sC_MCCH	){
    dst = SC_MCCH_LTE_RRC_CLASS ;
  }else {
    assert( 0!=0 && "Unknown type");
  } 

  return dst;
}

static
nr_rrc_class_e cp_rrc_msg_type_nr(RRCclass_NR_t	src)
{
  nr_rrc_class_e dst = {0};

  if(src == RRCclass_NR_bCCH_BCH){
    dst = BCCH_BCH_NR_RRC_CLASS;
  } else if(src == RRCclass_NR_bCCH_DL_SCH){
    dst = BCCH_DL_SCH_NR_RRC_CLASS;
  }else if(src == RRCclass_NR_dL_CCCH){
    dst = DL_CCCH_NR_RRC_CLASS;
  }else if(src == RRCclass_NR_dL_DCCH	){
    dst = DL_DCCH_NR_RRC_CLASS ;
  }else if(src ==RRCclass_NR_pCCH	){
    dst = PCCH_NR_RRC_CLASS ;
  }else if(src ==RRCclass_NR_uL_CCCH	){
    dst = UL_CCCH_NR_RRC_CLASS ;
  }else if(src ==RRCclass_NR_uL_CCCH1	){
    dst = UL_CCCH1_NR_RRC_CLASS ;
  }else if(src ==RRCclass_NR_uL_DCCH	){
    dst = UL_DCCH_NR_RRC_CLASS ;
  }else {
    assert(0!=0 && "Unknown type");
  }

  return dst;
}


static
rrc_msg_id_t cp_msg_type_rrc(MessageType_Choice_RRC_t* const src)
{
  assert(src != NULL);

  rrc_msg_id_t dst = {0}; 

  // Mandatory
  //rrc_message_id_e type;
  if(src->rRC_Message.rrcType.present == RRC_MessageID__rrcType_PR_lTE){
    dst.type = LTE_RRC_MESSAGE_ID;
    dst.lte = cp_rrc_msg_type_lte( src->rRC_Message.rrcType.choice.lTE);
  } else if( src->rRC_Message.rrcType.present ==  RRC_MessageID__rrcType_PR_nR){
    dst.type = NR_RRC_MESSAGE_ID;
    dst.nr = cp_rrc_msg_type_nr(src->rRC_Message.rrcType.choice.nR);
  } else {
    assert(0!=0 && "Unknown type");
  }

  // Mandatory
  // Integer
  // Number starts from 0 from the first
  // entry of a given RRC message class
  // defined in TS 36.331 [14] or TS
  // 38.331 [15].
  // uint64_t rrc_msg_id;
  dst.rrc_msg_id = src->rRC_Message.messageID;

  return dst;
}




static
msg_ev_trg_t cp_rc_ev_trigger_format_1_it(E2SM_RC_EventTrigger_Format1_Item_t const* src)
{
  assert(src != NULL);

  msg_ev_trg_t dst = {0}; 

  // Event Trigger Condition ID
  // Mandatory
  // 9.3.21
  // [1- 65535]
  assert(src->ric_eventTriggerCondition_ID > 0 && src->ric_eventTriggerCondition_ID  < 65535 +1);
  dst.ev_trigger_cond_id = src->ric_eventTriggerCondition_ID ;

  // CHOICE Message Type
  // Mandatory
  if(src->messageType.present == MessageType_Choice_PR_messageType_Choice_NI   ){
    dst.msg_type = NETWORK_INTERFACE_MSG_TYPE_EV_TRG;
    dst.net = cp_msg_type_ni(src->messageType.choice.messageType_Choice_NI);
  } else if(src->messageType.present == MessageType_Choice_PR_messageType_Choice_RRC ){
    dst.msg_type =  RRC_MSG_MSG_TYPE_EV_TRG;
    dst.rrc_msg = cp_msg_type_rrc(src->messageType.choice.messageType_Choice_RRC);
  } else {
    assert(0!=0 && "Unknown type");
  }

  //Message Direction
  //Optional
  assert(src->messageDirection == NULL && "Not implemented");

  //  Associated UE Info
  //  Optional
  //  9.3.26
  assert(src->associatedUEInfo == NULL && "Not implemented");

  // Logical OR
  // Optional
  // 9.3.25
  assert(src->logicalOR == NULL && "Not implemented");

  return dst;
}







static
e2sm_rc_ev_trg_frmt_1_t cp_rc_ev_trigger_format_1(E2SM_RC_EventTrigger_Format1_t const* src)
{
  assert(src != NULL);

  e2sm_rc_ev_trg_frmt_1_t dst = {0}; 

  size_t const sz = src->message_List.list.count; 
  assert(sz > 0 && sz < 65535 + 1);

  dst.sz_msg_ev_trg = sz;
  dst.msg_ev_trg = calloc(sz, sizeof(msg_ev_trg_t));

  for(size_t i = 0; i < sz; ++i){
    dst.msg_ev_trg[i] = cp_rc_ev_trigger_format_1_it(src->message_List.list.array[i]);
  }

  assert(src->globalAssociatedUEInfo == NULL && "Not implemented");

  return dst;
}

static
e2sm_rc_ev_trg_frmt_2_t cp_rc_ev_trigger_format_2(E2SM_RC_EventTrigger_Format2_t const* src)
{
  assert(src != NULL);

  e2sm_rc_ev_trg_frmt_2_t dst = {0}; 

  //  Call Process Type ID
  //  Mandatory
  //  9.3.15
  //  INTEGER (1.. 65535, …)
  assert(src->ric_callProcessType_ID > 0 && src->ric_callProcessType_ID < 65535 +1 && "Out of range");
  dst.call_proc_type_id = src->ric_callProcessType_ID;

  // Call Breakpoint ID
  // Mandatory
  // 9.3.49
  // INTEGER (1.. 65535, …)
  assert(src->ric_callProcessBreakpoint_ID > 0 &&  src->ric_callProcessBreakpoint_ID < 65535 +1 && "Out of range" ); 
  dst.call_break_id = src->ric_callProcessBreakpoint_ID; 

  // Associated E2 Node Info
  // Optional
  // 9.3.29
  assert(src->associatedE2NodeInfo == NULL && "Not implmeented");

  // Associated UE Info
  // Optional
  // 9.3.26
  assert(src->associatedUEInfo == NULL && "Not implemneted");

  return dst;
}


static
e2_node_info_chng_t cp_e2_node_info_chng(E2SM_RC_EventTrigger_Format3_Item_t const * src)
{
  assert(src != NULL);

  e2_node_info_chng_t dst = {0}; 

  //Event Trigger Condition ID
  //Mandatory
  //9.3.21
  // INTEGER (1..65535, …)
  assert(src->ric_eventTriggerCondition_ID > 0 && src->ric_eventTriggerCondition_ID <  65535 + 1 && "Out of range");
  dst.ev_trigger_cond_id = src->ric_eventTriggerCondition_ID; 

  // E2 Node Information Change ID
  // Mandatory
  // INTEGER (1..512, ...)
  assert(src->e2NodeInfoChange_ID > 0 &&  src->e2NodeInfoChange_ID < 513 && "Out of range");
  dst.e2_node_info_chng_id = src->e2NodeInfoChange_ID;

  // Associated Cell Info
  // Optional
  // 9.3.27
  assert(src->associatedCellInfo == NULL && "Not implemented"); 

  // Logical OR
  // Optional
  // 9.3.25
  assert(src->logicalOR == NULL && "Not implemented"); 

  return dst;
}


static
e2sm_rc_ev_trg_frmt_3_t cp_rc_ev_trigger_format_3(E2SM_RC_EventTrigger_Format3_t const* src)
{
  assert(src != NULL);

  e2sm_rc_ev_trg_frmt_3_t dst = {0};

  // Sequence of E2 Node
  // Information Change
  // [1 - 65535]
  assert(src->e2NodeInfoChange_List.list.count > 0 && src->e2NodeInfoChange_List.list.count <  65535 +1);
  
  dst.sz_e2_node_info_chng = src->e2NodeInfoChange_List.list.count; 

  dst.e2_node_info_chng = calloc(dst.sz_e2_node_info_chng, sizeof(e2_node_info_chng_t)); 
  assert(dst.e2_node_info_chng != NULL && "Memory exhausted" );

  for(size_t i = 0; i < dst.sz_e2_node_info_chng ; ++i ){
    dst.e2_node_info_chng[i] = cp_e2_node_info_chng(src->e2NodeInfoChange_List.list.array[i]);
  }

  return dst; 
}

static
rrc_state_t cp_rrc_state(TriggerType_Choice_RRCstate_Item_t const * src)
{
  assert(src != NULL);

  rrc_state_t dst = {0}; 

  if(src->stateChangedTo == RRC_State_rrc_connected	 ){
    dst.state_chngd_to = RRC_CONNECTED_RRC_STATE_E2SM_RC;
  } else if(src->stateChangedTo == RRC_State_rrc_inactive	){
    dst.state_chngd_to = RRC_INACTIVE_RRC_STATE_E2SM_RC;
  } else if(src->stateChangedTo == RRC_State_rrc_idle	){
    dst.state_chngd_to = RRC_IDLE_RRC_STATE_E2SM_RC;
  } else if(src->stateChangedTo == RRC_State_any){
    dst.state_chngd_to = ANY_RRC_STATE_E2SM_RC;
  } else{
    assert(0 != 0 && " Unknown state changed");
  }

  assert(src->logicalOR == NULL && "Not implemented");

  return dst;
}

static
rrc_state_lst_t cp_rrc_state_lst(TriggerType_Choice_RRCstate_t const* src)
{
  assert(src != NULL);

  rrc_state_lst_t dst = {0}; 

  // 9.3.37
  // [1 - 8]
  assert(src->rrcState_List.list.count > 0 &&  src->rrcState_List.list.count < 9);
  dst.sz_rrc_state = src->rrcState_List.list.count;

  dst.state_chng_to = calloc( dst.sz_rrc_state, sizeof(rrc_state_t));
  assert(dst.state_chng_to != NULL && "Memory exhausted");

  for(size_t i = 0; i < dst.sz_rrc_state; ++i){
    dst.state_chng_to[i] = cp_rrc_state(src->rrcState_List.list.array[i]); 
  }

  assert(dst.sz_rrc_state > 0 && dst.sz_rrc_state < 9);
  return dst; 
}

static
ran_param_test_t cp_ran_param_test(RANParameter_Testing_Item_t const* src);


static
ran_param_test_lst_t cp_lst(RANParameter_Testing_Item_Choice_List_t const* src)
{
  assert(src != NULL);

  ran_param_test_lst_t dst = {0}; 

  // [1- 65535]
  assert(src->ranParameter_List->list.count > 0 && src->ranParameter_List->list.count < 65535 + 1);
  dst.sz_lst = src->ranParameter_List->list.count; 

  dst.ran_param_test = calloc(dst.sz_lst, sizeof(ran_param_test_t));
  assert(dst.ran_param_test != NULL && "Memory exhausted" );

  for(size_t i = 0; i < dst.sz_lst; ++i){
    dst.ran_param_test[i] = cp_ran_param_test(src->ranParameter_List->list.array[i]) ;
  }

  return dst;
}

static
ran_param_test_strct_t cp_strct(RANParameter_Testing_Item_Choice_Structure_t const* src)
{
  assert(src != NULL);

  ran_param_test_strct_t dst = {0}; 

  // [1-65535]
  assert(src->ranParameter_Structure->list.count > 0 && src->ranParameter_Structure->list.count < 65535 + 1); 
  dst.sz_strct = src->ranParameter_Structure->list.count; 

  dst.ran_param_test = calloc(dst.sz_strct, sizeof(ran_param_test_t));
  assert(dst.ran_param_test != NULL && "Memory exhausted");

  for(size_t i = 0; i <  dst.sz_strct; ++i){
    dst.ran_param_test[i] = cp_ran_param_test(src->ranParameter_Structure->list.array[i]);
  }

  return dst;
}

static
ran_parameter_value_t cp_ran_param_val(RANParameter_Value_t	const* src)
{
  assert(src != NULL);

  ran_parameter_value_t dst = {0}; 

  if(src->present == RANParameter_Value_PR_valueBoolean){
    dst.type = BOOLEAN_RAN_PARAMETER_VALUE;
    dst.bool_ran = src->choice.valueBoolean;

  } else if(src->present == RANParameter_Value_PR_valueInt){
    dst.type = INTEGER_RAN_PARAMETER_VALUE;
    dst.int_ran = src->choice.valueInt;

  }else if(src->present == RANParameter_Value_PR_valueReal){
    dst.type = REAL_RAN_PARAMETER_VALUE;
    dst.real_ran = src->choice.valueReal;

  }else if(src->present == RANParameter_Value_PR_valueBitS){
    dst.type = BIT_STRING_RAN_PARAMETER_VALUE;
    dst.bit_str_ran = copy_bit_string_to_ba(src->choice.valueBitS ); 

  }else if(src->present == RANParameter_Value_PR_valueOctS){
    dst.type = OCTET_STRING_RAN_PARAMETER_VALUE;
    dst.octet_str_ran = copy_ostring_to_ba(src->choice.valueOctS);

  }else if(src->present == RANParameter_Value_PR_valuePrintableString){
    dst.type = PRINTABLESTRING_RAN_PARAMETER_VALUE;
    dst.printable_str_ran = copy_ostring_to_ba( src->choice.valuePrintableString);

  } else {
    assert(0!=0 && "Unknown type");
  }

  return dst;
}

static
ran_parameter_value_t cp_key_flag_true(RANParameter_Testing_Item_Choice_ElementTrue_t const* src)
{
  assert(src != NULL);

  ran_parameter_value_t dst = cp_ran_param_val(&src->ranParameter_value);

  return dst;
}

static
ran_param_test_cond_comp_e cp_ran_param_test_cond_comp(long src)
{
  ran_param_test_cond_comp_e dst = {0};

  if(src == RANParameter_TestingCondition__ranP_Choice_comparison_equal	){
    dst = EQUAL_RAN_PARAM_TEST_COND_COMP;
  } else if(src == RANParameter_TestingCondition__ranP_Choice_comparison_difference	 ){
    dst = DIFFERENCE_RAN_PARAM_TEST_COND_COMP;
  } else if(src == RANParameter_TestingCondition__ranP_Choice_comparison_greaterthan	 ){
    dst = GREATERTHAN_RAN_PARAM_TEST_COND_COMP;
  } else if(src == RANParameter_TestingCondition__ranP_Choice_comparison_lessthan	 ){
    dst = LESSTHAN_RAN_PARAM_TEST_COND_COMP;
  } else if(src ==  RANParameter_TestingCondition__ranP_Choice_comparison_contains	){
    dst = CONTAINS_RAN_PARAM_TEST_COND_COMP;
  } else if(src ==  RANParameter_TestingCondition__ranP_Choice_comparison_starts_with	){
    dst = STARTS_WITH_RAN_PARAM_TEST_COND_COMP;
  } else {
    assert(0!=0 && "Unknown type");
  }

  return dst;
}

static
ran_param_test_cond_presence_e cp_ran_param_test_cond_presence(long src)
{
  ran_param_test_cond_presence_e dst = {0}; 

  if(src == RANParameter_TestingCondition__ranP_Choice_presence_present){
    dst = PRESENT_RAN_PARAM_TEST_COND_PRESENCE;
  } else if(src == RANParameter_TestingCondition__ranP_Choice_presence_configured){
    dst = CONFIGURED_RAN_PARAM_TEST_COND_PRESENCE;
  } else if(src == RANParameter_TestingCondition__ranP_Choice_presence_rollover){
    dst = ROLLOVER_RAN_PARAM_TEST_COND_PRESENCE;
  } else if(src == RANParameter_TestingCondition__ranP_Choice_presence_non_zero	 ) {
    dst = NON_ZERO_RAN_PARAM_TEST_COND_PRESENCE;
  } else {
    assert(0 != 0 && "Unknown type");
  }

  return dst;
}

static
ran_param_test_cond_t cp_test_cond(RANParameter_TestingCondition_t const* src)
{
  assert(src != NULL);

  ran_param_test_cond_t dst = {0}; 
  
  if(src->present == RANParameter_TestingCondition_PR_ranP_Choice_comparison){
    dst.cond = COMPARISON_RAN_PARAM_TEST_COND;
    dst.comp = cp_ran_param_test_cond_comp(src->choice.ranP_Choice_comparison) ;
  }else if(src->present == RANParameter_TestingCondition_PR_ranP_Choice_presence){
    dst.cond = PRESENCE_RAN_PARAM_TEST_COND;
    dst.presence = cp_ran_param_test_cond_presence(src->choice.ranP_Choice_presence) ;
  }else{
    assert(0!=0 && "Unknown type");
  }

  return dst;
}

static
ran_param_elm_key_false_t cp_key_flag_false(RANParameter_Testing_Item_Choice_ElementFalse_t const* src)
{
  assert(src != NULL);

  ran_param_elm_key_false_t dst = {0}; 

  // RAN Parameter Test Condition
  // 9.3.31
  // Mandatory
  dst.test_cond = cp_test_cond(&src->ranParameter_TestCondition); 

  // RAN Parameter Value
  // Optional
  // 9.3.14
  assert(src->ranParameter_Value == NULL && "Not implemented"); 

  // Logical OR
  // Optional
  // 9.3.25
  assert(src->logicalOR == NULL && "Not implemented");

  return dst;
}

static
ran_param_test_t cp_ran_param_test(RANParameter_Testing_Item_t const* src)
{
  assert(src != NULL);

  ran_param_test_t dst = {0}; 

  //RAN Parameter ID
  //Mandatory
  //Bug in the standard. 9.3.9 wrote in section 9. 
  //9.3.8 in ASN language. Probably 9.3.8 intended
  //1.. 4294967295
  assert(src->ranParameter_ID > 0 && src->ranParameter_ID < 4294967295 + 1);
  dst.ran_param_id = src->ranParameter_ID;

  if(src->ranParameter_Type.present == RANParameter_Testing_Item__ranParameter_Type_PR_ranP_Choice_List){
    dst.type = LIST_RAN_PARAMETER_TYPE;
    dst.lst = cp_lst(src->ranParameter_Type.choice.ranP_Choice_List);
  } else if(src->ranParameter_Type.present == RANParameter_Testing_Item__ranParameter_Type_PR_ranP_Choice_Structure ){
    dst.type = STRUCTURE_RAN_PARAMETER_TYPE;
    dst.strct = cp_strct(src->ranParameter_Type.choice.ranP_Choice_Structure);
  }else if(src->ranParameter_Type.present == RANParameter_Testing_Item__ranParameter_Type_PR_ranP_Choice_ElementTrue ){
    dst.type = ELEMENT_WITH_KEY_FLAG_TRUE_RAN_PARAMETER_TYPE;
    dst.flag_true = cp_key_flag_true(src->ranParameter_Type.choice.ranP_Choice_ElementTrue);
  }else if(src->ranParameter_Type.present == RANParameter_Testing_Item__ranParameter_Type_PR_ranP_Choice_ElementFalse){
    dst.type = ELEMENT_WITH_KEY_FLAG_FALSE_RAN_PARAMETER_TYPE;
    dst.flag_false = cp_key_flag_false(src->ranParameter_Type.choice.ranP_Choice_ElementFalse);
  }

  return dst;
}

static
ran_param_cond_crit_def_t cp_ran_param_cond_crit_def(RANParameter_Testing_t	const* src)
{
  assert(src != NULL);

  ran_param_cond_crit_def_t dst = {0}; 

  // [1 - 255 ]
  assert(src->list.count > 0 && src->list.count < 256); 
  dst.sz_ran_param_test = src->list.count;

  // RAN Parameter Test
  // 9.3.30
  dst.ran_param_test = calloc(dst.sz_ran_param_test, sizeof(ran_param_test_t) );
  assert(dst.ran_param_test != NULL && "Memory exhausted");

  for(size_t i = 0; i < dst.sz_ran_param_test; ++i){
    dst.ran_param_test[i] = cp_ran_param_test(src->list.array[i]); 
  }

  return dst;
}


static
ue_info_chng_t cp_ue_info_chng(E2SM_RC_EventTrigger_Format4_Item_t const* src)
{
  assert(src != NULL);

  ue_info_chng_t dst = {0}; 

  //  Event Trigger Condition ID
  //  Mandatory
  //  9.3.21
  // INTEGER (1..65535, …)
  assert(src->ric_eventTriggerCondition_ID > 0 && src->ric_eventTriggerCondition_ID < 65535+1);
  dst.ev_trig_cond_id = src->ric_eventTriggerCondition_ID; 

  // RRC State
  if(src->triggerType.present == TriggerType_Choice_PR_triggerType_Choice_RRCstate){
    dst.type = RRC_STATE_UE_INFO_CHNG_TRIGGER_TYPE;
    dst.rrc_state = cp_rrc_state_lst(src->triggerType.choice.triggerType_Choice_RRCstate);
  // UE Identifier Change
  // [1 - 512]
  } else if(src->triggerType.present == TriggerType_Choice_PR_triggerType_Choice_UEID){
    dst.type =UE_ID_CHANGE_UE_INFO_CHNG_TRIGGER_TYPE;
    dst.ue_id_chng = src->triggerType.choice.triggerType_Choice_UEID->ueIDchange_ID;

  // L2 State
  // 9.3.29
  // RAN Parameter Conditional Criteria Definition
  } else if(src->triggerType.present == TriggerType_Choice_PR_triggerType_Choice_L2state){
    dst.type =L2_STATE_UE_INFO_CHNG_TRIGGER_TYPE;
    dst.l2_state = cp_ran_param_cond_crit_def(&src->triggerType.choice.triggerType_Choice_L2state->associatedL2variables);

  } else {
    assert(0!=0 && "Unknown type");
  }

  // Associated UE Info 
  // Optional
  // 9.3.26
  assert(src->associatedUEInfo == NULL && "Not implemented");

  // Logical OR
  // Optional
  // 9.3.25
  assert(src->logicalOR == NULL && "Not implemented");

  return dst;
}

static
e2sm_rc_ev_trg_frmt_4_t cp_rc_ev_trigger_format_4(E2SM_RC_EventTrigger_Format4_t const* src)
{
  assert(src != NULL);

  e2sm_rc_ev_trg_frmt_4_t dst = {0}; 

 // Sequence of UE Information Change
 // [ 1 - 65535]
  assert(src->uEInfoChange_List.list.count > 0 && src->uEInfoChange_List.list.count <  65535 + 1);
  dst.sz_ue_info_chng = src->uEInfoChange_List.list.count;

  dst.ue_info_chng = calloc(dst.sz_ue_info_chng, sizeof( ue_info_chng_t ) );
  assert(dst.ue_info_chng != NULL && "Memory exhausted");

  for(size_t i = 0; i < dst.sz_ue_info_chng; ++i){
    dst.ue_info_chng[i] = cp_ue_info_chng(src->uEInfoChange_List.list.array[i]); 
  }

  return dst;
}

static
e2sm_rc_ev_trg_frmt_5_t cp_rc_ev_trigger_format_5(E2SM_RC_EventTrigger_Format5_t const* src)
{
  assert(src != NULL);

  e2sm_rc_ev_trg_frmt_5_t dst = {0}; 

  // On Demand
  // Mandatory
  if(src->onDemand == E2SM_RC_EventTrigger_Format5__onDemand_true){
    dst.on_demand = TRUE_ON_DEMAND_FRMT_5; 
  }else{
    assert(0!=0 && "Unknown type");
  } 
  
  // Associated UE Info
  // Optional
  // 9.3.26
  assert(src->associatedUEInfo == NULL && "Not implemented"); 

  // Associated Cell Info
  // Optional
  // 9.3.27
  assert(src->associatedCellInfo == NULL && "Not implemented");

  return dst;
}



e2sm_rc_event_trigger_t rc_dec_event_trigger_asn(size_t len, uint8_t const buf[len])
{
  assert(buf != NULL);
  assert(len != 0);

  E2SM_RC_EventTrigger_t  src = {0};
  defer({  ASN_STRUCT_RESET(asn_DEF_E2SM_RC_EventTrigger, &src); });
  E2SM_RC_EventTrigger_t* src_ref = &src;

  asn_dec_rval_t const ret = aper_decode(NULL, &asn_DEF_E2SM_RC_EventTrigger, (void **)&src_ref, buf, len, 0, 0);
  assert( ret.code == RC_OK);

  //  xer_fprint(stdout, &asn_DEF_E2SM_RC_EventTrigger, &src);
  //  fflush(stdout);

  e2sm_rc_event_trigger_t dst = {0}; 

  if(src.ric_eventTrigger_formats.present == E2SM_RC_EventTrigger__ric_eventTrigger_formats_PR_eventTrigger_Format1){

    dst.format = FORMAT_1_E2SM_RC_EV_TRIGGER_FORMAT;
    dst.frmt_1 = cp_rc_ev_trigger_format_1(src.ric_eventTrigger_formats.choice.eventTrigger_Format1);

  } else if(src.ric_eventTrigger_formats.present == E2SM_RC_EventTrigger__ric_eventTrigger_formats_PR_eventTrigger_Format2){
    dst.format = FORMAT_2_E2SM_RC_EV_TRIGGER_FORMAT;
    dst.frmt_2 = cp_rc_ev_trigger_format_2(src.ric_eventTrigger_formats.choice.eventTrigger_Format2);

  }else if(src.ric_eventTrigger_formats.present == E2SM_RC_EventTrigger__ric_eventTrigger_formats_PR_eventTrigger_Format3){
    dst.format = FORMAT_3_E2SM_RC_EV_TRIGGER_FORMAT;
    dst.frmt_3 = cp_rc_ev_trigger_format_3(src.ric_eventTrigger_formats.choice.eventTrigger_Format3);

  }else if(src.ric_eventTrigger_formats.present == E2SM_RC_EventTrigger__ric_eventTrigger_formats_PR_eventTrigger_Format4){
    dst.format = FORMAT_4_E2SM_RC_EV_TRIGGER_FORMAT;
    dst.frmt_4 = cp_rc_ev_trigger_format_4(src.ric_eventTrigger_formats.choice.eventTrigger_Format4);

  }else if(src.ric_eventTrigger_formats.present == E2SM_RC_EventTrigger__ric_eventTrigger_formats_PR_eventTrigger_Format5){
    dst.format = FORMAT_5_E2SM_RC_EV_TRIGGER_FORMAT;
    dst.frmt_5 = cp_rc_ev_trigger_format_5(src.ric_eventTrigger_formats.choice.eventTrigger_Format5);

  }else {
    assert(0!=0 && "Unknown format");
  }


  return dst;
}

static
param_report_def_t cp_param_report_def(E2SM_RC_ActionDefinition_Format1_Item_t const* src)
{
  assert(src != NULL);

  param_report_def_t dst = {0}; 

  // RAN Parameter ID
  // Mandatory
  // 9.3.8
  // [1 - 4294967295]
  assert(src->ranParameter_ID > 0);
  dst.ran_param_id = src->ranParameter_ID;

  // RAN Parameter Definition
  // Optional
  // 9.3.51
  assert(src->ranParameter_Definition == NULL && "Not implemented"); 

  return dst;
}


static
e2sm_rc_act_def_frmt_1_t cp_act_def_frmt_1( E2SM_RC_ActionDefinition_Format1_t const* src)
{
  assert(src != NULL);

  e2sm_rc_act_def_frmt_1_t dst = {0}; 

  // Parameters to be Reported List
  // [1-65535]
  assert(src->ranP_ToBeReported_List.list.count > 0 && src->ranP_ToBeReported_List.list.count < 65535 + 1);
  dst.sz_param_report_def = src->ranP_ToBeReported_List.list.count; 

  dst.param_report_def = calloc(dst.sz_param_report_def , sizeof(param_report_def_t));
  assert(dst.param_report_def != NULL && "memory exhausted");

  for(size_t i = 0; i <  dst.sz_param_report_def; ++i){
    dst.param_report_def[i] =	cp_param_report_def(src->ranP_ToBeReported_List.list.array[i]);
  }

  return dst;
}

static
ran_parameter_value_t dec_ran_parameter_value(RANParameter_Value_t	const* src)
{
  assert(src != NULL);

  ran_parameter_value_t dst = {0}; 

  if(src->present ==RANParameter_Value_PR_valueBoolean){
    dst.type = BOOLEAN_RAN_PARAMETER_VALUE ;  
    dst.bool_ran = src->choice.valueBoolean;
  } else if(src->present ==RANParameter_Value_PR_valueInt){
    dst.type = INTEGER_RAN_PARAMETER_VALUE ;  
    dst.int_ran = src->choice.valueInt;
  }else if(src->present ==RANParameter_Value_PR_valueReal){
    dst.type = REAL_RAN_PARAMETER_VALUE ;  
    dst.real_ran = src->choice.valueReal;
  }else if(src->present ==RANParameter_Value_PR_valueBitS){
    dst.type = BIT_STRING_RAN_PARAMETER_VALUE;  
    dst.bit_str_ran = copy_bit_string_to_ba(src->choice.valueBitS);
  }else if(src->present ==RANParameter_Value_PR_valueOctS){
    dst.type = OCTET_STRING_RAN_PARAMETER_VALUE;  
    dst.octet_str_ran = copy_ostring_to_ba(src->choice.valueOctS);
  }else if(src->present == RANParameter_Value_PR_valuePrintableString){
    dst.type = PRINTABLESTRING_RAN_PARAMETER_VALUE;  
    dst.printable_str_ran = copy_ostring_to_ba(src->choice.valuePrintableString);
  } else {
    assert(0!=0 && "Unknown type");
  }

  return dst;
}

static
ran_param_val_type_t cp_ran_param_value_type(RANParameter_ValueType_t	const* src);

static
seq_ran_param_t cp_seq_ran_param_strc_it(RANParameter_STRUCTURE_Item_t const* src)
{
  assert(src != NULL);

  seq_ran_param_t dst = {0}; 

  //RAN Parameter ID
  //Mandatory
  //9.3.8
  // [1 - 4294967295]
  assert(src->ranParameter_ID > 0);
  dst.ran_param_id = src->ranParameter_ID;

  // RAN Parameter Value Type
  // 9.3.11
  // Mandatory
  dst.ran_param_val = cp_ran_param_value_type(src->ranParameter_valueType);

  return dst;
}

static
ran_param_struct_t* cp_ran_parameter_strct(RANParameter_STRUCTURE_t const* src)
{
  assert(src != NULL);

  ran_param_struct_t* dst = calloc(1, sizeof(ran_param_struct_t ));
  assert(dst != NULL && "Memory exhausted" );

  // [1-65535]
  assert(src->sequence_of_ranParameters != NULL);
  assert(src->sequence_of_ranParameters->list.count > 0 && src->sequence_of_ranParameters->list.count <  65535 + 1);
  dst->sz_ran_param_struct = src->sequence_of_ranParameters->list.count;

  dst->ran_param_struct = calloc(dst->sz_ran_param_struct, sizeof(seq_ran_param_t));
  assert(dst->ran_param_struct != NULL && "Memory exhausted" );

  for(size_t i = 0; i < dst->sz_ran_param_struct; ++i){
    dst->ran_param_struct[i] = cp_seq_ran_param_strc_it(src->sequence_of_ranParameters->list.array[i]);
  }

  return dst;
}

/*
static
lst_ran_param_t cp_lst_ran_param(RANParameter_STRUCTURE_Item_t const* src)
{
  assert(src != NULL);

  lst_ran_param_t dst = {0}; 

  // RAN Parameter ID
  // Mandatory
  // 9.3.8
  //1.. 4294967295
  assert(src->ranParameter_ID > 0 && src->ranParameter_ID <  4294967295 +1);
  dst.ran_param_id = src->ranParameter_ID;

  // RAN Parameter Structure
  // Mandatory
  // 9.3.12
  dst.ran_param_struct = cp_ran_param_struct(src->ranParameter_valueType);

  return dst;
}

static
ran_param_list_t* cp_ran_param_list( RANParameter_STRUCTURE_t const* src)
{
  assert(src != NULL);

  ran_param_list_t* dst = calloc(1, sizeof( ran_param_list_t));
  assert(dst != NULL && "Memory exhausted");

  // [0- 65535]
  assert(src->list_of_ranParameter.list.count  <  65535 + 1);
  dst->sz_lst_ran_param =  src->list_of_ranParameter.list.count ;

  for(size_t i = 0; i <  dst->sz_lst_ran_param; ++i){
    dst->lst_ran_param[i] = cp_lst_ran_param(src->list_of_ranParameter.list.array[i]); 
  }

  return dst;
}

*/

static
seq_ran_param_t dec_ran_param_struct(RANParameter_STRUCTURE_Item_t const* src)
{
  assert(src != NULL);

  seq_ran_param_t dst = {0}; 

  //RAN Parameter ID
  //Mandatory
  //9.3.8
  // [1 - 4294967295]
  assert(src->ranParameter_ID > 0);
  dst.ran_param_id = src->ranParameter_ID;

  // RAN Parameter Value Type
  // 9.3.11
  // Mandatory
  assert(src->ranParameter_valueType != NULL); 
  dst.ran_param_val = cp_ran_param_value_type(src->ranParameter_valueType);

  return dst;
}

static
lst_ran_param_t dec_lst_ran_param(RANParameter_STRUCTURE_t const* src)
{
  assert(src != NULL);

  lst_ran_param_t dst = {0};

  // Bug in the standard. RAN Parameter List 9.3.13 
  // has a mandatory ie RAN Parameter ID 9.3.8 
  // and a mandatory ie RAN Parameter Structure 9.3.12
  // However, the ASN  
  // RANParameter-LIST ::= SEQUENCE {
  // list-of-ranParameter  SEQUENCE (SIZE(1..maxnoofItemsinList)) OF RANParameter-STRUCTURE, 
  // ..
  // }
  //
  // Misses RAN Parameter ID and only has RAN Parameter Structure

  // RAN Parameter ID
  // Mandatory
  // 9.3.8
  //1.. 4294967295
  // Let's ignore the english written standard and believe the ASN.1 is the correct
  //  uint32_t ran_param_id;

  // RAN Parameter Structure
  // Mandatory
  // 9.3.12
  //ran_param_struct_t ran_param_struct;

  assert(src->sequence_of_ranParameters->list.count > 0 && src->sequence_of_ranParameters->list.count < 65535 + 1);

  const size_t sz = src->sequence_of_ranParameters->list.count;
  dst.ran_param_struct.sz_ran_param_struct = sz;
  dst.ran_param_struct.ran_param_struct = calloc(sz, sizeof(seq_ran_param_t));
  assert(dst.ran_param_struct.ran_param_struct != NULL && "Memory exhausted");

  for(size_t i = 0; i < sz; ++i){
   dst.ran_param_struct.ran_param_struct[i] = dec_ran_param_struct(src->sequence_of_ranParameters->list.array[i]);
  }

  return dst;
}


static
ran_param_val_type_t cp_ran_param_value_type(RANParameter_ValueType_t	const* src)
{
  assert(src != NULL);

  ran_param_val_type_t dst = {0}; 

  if(src->present == RANParameter_ValueType_PR_ranP_Choice_ElementTrue){
    dst.type = ELEMENT_KEY_FLAG_TRUE_RAN_PARAMETER_VAL_TYPE;  

    dst.flag_true = calloc(1, sizeof( ran_parameter_value_t)); 
    assert(dst.flag_true != NULL && "Memory exhausted" );

    *dst.flag_true = dec_ran_parameter_value(&src->choice.ranP_Choice_ElementTrue->ranParameter_value);

  } else if(src->present == RANParameter_ValueType_PR_ranP_Choice_ElementFalse ){
    dst.type = ELEMENT_KEY_FLAG_FALSE_RAN_PARAMETER_VAL_TYPE;  

    dst.flag_false = calloc(1, sizeof( ran_parameter_value_t)); 
    assert(dst.flag_false != NULL && "Memory exhausted" );

    *dst.flag_false = dec_ran_parameter_value(src->choice.ranP_Choice_ElementFalse->ranParameter_value);

  }else if(src->present ==  RANParameter_ValueType_PR_ranP_Choice_Structure){
    dst.type = STRUCTURE_RAN_PARAMETER_VAL_TYPE;  
    dst.strct = cp_ran_parameter_strct(src->choice.ranP_Choice_Structure->ranParameter_Structure); //->sequence_of_ranParameters->list.count;

  }else if(src->present == RANParameter_ValueType_PR_ranP_Choice_List){
    dst.type = LIST_RAN_PARAMETER_VAL_TYPE;  
    dst.lst = calloc(1, sizeof( ran_param_list_t)); 
    assert(dst.lst != NULL && "Memory exhausted");

    dst.lst->sz_lst_ran_param = src->choice.ranP_Choice_List->ranParameter_List->list_of_ranParameter.list.count;
    dst.lst->lst_ran_param = calloc( dst.lst->sz_lst_ran_param, sizeof(lst_ran_param_t));
    assert(dst.lst->lst_ran_param != NULL && "Memory exhausted");
    for(size_t i =0; i < dst.lst->sz_lst_ran_param; ++i){
      dst.lst->lst_ran_param[i] = dec_lst_ran_param(src->choice.ranP_Choice_List->ranParameter_List->list_of_ranParameter.list.array[i]); 
    }

  } else {
    assert(0!=0 && "Not implemented");
  }

  return dst;
}

static
seq_ran_param_t dec_seq_ran_param(RIC_PolicyAction_RANParameter_Item_t const* src)
{
  assert(src != NULL);
  
  seq_ran_param_t dst = {0}; 

  //RAN Parameter ID
  //Mandatory
  //9.3.8
  // [1 - 4294967295]
  assert(src->ranParameter_ID > 0 && src->ranParameter_ID < 4294967295 +1);
  dst.ran_param_id = src->ranParameter_ID;

  // RAN Parameter Value Type
  // 9.3.11
  // Mandatory
  dst.ran_param_val = cp_ran_param_value_type(&src->ranParameter_valueType);

  return dst;
}



static
policy_action_t cp_policy_action(RIC_PolicyAction_t const* src)
{
  assert(src != NULL);

  policy_action_t dst = {0}; 


  //  Policy Action ID
  //  Mandatory
  //  9.3.6
  //  [1 - 65535]
  assert(src->ric_PolicyAction_ID > 0 && src->ric_PolicyAction_ID < 65535 + 1);
  dst.policy_act_id = src->ric_PolicyAction_ID;

  // Sequence of RAN Parameters
  // [0- 65535]
  if(src->ranParameters_List != NULL){
    assert(src->ranParameters_List->list.count > 0 && src->ranParameters_List->list.count < 65535);
    dst.sz_seq_ran_param = src->ranParameters_List->list.count ;
    dst.seq_ran_param = calloc(dst.sz_seq_ran_param, sizeof(seq_ran_param_t) );
    assert(dst.seq_ran_param != NULL && "Memory exhausted");

    for(int i = 0; i < src->ranParameters_List->list.count; ++i ){
     dst.seq_ran_param[i] = dec_seq_ran_param(src->ranParameters_List->list.array[i]); 
    }
  }

  // RIC Policy decision
  // Optional
  assert(src->ric_PolicyDecision == NULL && "Not implemented");

  return dst;
}


static
policy_cond_t cp_policy_cond(E2SM_RC_ActionDefinition_Format2_Item_t const* src)
{
  assert(src != NULL);

  policy_cond_t dst = {0}; 


  // Policy Action Definition
  // Mandatory
  // 9.3.20
  dst.pol_act = cp_policy_action(&src->ric_PolicyAction);

  // Policy Condition Definition
  // Optional
  // 9.3.29
  assert(src->ric_PolicyConditionDefinition == NULL && "Not implemented");

  return dst;
}


static
e2sm_rc_act_def_frmt_2_t cp_act_def_frmt_2(E2SM_RC_ActionDefinition_Format2_t const* src)
{
  assert(src != NULL);

  e2sm_rc_act_def_frmt_2_t dst = {0}; 

  // Sequence of Policy Conditions
  // [1 - 65535]
  assert(src->ric_PolicyConditions_List.list.count > 0 && src->ric_PolicyConditions_List.list.count <   65535 + 1);

  dst.sz_policy_cond = src->ric_PolicyConditions_List.list.count;

  dst.policy_cond = calloc(dst.sz_policy_cond, sizeof(policy_cond_t) );
  assert(dst.policy_cond != NULL && "Memory exhausted");
  
  for(size_t i = 0; i < dst.sz_policy_cond; ++i){
    dst.policy_cond[i] = cp_policy_cond(src->ric_PolicyConditions_List.list.array[i]);
  }

  return dst;
}

static
ran_param_ins_t cp_ran_param_ins( E2SM_RC_ActionDefinition_Format3_Item_t const* src)
{
  assert(src != NULL);

  ran_param_ins_t dst = {0}; 

  // RAN Parameter ID
  // Mandatory
  // 9.3.8
  // [1 - 4294967295]
  assert(src->ranParameter_ID > 0);
  dst.ran_id = src->ranParameter_ID;

  // RAN Parameter Definition
  // Optional
  // 9.3.51
  assert(src->ranParameter_Definition == NULL && "Not implemented");

  return dst;
}


static
e2sm_rc_act_def_frmt_3_t cp_act_def_frmt_3(E2SM_RC_ActionDefinition_Format3_t const* src)
{
  assert(src != NULL);

  e2sm_rc_act_def_frmt_3_t dst = {0}; 

  // Insert Indication ID
  // Mandatory
  // 9.3.16
  // [1 - 65535] 
  assert(src->ric_InsertIndication_ID > 0 && src->ric_InsertIndication_ID < 65535 + 1); 
  dst.id = src->ric_InsertIndication_ID;

  // List of RAN parameters for Insert
  // Indication
  // [1 - 65535]
  assert(src->ranP_InsertIndication_List.list.count > 0 && src->ranP_InsertIndication_List.list.count <   65535 + 1);

  dst.sz_ran_param_ins = src->ranP_InsertIndication_List.list.count; 
  dst.ran_param = calloc(dst.sz_ran_param_ins, sizeof( ran_param_ins_t ) );
  assert(dst.ran_param != NULL && "memory exhausted");

  for(size_t i = 0; i < dst.sz_ran_param_ins; ++i){
    dst.ran_param[i] = cp_ran_param_ins(src->ranP_InsertIndication_List.list.array[i]);
  }

  //  UE ID
  //  Optional
  //  9.3.10
  assert(src->ueID == NULL && "Not implemented"); 

  return dst;
}

static
ran_param_ins_ind_t cp_ran_param_ins_ind(E2SM_RC_ActionDefinition_Format4_RANP_Item_t const* src)
{
  assert(src != NULL);

  ran_param_ins_ind_t dst = {0}; 

  // RAN Parameter ID
  // Mandatory
  // 9.3.8
  // [1.. 429496729 ]
  assert(src->ranParameter_ID > 0); 
  dst.ran_param_id = src->ranParameter_ID;

  // RAN Parameter Definition
  // Optional
  // 9.3.51
  assert(src->ranParameter_Definition == NULL && "Not implemented");

  return dst;
}


static
seq_ins_ind_act_def_t cp_seq_ins_ind_act_def(E2SM_RC_ActionDefinition_Format4_Indication_Item_t const* src)
{
  assert(src != NULL);

  seq_ins_ind_act_def_t dst = {0} ;

    // Insert Indication ID
  // Mandatory
  // 9.3.16
  // [1 - 65535]
  assert(src->ric_InsertIndication_ID > 0);
  dst.ind_id = src->ric_InsertIndication_ID;

  // List of RAN parameters for
  // Insert Indication
  // [1-65535]
  assert(src->ranP_InsertIndication_List.list.count > 0 && src->ranP_InsertIndication_List.list.count < 65535+1); 
  
  dst.sz_ran_param_ins_ind = src->ranP_InsertIndication_List.list.count ;

  dst.ran_param_ins_ind = calloc(dst.sz_ran_param_ins_ind, sizeof( ran_param_ins_ind_t) );
  assert(dst.ran_param_ins_ind != NULL && "Memory exhausted");

  for(size_t i = 0; i < dst.sz_ran_param_ins_ind; ++i){
    dst.ran_param_ins_ind[i] = cp_ran_param_ins_ind(src->ranP_InsertIndication_List.list.array[i]);
  }

  return dst;
}

static
seq_ins_style_t cp_seq_ins_styles(E2SM_RC_ActionDefinition_Format4_Style_Item_t const* src)
{
  assert(src != NULL);

  seq_ins_style_t dst = {0}; 

  // Requested Insert Style
  // Mandatory
  // 9.3.3
  // 6.2.2.2. in E2 SM common 
  // Integer
  dst.req_insert_style = src->requested_Insert_Style_Type;

  // Sequence of Insert Indication
  // Action Definition
  // [1-63]
  assert(src->ric_InsertIndication_List.list.count > 0 && src->ric_InsertIndication_List.list.count < 64);
 dst.sz_seq_ins_ind_act_def = src->ric_InsertIndication_List.list.count; 

  dst.seq_ins_ind_act_def = calloc(dst.sz_seq_ins_ind_act_def, sizeof(seq_ins_ind_act_def_t));
  assert(dst.seq_ins_ind_act_def != NULL && "Memory exhausted");

  for(size_t i = 0; i < dst.sz_seq_ins_ind_act_def; ++i){
    dst.seq_ins_ind_act_def[i] = cp_seq_ins_ind_act_def(src->ric_InsertIndication_List.list.array[i]);
  }

  return dst;
}


static
e2sm_rc_act_def_frmt_4_t cp_act_def_frmt_4(E2SM_RC_ActionDefinition_Format4_t const* src)
{
  assert(src != NULL);

  e2sm_rc_act_def_frmt_4_t dst = {0}; 

  // Sequence of Insert Styles for
  // Multiple Actions
  // [1-4]
  assert(src->ric_InsertStyle_List.list.count > 0 && src->ric_InsertStyle_List.list.count < 5);
  dst.sz_seq_ins_style =  src->ric_InsertStyle_List.list.count; 

  dst.seq_ins_style = calloc(dst.sz_seq_ins_style, sizeof(seq_ins_style_t));
  assert(dst.seq_ins_style != NULL && "memory exhausted");

  for(size_t i = 0; i < dst.sz_seq_ins_style; ++i){
    dst.seq_ins_style[i] =	cp_seq_ins_styles(src->ric_InsertStyle_List.list.array[i]);
  }

  // UE ID
  // Optional
  // 9.3.10
  assert(src->ueID == NULL && "Not implemented"); 

  return dst;
}


e2sm_rc_action_def_t rc_dec_action_def_asn(size_t len, uint8_t const action_def[len])
{
  assert(action_def != NULL);
  assert(len != 0);

  E2SM_RC_ActionDefinition_t src = {0};
  defer({  ASN_STRUCT_RESET(asn_DEF_E2SM_RC_ActionDefinition, &src); });
  E2SM_RC_ActionDefinition_t* src_ref = &src;

  asn_dec_rval_t const ret = aper_decode(NULL, &asn_DEF_E2SM_RC_ActionDefinition, (void **)&src_ref, action_def, len, 0, 0);
  assert( ret.code == RC_OK);

  //  xer_fprint(stdout, &asn_DEF_E2SM_RC_EventTrigger, &src);
  //  fflush(stdout);

  e2sm_rc_action_def_t dst = {0}; 

  //  RIC Style Type
  //  Mandatory
  //  9.3.3
  // Defined in common 6.2.2.2.
  dst.ric_style_type = src.ric_Style_Type; 

  if(src.ric_actionDefinition_formats.present == E2SM_RC_ActionDefinition__ric_actionDefinition_formats_PR_actionDefinition_Format1){
    dst.format = FORMAT_1_E2SM_RC_ACT_DEF;
    dst.frmt_1 = cp_act_def_frmt_1(src.ric_actionDefinition_formats.choice.actionDefinition_Format1);

  } else if(src.ric_actionDefinition_formats.present ==  E2SM_RC_ActionDefinition__ric_actionDefinition_formats_PR_actionDefinition_Format2){
    dst.format = FORMAT_2_E2SM_RC_ACT_DEF;
    dst.frmt_2 = cp_act_def_frmt_2(src.ric_actionDefinition_formats.choice.actionDefinition_Format2);

  }else if(src.ric_actionDefinition_formats.present == E2SM_RC_ActionDefinition__ric_actionDefinition_formats_PR_actionDefinition_Format3 ){
    dst.format = FORMAT_3_E2SM_RC_ACT_DEF ;
    dst.frmt_3 = cp_act_def_frmt_3(src.ric_actionDefinition_formats.choice.actionDefinition_Format3);

  } else if(src.ric_actionDefinition_formats.present == E2SM_RC_ActionDefinition__ric_actionDefinition_formats_PR_actionDefinition_Format4 ){
    dst.format = FORMAT_4_E2SM_RC_ACT_DEF ;
    dst.frmt_4 = cp_act_def_frmt_4(src.ric_actionDefinition_formats.choice.actionDefinition_Format4);

  } else {
    assert(0!=0 && "Unknown type");
  }

  return dst;
}

static
e2sm_rc_ind_hdr_frmt_1_t cp_ind_hdr_frmt_1(E2SM_RC_IndicationHeader_Format1_t const* src)
{
  assert(src != NULL);

  e2sm_rc_ind_hdr_frmt_1_t dst = {0}; 

  // Event Trigger Condition ID
  // Optional
  // 9.3.21
  // [1 - 65535]
  assert(src->ric_eventTriggerCondition_ID != NULL && "Optional, but only one member" );

  dst.ev_trigger_id = malloc(sizeof(uint16_t));
  assert(dst.ev_trigger_id != NULL && "Memory exhausted" );

  assert(*src->ric_eventTriggerCondition_ID > 0 && *src->ric_eventTriggerCondition_ID < 65535+1);

  *dst.ev_trigger_id = *src->ric_eventTriggerCondition_ID;

  return dst;
}

static
e2sm_rc_ind_hdr_frmt_2_t cp_ind_hdr_frmt_2(E2SM_RC_IndicationHeader_Format2_t const* src)
{
  assert(src != NULL);

  e2sm_rc_ind_hdr_frmt_2_t dst = {0}; 

  // UE ID
  // Mandatory
  // 9.3.10
  dst.ue_id = dec_ue_id_asn(&src->ueID);

  // RIC Insert Style Type
  // Mandatory
  // 9.3.3
  // 6.2.2.2. From common SM
  // RIC Style Type 
  // Integer
  dst.ric_style_type = src->ric_InsertStyle_Type;

  // Insert Indication ID
  // Mandatory
  // 9.3.16
  // [1 - 65535]
  assert(src->ric_InsertIndication_ID > 0 ); 
  dst.ins_ind_id = src->ric_InsertIndication_ID; 

  return dst;
}

static
e2sm_rc_ind_hdr_frmt_3_t cp_ind_hdr_frmt_3(E2SM_RC_IndicationHeader_Format3_t const* src)
{
  assert(src != NULL);

  e2sm_rc_ind_hdr_frmt_3_t dst = {0}; 

  // Event Trigger Condition ID
  // Optional
  // 9.3.21
  // [1 - 65535]
  if(src->ric_eventTriggerCondition_ID != NULL){
    assert(*src->ric_eventTriggerCondition_ID > 0 && *src->ric_eventTriggerCondition_ID < 65535+1); 

    dst.ev_trigger_cond = malloc(sizeof(uint16_t));
    assert(dst.ev_trigger_cond != NULL && "Memory exhausted");
 
    *dst.ev_trigger_cond = *src->ric_eventTriggerCondition_ID;
  }

  // UE ID
  // Optional 
  // 9.3.10
  if(src->ueID != NULL){
  
    dst.ue_id = calloc(1, sizeof(ue_id_e2sm_t));
    assert(dst.ue_id != NULL && "Memory exhausted");
    
    *dst.ue_id = dec_ue_id_asn(src->ueID);
  } 

  return dst;
}

e2sm_rc_ind_hdr_t rc_dec_ind_hdr_asn(size_t len, uint8_t const ind_hdr[len])
{
  assert(ind_hdr != NULL);
  assert(len != 0);

  E2SM_RC_IndicationHeader_t src = {0};
  defer({  ASN_STRUCT_RESET(asn_DEF_E2SM_RC_IndicationHeader, &src); });
  E2SM_RC_IndicationHeader_t* src_ref = &src;

  asn_dec_rval_t const ret = aper_decode(NULL, &asn_DEF_E2SM_RC_IndicationHeader, (void **)&src_ref, ind_hdr, len, 0, 0);
  assert(ret.code == RC_OK);

  //  xer_fprint(stdout, &asn_DEF_E2SM_RC_EventTrigger, &src);
  //  fflush(stdout);

  e2sm_rc_ind_hdr_t dst = {0}; 

  if(src.ric_indicationHeader_formats.present == E2SM_RC_IndicationHeader__ric_indicationHeader_formats_PR_indicationHeader_Format1){
    dst.format = FORMAT_1_E2SM_RC_IND_HDR;
    dst.frmt_1 = cp_ind_hdr_frmt_1(src.ric_indicationHeader_formats.choice.indicationHeader_Format1);
  }else if(src.ric_indicationHeader_formats.present == E2SM_RC_IndicationHeader__ric_indicationHeader_formats_PR_indicationHeader_Format2){
    dst.format =FORMAT_2_E2SM_RC_IND_HDR   ;
    dst.frmt_2 = cp_ind_hdr_frmt_2(src.ric_indicationHeader_formats.choice.indicationHeader_Format2);
  }else if(src.ric_indicationHeader_formats.present == E2SM_RC_IndicationHeader__ric_indicationHeader_formats_PR_indicationHeader_Format3){
    dst.format = FORMAT_3_E2SM_RC_IND_HDR;
    dst.frmt_3 = cp_ind_hdr_frmt_3(src.ric_indicationHeader_formats.choice.indicationHeader_Format3);
  } else {
    assert(0!=0 && "Unknown format");
  }

  return dst;
}

static
seq_ran_param_t dec_ind_msg_frmt_1_it(E2SM_RC_IndicationMessage_Format1_Item_t const* src)
{
  assert(src != NULL);

  seq_ran_param_t dst = {0}; 

  //RAN Parameter ID
  //Mandatory
  //9.3.8
  // [1 - 4294967295]
  assert(src->ranParameter_ID > 0);
  dst.ran_param_id = src->ranParameter_ID;

  // RAN Parameter Value Type
  // 9.3.11
  // Mandatory
  dst.ran_param_val = cp_ran_param_value_type(&src->ranParameter_valueType);

  return dst;
}


static
e2sm_rc_ind_msg_frmt_1_t dec_ind_msg_frmt_1(E2SM_RC_IndicationMessage_Format1_t const* src)
{
  assert(src != NULL);
  e2sm_rc_ind_msg_frmt_1_t dst = {0}; 

  //  Sequence of RAN
  //  Parameters
  //  [1 - 65535]
  assert(src->ranP_Reported_List.list.count > 0 && src->ranP_Reported_List.list.count < 65535+1);
  
  dst.sz_seq_ran_param = src->ranP_Reported_List.list.count; 
  dst.seq_ran_param = calloc(dst.sz_seq_ran_param, sizeof(seq_ran_param_t));
  assert(dst.seq_ran_param != NULL && "Memory exhausted" );

  for(size_t i = 0; i < dst.sz_seq_ran_param; ++i){
    dst.seq_ran_param[i] = dec_ind_msg_frmt_1_it(src->ranP_Reported_List.list.array[i]);
  }

  return dst;
}

static
seq_ran_param_t dec_frmt_2_ran_param(E2SM_RC_IndicationMessage_Format2_RANParameter_Item_t const* src)
{
  assert(src != NULL);

  seq_ran_param_t dst = {0}; 

  //RAN Parameter ID
  //Mandatory
  //9.3.8
  // [1 - 4294967295]
  assert(src->ranParameter_ID > 0);
  dst.ran_param_id = src->ranParameter_ID;

  // RAN Parameter Value Type
  // 9.3.11
  // Mandatory
  dst.ran_param_val = cp_ran_param_value_type(&src->ranParameter_valueType);

  return dst;
}

static
seq_ue_id_t dec_seq_ue_id(E2SM_RC_IndicationMessage_Format2_Item_t const* src)
{
  assert(src != NULL);

  seq_ue_id_t dst = {0}; 

  // UE ID
  // Mandatory
  // 9.3.10
  dst.ue_id = dec_ue_id_asn(&src->ueID);

  // Sequence of
  // RAN Parameter
  // [1- 65535]
  assert(src->ranP_List.list.count > 0 && src->ranP_List.list.count <  65535+1); 

  dst.sz_seq_ran_param = src->ranP_List.list.count;

  dst.seq_ran_param = calloc(dst.sz_seq_ran_param ,sizeof(seq_ran_param_t));
  assert(dst.seq_ran_param != NULL && "Memory exhausted" );

  for(size_t i =0; i < dst.sz_seq_ran_param; ++i){
    dst.seq_ran_param[i] = dec_frmt_2_ran_param(src->ranP_List.list.array[i]); 
  }

  return dst;
}


static
e2sm_rc_ind_msg_frmt_2_t dec_ind_msg_frmt_2(E2SM_RC_IndicationMessage_Format2_t const* src)
{
  assert(src != NULL);

  e2sm_rc_ind_msg_frmt_2_t dst = {0}; 

  //Sequence of UE Identifier
  //[1-65535]
  assert(src->ueParameter_List.list.count > 0 && src->ueParameter_List.list.count < 65535+1);

  dst.sz_seq_ue_id = src->ueParameter_List.list.count; 

  dst.seq_ue_id = calloc(dst.sz_seq_ue_id, sizeof(seq_ue_id_t ) );
  assert(dst.seq_ue_id != NULL && "Memory exhausted");

  for(size_t i = 0; i < dst.sz_seq_ue_id; ++i){
    dst.seq_ue_id[i] = dec_seq_ue_id( src->ueParameter_List.list.array[i]);
  } 

  return dst;
}

static
seq_cell_info_t dec_ind_msg_frmt_3_it(E2SM_RC_IndicationMessage_Format3_Item_t const* src)
{
  assert(src != NULL);

  seq_cell_info_t dst = {0}; 

  // Cell Global ID
  // Mandatory
  // 9.3.36
  // 6.2.2.5
  dst.cell_global_id = dec_cell_global_id_asn(&src->cellGlobal_ID);

  // Cell Context Information
  // Optional
  // OCTET STRING
  assert(src->cellContextInfo == NULL && "Not implemented" );

  // Cell Deleted
  // Optional
  // BOOLEAN
  assert(src->cellDeleted == NULL && "not implemented");

  // Neighbour Relation Table
  // Optional
  // 9.3.38
  assert(src->neighborRelation_Table == NULL && "Not implemented");

  return dst;
}

static
e2sm_rc_ind_msg_frmt_3_t dec_ind_msg_frmt_3(E2SM_RC_IndicationMessage_Format3_t const* src)
{
  assert(src != NULL);

  e2sm_rc_ind_msg_frmt_3_t dst = {0}; 

  // Sequence of Cell Information
  // [1 - 65535]
  assert(src->cellInfo_List.list.count > 0 &&  src->cellInfo_List.list.count < 65535+1);

  dst.sz_seq_cell_info = src->cellInfo_List.list.count;

  dst.seq_cell_info = calloc(dst.sz_seq_cell_info , sizeof(seq_cell_info_t ));
  assert(dst.seq_cell_info != NULL && "Memory exhausted");

  for(size_t i = 0; i < dst.sz_seq_cell_info; ++i){
    dst.seq_cell_info[i] = dec_ind_msg_frmt_3_it(src->cellInfo_List.list.array[i]);
  }

  return dst;
}

static
seq_ue_info_t dec_ind_msg_frmt_4_it_ue_info(E2SM_RC_IndicationMessage_Format4_ItemUE_t const* src)
{
  assert(src != NULL);

  seq_ue_info_t dst = {0}; 

  // UE ID
  // Mandatory
  // 9.3.10
  dst.ue_id = dec_ue_id_asn(&src->ueID);

  // UE Context Information
  // Optional
  // OCTET STRING
  assert(src->ueContextInfo == NULL && "Not implemented");

  // Cell Global ID
  // Mandatory
  // 9.3.36
  dst.cell_global_id = dec_cell_global_id_asn(&src->cellGlobal_ID);

  return dst;
}

static
seq_cell_info_2_t dec_ind_msg_frmt_4_it_dell_info(E2SM_RC_IndicationMessage_Format4_ItemCell_t const* src)
{
  assert(src != NULL);

  seq_cell_info_2_t dst = {0}; 

  // Cell Global ID
  // Mandatory
  // 9.3.36
  // 6.2.2.5. 
  dst.cell_global_id = dec_cell_global_id_asn(&src->cellGlobal_ID);

  // Cell Context Information
  // Optional
  // OCTET STRING
  assert(src->cellContextInfo == NULL && "Not implemented");

  // Neighbour Relation Table
  // Optional
  // 9.3.38
  assert(src->neighborRelation_Table == NULL && "Not implemented");

  return dst;
}

static
e2sm_rc_ind_msg_frmt_4_t dec_ind_msg_frmt_4(E2SM_RC_IndicationMessage_Format4_t const* src)
{
  assert(src != NULL);

  e2sm_rc_ind_msg_frmt_4_t dst = {0};

  //Sequence of UE Information
  // [0-65535]
  assert(src->ueInfo_List.list.count < 65536);
  if(src->ueInfo_List.list.count > 0){
    dst.sz_seq_ue_info = src->ueInfo_List.list.count; 
    dst.seq_ue_info = calloc(dst.sz_seq_ue_info, sizeof(seq_ue_info_t)); 
    assert(dst.seq_ue_info != NULL && "Memory exhausted");
  }

  for(size_t i = 0; i < dst.sz_seq_ue_info; ++i){
    dst.seq_ue_info[i] = dec_ind_msg_frmt_4_it_ue_info(src->ueInfo_List.list.array[i]); 
  }

  // Sequence of Cell Information
  // [0-65535]
  assert(src->cellInfo_List.list.count < 65536); 
  if(src->cellInfo_List.list.count > 0){
    dst.sz_seq_cell_info_2 = src->cellInfo_List.list.count; 
    dst.seq_cell_info_2 = calloc(dst.sz_seq_cell_info_2, sizeof(seq_cell_info_2_t)); 
    assert(dst.seq_cell_info_2 != NULL && "Memory exhausted");
  }

  for(size_t i = 0; i < dst.sz_seq_cell_info_2; ++i){
    dst.seq_cell_info_2[i] = dec_ind_msg_frmt_4_it_dell_info(src->cellInfo_List.list.array[i]); 
  }

  return dst;
}

static
seq_ran_param_t dec_ind_msg_frmt_5_it(E2SM_RC_IndicationMessage_Format5_Item_t const* src)
{
  assert(src != NULL);

  seq_ran_param_t dst = {0}; 

  //RAN Parameter ID
  //Mandatory
  //9.3.8
  // [1 - 4294967295]
  assert(src->ranParameter_ID > 0);
  dst.ran_param_id = src->ranParameter_ID;
  
  // RAN Parameter Value Type
  // 9.3.11
  // Mandatory
  dst.ran_param_val = cp_ran_param_value_type(&src->ranParameter_valueType); 

  return dst;
}

static
e2sm_rc_ind_msg_frmt_5_t dec_ind_msg_frmt_5(E2SM_RC_IndicationMessage_Format5_t const* src)
{
  assert(src != NULL);

  e2sm_rc_ind_msg_frmt_5_t dst = {0}; 

  // List of RAN parameters requested
  // [0-65535]
  assert(src->ranP_Requested_List.list.count < 65536);
 
  if(src->ranP_Requested_List.list.count > 0){
    dst.sz_seq_ran_param = src->ranP_Requested_List.list.count;
    dst.seq_ran_param = calloc(dst.sz_seq_ran_param, sizeof(seq_ran_param_t) ); 
    assert(dst.seq_ran_param != NULL && "Memory exhausted" );
  }

  for(size_t i = 0; i < dst.sz_seq_ran_param; ++i){
    dst.seq_ran_param[i] = dec_ind_msg_frmt_5_it(src->ranP_Requested_List.list.array[i]);
  }

  return dst;
}

static
ran_param_req_t dec_ran_param_req(E2SM_RC_IndicationMessage_Format6_RANP_Item_t const* src)
{
  assert(src != NULL);

  ran_param_req_t dst = {0}; 

  // RAN Parameter ID
  // Mandatory
  // 9.3.8
  // 1 4294967295,
  assert(src->ranParameter_ID > 0 && src->ranParameter_ID <  4294967296);
  dst.ran_param_id = src->ranParameter_ID;

  // RAN Parameter Value Type
  // Mandatory
  // 9.3.11
  dst.ran_param = cp_ran_param_value_type(&src->ranParameter_valueType);

  return dst;
}

static
seq_ins_ind_act_2_t dec_seq_ins_ind_act( E2SM_RC_IndicationMessage_Format6_Indication_Item_t const* src)
{
  assert(src != NULL);

  seq_ins_ind_act_2_t dst = {0}; 

  //  Insert Indication ID
  //  Mandatory
  //  9.3.16
  //  1.. 65535
  assert(src->ric_InsertIndication_ID > 0 && src->ric_InsertIndication_ID < 65536);
  dst.ins_ind_id = src->ric_InsertIndication_ID;

  // List of RAN parameters requested
  // [0-65535]
  if(src->ranP_InsertIndication_List.list.count > 0){
    dst.sz_ran_param_req = src->ranP_InsertIndication_List.list.count;
    dst.ran_param_req = calloc(dst.sz_ran_param_req , sizeof(ran_param_req_t));
    assert(dst.ran_param_req != NULL && "memory exhausted");
  }

  for(size_t i = 0; i < dst.sz_ran_param_req; ++i){
    dst.ran_param_req[i] = dec_ran_param_req(src->ranP_InsertIndication_List.list.array[i]);    
  }

  return dst;
}


static
seq_ins_style_2_t dec_seq_ins_style(E2SM_RC_IndicationMessage_Format6_Style_Item_t const* src)
{
  assert(src != NULL);

  seq_ins_style_2_t dst = {0}; 

  // Indicated Insert Style
  // Mandatory
  // 9.3.3
  // 6.2.2.2.
  // INTEGER
  dst.ind_ins_style = src->indicated_Insert_Style_Type;

  // Sequence of Insert Indication Actions
  // [1-63]
  assert(src->ric_InsertIndication_List.list.count > 0 && src->ric_InsertIndication_List.list.count < 64);
  
  dst.sz_seq_ins_ind_act_2 = src->ric_InsertIndication_List.list.count;
  dst.seq_ins_ind_act = calloc(dst.sz_seq_ins_ind_act_2, sizeof(seq_ins_ind_act_2_t));
  assert(dst.seq_ins_ind_act != NULL && "Memory exhausted" );

  for(size_t i = 0; i < dst.sz_seq_ins_ind_act_2; ++i){
    dst.seq_ins_ind_act[i] = dec_seq_ins_ind_act(src->ric_InsertIndication_List.list.array[i]);
  }

  return dst;
}

static
e2sm_rc_ind_msg_frmt_6_t dec_ind_msg_frmt_6(E2SM_RC_IndicationMessage_Format6_t const* src)
{
  assert(src != NULL);

  e2sm_rc_ind_msg_frmt_6_t dst = {0}; 

  // Sequence of Insert Styles for Multiple Actions
  // [1-63]
  assert(src->ric_InsertStyle_List.list.count > 0 && src->ric_InsertStyle_List.list.count < 64);
  
  dst.sz_seq_ins_style_ind_msg = src->ric_InsertStyle_List.list.count; 

  dst.seq_ins_style = calloc(dst.sz_seq_ins_style_ind_msg, sizeof(seq_ins_style_2_t));
  assert(dst.seq_ins_style != NULL && "Memory exhausted");

  for(size_t i = 0; i <dst.sz_seq_ins_style_ind_msg; ++i){
    dst.seq_ins_style[i] = dec_seq_ins_style(src->ric_InsertStyle_List.list.array[i]);
  }

  return dst;
}


e2sm_rc_ind_msg_t rc_dec_ind_msg_asn(size_t len, uint8_t const ind_msg[len])
{
  assert(ind_msg != NULL);
  assert(len != 0);

  E2SM_RC_IndicationMessage_t src = {0};
  defer({  ASN_STRUCT_RESET(asn_DEF_E2SM_RC_IndicationMessage, &src); });
  E2SM_RC_IndicationMessage_t* src_ref = &src;

  asn_dec_rval_t const ret = aper_decode(NULL, &asn_DEF_E2SM_RC_IndicationMessage, (void **)&src_ref, ind_msg, len, 0, 0);
  assert(ret.code == RC_OK);

  //  xer_fprint(stdout, &asn_DEF_E2SM_RC_EventTrigger, &src);
  //  fflush(stdout);

  e2sm_rc_ind_msg_t dst = {0}; 

  if(src.ric_indicationMessage_formats.present == E2SM_RC_IndicationMessage__ric_indicationMessage_formats_PR_indicationMessage_Format1){
    dst.format = FORMAT_1_E2SM_RC_IND_MSG ;
    dst.frmt_1 = dec_ind_msg_frmt_1(src.ric_indicationMessage_formats.choice.indicationMessage_Format1);
  } else if(src.ric_indicationMessage_formats.present == E2SM_RC_IndicationMessage__ric_indicationMessage_formats_PR_indicationMessage_Format2){
    dst.format = FORMAT_2_E2SM_RC_IND_MSG ;
    dst.frmt_2 = dec_ind_msg_frmt_2(src.ric_indicationMessage_formats.choice.indicationMessage_Format2);
  } else if(src.ric_indicationMessage_formats.present == E2SM_RC_IndicationMessage__ric_indicationMessage_formats_PR_indicationMessage_Format3){
    dst.format = FORMAT_3_E2SM_RC_IND_MSG ;
    dst.frmt_3 = dec_ind_msg_frmt_3(src.ric_indicationMessage_formats.choice.indicationMessage_Format3);
  } else if(src.ric_indicationMessage_formats.present == E2SM_RC_IndicationMessage__ric_indicationMessage_formats_PR_indicationMessage_Format4){
    dst.format = FORMAT_4_E2SM_RC_IND_MSG ;
    dst.frmt_4 = dec_ind_msg_frmt_4(src.ric_indicationMessage_formats.choice.indicationMessage_Format4);
  } else if(src.ric_indicationMessage_formats.present == E2SM_RC_IndicationMessage__ric_indicationMessage_formats_PR_indicationMessage_Format5){
    dst.format = FORMAT_5_E2SM_RC_IND_MSG ;
    dst.frmt_5 = dec_ind_msg_frmt_5(src.ric_indicationMessage_formats.choice.indicationMessage_Format5);
  } else if(src.ric_indicationMessage_formats.present == E2SM_RC_IndicationMessage__ric_indicationMessage_formats_PR_indicationMessage_Format6){
    dst.format = FORMAT_6_E2SM_RC_IND_MSG ;
    dst.frmt_6 = dec_ind_msg_frmt_6(src.ric_indicationMessage_formats.choice.indicationMessage_Format6);
  } else {
    assert(0!=0 && "Unknown format type");
  }

  return dst;
}

e2sm_rc_cpid_t rc_dec_cpid_asn(size_t len, uint8_t const call_proc_id[len])
{
  assert(call_proc_id != NULL);

  E2SM_RC_CallProcessID_t src = {0};
  defer({  ASN_STRUCT_RESET(asn_DEF_E2SM_RC_CallProcessID, &src); });
  E2SM_RC_CallProcessID_t* src_ref = &src;

  asn_dec_rval_t const ret = aper_decode(NULL, &asn_DEF_E2SM_RC_CallProcessID, (void **)&src_ref, call_proc_id, len, 0, 0);
  assert(ret.code == RC_OK);

  //  xer_fprint(stdout, &asn_DEF_E2SM_RC_EventTrigger, &src);
  //  fflush(stdout);

  e2sm_rc_cpid_t dst = {0}; 

  // RIC Call Process ID
  // Mandatory
  // 9.3.18
  // [ 1 - 4294967295]
  assert(src.ric_callProcessID_formats.present == E2SM_RC_CallProcessID__ric_callProcessID_formats_PR_callProcessID_Format1);
  assert(src.ric_callProcessID_formats.choice.callProcessID_Format1->ric_callProcess_ID > 0 && src.ric_callProcessID_formats.choice.callProcessID_Format1->ric_callProcess_ID < 4294967296);

  dst.ric_cpid = src.ric_callProcessID_formats.choice.callProcessID_Format1->ric_callProcess_ID;

  return dst;
}

static
e2sm_rc_ctrl_hdr_frmt_1_t dec_ctrl_hdr_frmt_1(E2SM_RC_ControlHeader_Format1_t const* src)
{
  assert(src != NULL);
  e2sm_rc_ctrl_hdr_frmt_1_t dst = {0};  

  // UE ID
  // Mandatory
  // 9.3.10
  dst.ue_id = dec_ue_id_asn(&src->ueID);

  // RIC Style Type
  // Mandatory
  // 9.3.3
  // 6.2.2.2. 
  // INTEGER
  dst.ric_style_type = src->ric_Style_Type;

  // Control Action ID
  // Mandatory
  // 9.3.6
  // [1- 65535]
  assert(src->ric_ControlAction_ID > 0 && src->ric_ControlAction_ID < 65536);
  dst.ctrl_act_id = src->ric_ControlAction_ID;

  // RIC Control decision
  // Optional
  assert(src->ric_ControlDecision == NULL && "Not implemented");

 return dst;
}

static
e2sm_rc_ctrl_hdr_frmt_2_t dec_ctrl_hdr_frmt_2(E2SM_RC_ControlHeader_Format2_t const* src)
{
  e2sm_rc_ctrl_hdr_frmt_2_t dst = {0}; 
 // UE ID
 // Optional
 // 9.3.10
  if(src->ueID != NULL){
    dst.ue_id = calloc(1, sizeof(ue_id_e2sm_t));
    assert(dst.ue_id != NULL && "Memory exhausted");

    *dst.ue_id = dec_ue_id_asn(src->ueID);
  }

  // RIC Control decision
  // Optional
  assert(src->ric_ControlDecision == NULL && "Not implemented");

  return dst;
}

e2sm_rc_ctrl_hdr_t rc_dec_ctrl_hdr_asn(size_t len, uint8_t const ctrl_hdr[len])
{
  assert(ctrl_hdr != NULL);

  E2SM_RC_ControlHeader_t src = {0};
  defer({  ASN_STRUCT_RESET(asn_DEF_E2SM_RC_ControlHeader, &src); });
  E2SM_RC_ControlHeader_t* src_ref = &src;

  asn_dec_rval_t const ret = aper_decode(NULL, & asn_DEF_E2SM_RC_ControlHeader, (void **)&src_ref, ctrl_hdr, len, 0, 0);
  assert(ret.code == RC_OK);

  //  xer_fprint(stdout, &asn_DEF_E2SM_RC_EventTrigger, &src);
  //  fflush(stdout);

  e2sm_rc_ctrl_hdr_t dst = {0}; 

  if(src.ric_controlHeader_formats.present == E2SM_RC_ControlHeader__ric_controlHeader_formats_PR_controlHeader_Format1){
    dst.format = FORMAT_1_E2SM_RC_CTRL_HDR;
    dst.frmt_1 = dec_ctrl_hdr_frmt_1(src.ric_controlHeader_formats.choice.controlHeader_Format1);
  } else if(src.ric_controlHeader_formats.present == E2SM_RC_ControlHeader__ric_controlHeader_formats_PR_controlHeader_Format2){
    dst.format = FORMAT_2_E2SM_RC_CTRL_HDR;
    dst.frmt_2 = dec_ctrl_hdr_frmt_2(src.ric_controlHeader_formats.choice.controlHeader_Format2);
  } else {
    assert(0!=0 && "Unknown format type");
  }

  return dst;
}

static
seq_ran_param_t dec_ctrl_msg_frmt_1_it(E2SM_RC_ControlMessage_Format1_Item_t const* src)
{
  assert(src != NULL);

  seq_ran_param_t dst = {0}; 
  //RAN Parameter ID
  //Mandatory
  //9.3.8
  // [1 - 4294967295]
  assert(src->ranParameter_ID > 0 && src->ranParameter_ID <  4294967296);
  dst.ran_param_id = src->ranParameter_ID;

  // RAN Parameter Value Type
  // 9.3.11
  // Mandatory
  dst.ran_param_val = cp_ran_param_value_type(&src->ranParameter_valueType);

  return dst;
}


static
e2sm_rc_ctrl_msg_frmt_1_t dec_ctrl_msg_frmt_1(E2SM_RC_ControlMessage_Format1_t const* src)
{
  assert(src != NULL);

  e2sm_rc_ctrl_msg_frmt_1_t dst = {0}; 

  // List of RAN parameters
  // [0- 65535]
  assert(src->ranP_List.list.count <  65536);

  if(src->ranP_List.list.count > 0){
    dst.sz_ran_param = src->ranP_List.list.count;

    dst.ran_param = calloc(dst.sz_ran_param, sizeof(seq_ran_param_t));
    assert(dst.ran_param != NULL && "Memory exhausted");
  }

  for(size_t i = 0;i < dst.sz_ran_param; ++i){
    dst.ran_param[i] = dec_ctrl_msg_frmt_1_it(src->ranP_List.list.array[i]);
  }

  return dst;
}

static
seq_ctrl_act_t dec_ctrl_msg_seq_ctrl_act(E2SM_RC_ControlMessage_Format2_ControlAction_Item_t const* src)
{
  assert(src != NULL);

  seq_ctrl_act_t dst = {0}; 

  //Control Action ID
  //Mandatory
  //9.3.6
  // [1 - 65535]
  assert(src->ric_ControlAction_ID > 0 && src->ric_ControlAction_ID < 65536);
  dst.ctrl_act_id = src->ric_ControlAction_ID;

  // Control Action Parameters
  // BUG, BUG, BUG in the standard 
  // Optional in english. Mandatory in ASN. 
  // 9.2.1.7.1 E2SM-RC Control Message Format 1
  dst.ctrl_msg_frmt_1 = calloc(1, sizeof( e2sm_rc_ctrl_msg_frmt_1_t));
  assert(dst.ctrl_msg_frmt_1 != NULL && "Memory exhausted" );

  *dst.ctrl_msg_frmt_1 = dec_ctrl_msg_frmt_1(&src->ranP_List); 

  return dst;
}

static
seq_ctrl_sma_t dec_ctrl_msg_seq_ctrl_sma(E2SM_RC_ControlMessage_Format2_Style_Item_t const* src)
{
  assert(src != NULL);

  seq_ctrl_sma_t dst = {0}; 

  // Indicated Control Style
  // Mandatory
  // 9.3.3
  // 6.2.2.2.
  // INTEGER
  dst.ctrl_style = src->indicated_Control_Style_Type;

  // Sequence of Control Actions
  // [1-63]
  assert(src->ric_ControlAction_List.list.count > 0 && src->ric_ControlAction_List.list.count < 64);

  dst.sz_seq_ctrl_act = src->ric_ControlAction_List.list.count;

  dst.seq_ctrl_act = calloc(dst.sz_seq_ctrl_act, sizeof(seq_ctrl_act_t));
  assert(dst.seq_ctrl_act != NULL && "Memory exhausted" );
  
  for(size_t i = 0; i < dst.sz_seq_ctrl_act; ++i){
    dst.seq_ctrl_act[i] = dec_ctrl_msg_seq_ctrl_act( src->ric_ControlAction_List.list.array[i]);
  }

  return dst;
}


static
e2sm_rc_ctrl_msg_frmt_2_t dec_ctrl_msg_frmt_2(E2SM_RC_ControlMessage_Format2_t const* src)
{
  assert(src != NULL);

  e2sm_rc_ctrl_msg_frmt_2_t dst = {0}; 

  // Sequence of Control Styles
  // for Multiple Actions
  // [1 - 63]  
  assert(src->ric_ControlStyle_List.list.count > 0 && src->ric_ControlStyle_List.list.count < 64);
  
  dst.sz_seq_ctrl_sma = src->ric_ControlStyle_List.list.count;
  dst.action = calloc(dst.sz_seq_ctrl_sma, sizeof(seq_ctrl_sma_t));
  assert(dst.action != NULL && "Memory exhausted");
  
  for(size_t i = 0; i < dst.sz_seq_ctrl_sma; ++i){
    dst.action[i] = dec_ctrl_msg_seq_ctrl_sma(src->ric_ControlStyle_List.list.array[i]);
  }

  return dst;
}

e2sm_rc_ctrl_msg_t rc_dec_ctrl_msg_asn(size_t len, uint8_t const ctrl_msg[len])
{
  assert(ctrl_msg != NULL);
  assert(len > 0);

  E2SM_RC_ControlMessage_t src = {0};
  defer({  ASN_STRUCT_RESET(asn_DEF_E2SM_RC_ControlMessage, &src); });
  E2SM_RC_ControlMessage_t* src_ref = &src;

  asn_dec_rval_t const ret = aper_decode(NULL, & asn_DEF_E2SM_RC_ControlMessage, (void **)&src_ref, ctrl_msg, len, 0, 0);
  assert(ret.code == RC_OK);

  //  xer_fprint(stdout, &asn_DEF_E2SM_RC_ControlMessage, &src);
  //  fflush(stdout);

  e2sm_rc_ctrl_msg_t dst = {0}; 

  if(src.ric_controlMessage_formats.present == E2SM_RC_ControlMessage__ric_controlMessage_formats_PR_controlMessage_Format1){
    dst.format = FORMAT_1_E2SM_RC_CTRL_MSG;
    dst.frmt_1 = dec_ctrl_msg_frmt_1(src.ric_controlMessage_formats.choice.controlMessage_Format1);
  } else if(src.ric_controlMessage_formats.present == E2SM_RC_ControlMessage__ric_controlMessage_formats_PR_controlMessage_Format2){
    dst.format = FORMAT_2_E2SM_RC_CTRL_MSG;
    dst.frmt_2 = dec_ctrl_msg_frmt_2(src.ric_controlMessage_formats.choice.controlMessage_Format2);
  } else {
    assert(0 && "Unknown format");
  }

  return dst;
}

static
seq_ran_param_2_t dec_ctrl_out_frmt_1_it(E2SM_RC_ControlOutcome_Format1_Item_t const* src)
{
  assert(src != NULL);

  seq_ran_param_2_t dst = {0};
  // RAN Parameter ID
  // Mandatory
  // 9.3.8
  // [1 - 4294967295]
  assert(src->ranParameter_ID > 0);
  dst.ran_param_id = src->ranParameter_ID;

  // RAN Parameter Value
  // Mandatory
  // 9.3.14
  dst.ran_param_value = cp_ran_param_val(&src->ranParameter_value);

  return dst;
}


static
e2sm_rc_ctrl_out_frmt_1_t dec_ctrl_out_frmt_1(E2SM_RC_ControlOutcome_Format1_t const* src)
{
  assert(src != NULL);

  e2sm_rc_ctrl_out_frmt_1_t dst = {0}; 

  // Sequence of RAN
  // Parameters
  // [0 - 255]
  assert(src->ranP_List.list.count < 256);

  if(src->ranP_List.list.count > 0){
    dst.sz_seq_ran_param_2 = src->ranP_List.list.count;
    dst.ran_param = calloc(dst.sz_seq_ran_param_2, sizeof(seq_ran_param_2_t ));
    assert(dst.ran_param != NULL && "Memory exhausted");
  }

  for(size_t i = 0; i < dst.sz_seq_ran_param_2; ++i){
    dst.ran_param[i] = dec_ctrl_out_frmt_1_it(src->ranP_List.list.array[i]);
  }

  return dst;
}

static
seq_ran_param_2_t dec_ctrl_out_frmt_2_ran_it(E2SM_RC_ControlOutcome_Format2_RANP_Item_t const* src) 
{
  assert(src != NULL);

  seq_ran_param_2_t dst = {0}; 

  // RAN Parameter ID
  // Mandatory
  // 9.3.8
  // [1 - 4294967295]
  assert(src->ranParameter_ID > 0 && src->ranParameter_ID < 4294967296);
  dst.ran_param_id = src->ranParameter_ID;

  // RAN Parameter Value
  // Mandatory
  // 9.3.14
  dst.ran_param_value = cp_ran_param_val(&src->ranParameter_value);

  return dst;
}

static
seq_ctrl_act_out_t dec_ctrl_out_frmt_2_ctrl_out_it(E2SM_RC_ControlOutcome_Format2_ControlOutcome_Item_t const* src)
{
  assert(src != NULL);

  seq_ctrl_act_out_t dst = {0}; 

  // Control Action ID
  // Mandatory
  // 9.3.6
  // [1- 65535]
  assert(src->ric_ControlAction_ID > 0 && src->ric_ControlAction_ID < 65536);
  dst.ctrl_act_id = src->ric_ControlAction_ID;

  //Sequence of RAN
  //Parameters
  // [1-255]  
  assert(src->ranP_List.list.count > 0 && src->ranP_List.list.count < 256); 

  dst.sz_ran_param = src->ranP_List.list.count;
  dst.ran_param = calloc(dst.sz_ran_param , sizeof(seq_ran_param_2_t));
  assert(dst.ran_param != NULL && "memory exhausted");

  for(size_t i = 0; i < dst.sz_ran_param; ++i){
    dst.ran_param[i] = dec_ctrl_out_frmt_2_ran_it(src->ranP_List.list.array[i]);
  }

  return dst;
}


static
seq_ctrl_sty_mul_out_t dec_ctrl_out_frmt_2_sty_it(E2SM_RC_ControlOutcome_Format2_Style_Item_t const* src)
{
  assert(src != NULL);
  seq_ctrl_sty_mul_out_t dst = {0}; 

  // Indicated Control Style
  // Mandatory
  // 9.3.3
  //  6.2.2.2.
  dst.ind_ctrl_style = src->indicated_Control_Style_Type; 

  //Sequence of Control
  //Actions Outcom
  // [1-63]
  assert(src->ric_ControlOutcome_List.list.count > 0 && src->ric_ControlOutcome_List.list.count < 64);
  dst.sz_seq_ctrl_act_out = src->ric_ControlOutcome_List.list.count;

  dst.seq_ctrl_act_out = calloc(dst.sz_seq_ctrl_act_out , sizeof(seq_ctrl_act_out_t));
  assert(dst.seq_ctrl_act_out != NULL && "Memory exhausted");

  for(size_t i = 0; i < dst.sz_seq_ctrl_act_out; ++i){
    dst.seq_ctrl_act_out[i] = dec_ctrl_out_frmt_2_ctrl_out_it(src->ric_ControlOutcome_List.list.array[i]);
  }

  return dst;
}


static
e2sm_rc_ctrl_out_frmt_2_t dec_ctrl_out_frmt_2(E2SM_RC_ControlOutcome_Format2_t const* src)
{
  assert(src != NULL);

  e2sm_rc_ctrl_out_frmt_2_t dst = {0}; 

// Sequence of Control Styles
// for Multiple Outcomes
// [1-63]
  assert(src->ric_ControlStyle_List.list.count > 0 && src->ric_ControlStyle_List.list.count < 64);

  dst.sz_seq_ctrl_sty_mul_out = src->ric_ControlStyle_List.list.count;

  dst.seq_ctrl_sty_mul_out = calloc(dst.sz_seq_ctrl_sty_mul_out, sizeof(seq_ctrl_sty_mul_out_t));
  assert(dst.seq_ctrl_sty_mul_out != NULL && "Memory exhausted" );

  for(size_t i = 0; i < dst.sz_seq_ctrl_sty_mul_out; ++i){
    dst.seq_ctrl_sty_mul_out[i] = dec_ctrl_out_frmt_2_sty_it(src->ric_ControlStyle_List.list.array[i]);
  }

  return dst;
}

static
seq_ran_param_t dec_ctr_out_frmt_3_it(E2SM_RC_ControlOutcome_Format3_Item_t const* src)
{
  assert(src != NULL);

  seq_ran_param_t dst = {0}; 

  //RAN Parameter ID
  //Mandatory
  //9.3.8
  // [1 - 4294967295]
  assert(src->ranParameter_ID > 0);
  dst.ran_param_id = src->ranParameter_ID; 

  // RAN Parameter Value Type
  // 9.3.11
  // Mandatory
  dst.ran_param_val = cp_ran_param_value_type(&src->ranParameter_valueType);

  return dst;
}

static
e2sm_rc_ctrl_out_frmt_3_t dec_ctrl_out_frmt_3(E2SM_RC_ControlOutcome_Format3_t const* src)
{
  assert(src != NULL);

  e2sm_rc_ctrl_out_frmt_3_t dst = {0}; 

  //  Sequence of RAN Parameters
  //  [0-255]
  assert(src->ranP_List.list.count < 256);

  if(src->ranP_List.list.count > 0){
    dst.sz_seq_ran_param = src->ranP_List.list.count;
    dst.ran_param = calloc(dst.sz_seq_ran_param , sizeof(seq_ran_param_t));
    assert(dst.ran_param != NULL && "Memory exhausted");
  }

  for(size_t i = 0; i < dst.sz_seq_ran_param; ++i){
    dst.ran_param[i] = dec_ctr_out_frmt_3_it(src->ranP_List.list.array[i]); 
  }

  return dst;
}


e2sm_rc_ctrl_out_t rc_dec_ctrl_out_asn(size_t len, uint8_t const ctrl_out[len]) 
{
  assert(ctrl_out != NULL);
  assert(len > 0);

  E2SM_RC_ControlOutcome_t src = {0};
  defer({  ASN_STRUCT_RESET(asn_DEF_E2SM_RC_ControlOutcome, &src); });
  E2SM_RC_ControlOutcome_t* src_ref = &src;

  asn_dec_rval_t const ret = aper_decode(NULL, &asn_DEF_E2SM_RC_ControlOutcome, (void **)&src_ref, ctrl_out, len, 0, 0);
  assert(ret.code == RC_OK);

  //  xer_fprint(stdout, &asn_DEF_E2SM_RC_ControlMessage, &src);
  //  fflush(stdout);

  e2sm_rc_ctrl_out_t dst = {0}; 

  if(src.ric_controlOutcome_formats.present == E2SM_RC_ControlOutcome__ric_controlOutcome_formats_PR_controlOutcome_Format1){
    dst.format = FORMAT_1_E2SM_RC_CTRL_OUT;
    dst.frmt_1 = dec_ctrl_out_frmt_1(src.ric_controlOutcome_formats.choice.controlOutcome_Format1);
  } else if(src.ric_controlOutcome_formats.present == E2SM_RC_ControlOutcome__ric_controlOutcome_formats_PR_controlOutcome_Format2){
    dst.format = FORMAT_2_E2SM_RC_CTRL_OUT; 
    dst.frmt_2 = dec_ctrl_out_frmt_2(src.ric_controlOutcome_formats.choice.controlOutcome_Format2);
  } else if(src.ric_controlOutcome_formats.present == E2SM_RC_ControlOutcome__ric_controlOutcome_formats_PR_controlOutcome_Format3){
    dst.format = FORMAT_3_E2SM_RC_CTRL_OUT; 
    dst.frmt_3 = dec_ctrl_out_frmt_3(src.ric_controlOutcome_formats.choice.controlOutcome_Format3);
  } else {
    assert(0!=0 && "Unknown format");
  }

  return dst;
}

rc_func_def_t rc_dec_func_def_asn(size_t len, uint8_t const func_def[len])
{
  assert(0!=0 && "Not implemented");
  assert(func_def != NULL);
 rc_func_def_t  avoid_warning;
  return avoid_warning;
}

