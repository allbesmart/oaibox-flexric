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


#include "../ie/asn/E2SM-RC-ActionDefinition.h"
#include "../ie/asn/E2SM-RC-ActionDefinition-Format1.h"
#include "../ie/asn/E2SM-RC-ActionDefinition-Format1-Item.h"




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
ran_param_list_t cp_lst(RANParameter_Testing_Item_Choice_List_t const* src)
{
  assert(src != NULL);

  ran_param_list_t dst = {0}; 

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
ran_param_struct_t cp_strct(RANParameter_Testing_Item_Choice_Structure_t const* src)
{
  assert(src != NULL);

  ran_param_struct_t dst = {0}; 

  // [1-65535]
  assert(src->ranParameter_Structure->list.count > 0 && src->ranParameter_Structure->list.count < 65535 + 1); 
  dst.sz_ran_param_struct = src->ranParameter_Structure->list.count; 

  dst.ran_param_struct = calloc(dst.sz_ran_param_struct, sizeof(ran_param_test_t));
  assert(dst.ran_param_struct != NULL && "Memory exhausted");

  for(size_t i = 0; i <  dst.sz_ran_param_struct; ++i){
    dst.ran_param_struct[i] = cp_ran_param_test(src->ranParameter_Structure->list.array[i]);
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
ran_param_elm_key_true_t cp_key_flag_true(RANParameter_Testing_Item_Choice_ElementTrue_t const* src)
{
  assert(src != NULL);
  
  ran_param_elm_key_true_t dst = {0}; 

  dst.value = cp_ran_param_val(&src->ranParameter_value);

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
    dst.format = FORMAT_1_E2SM_RC_ACT_DEF ;
    dst.frmt_1 =  cp_act_def_frmt_1(src.ric_actionDefinition_formats.choice.actionDefinition_Format1) ;

  } else if(src.ric_actionDefinition_formats.present ==  E2SM_RC_ActionDefinition__ric_actionDefinition_formats_PR_actionDefinition_Format2){
    dst.format = FORMAT_2_E2SM_RC_ACT_DEF ;
    assert(0!=0 && "Not implemented");
  }else if(src.ric_actionDefinition_formats.present == E2SM_RC_ActionDefinition__ric_actionDefinition_formats_PR_actionDefinition_Format3 ){
    dst.format = FORMAT_3_E2SM_RC_ACT_DEF ;
    assert(0!=0 && "Not implemented");
  } else if(src.ric_actionDefinition_formats.present == E2SM_RC_ActionDefinition__ric_actionDefinition_formats_PR_actionDefinition_Format4 ){
    dst.format = FORMAT_4_E2SM_RC_ACT_DEF ;
    assert(0!=0 && "Not implemented");
  } else {
    assert(0!=0 && "Unknown type");
  }

  return dst;
}

rc_ind_hdr_t rc_dec_ind_hdr_asn(size_t len, uint8_t const ind_hdr[len])
{
  assert(0!=0 && "Not implemented");
  assert(ind_hdr != NULL);
  rc_ind_hdr_t avoid_warning;
  return avoid_warning;
}

rc_ind_msg_t rc_dec_ind_msg_asn(size_t len, uint8_t const ind_msg[len])
{
  assert(0!=0 && "Not implemented");
  assert(ind_msg != NULL);
  rc_ind_msg_t avoid_warning;
  return avoid_warning;
}

rc_call_proc_id_t rc_dec_call_proc_id_asn(size_t len, uint8_t const call_proc_id[len])
{
  assert(0!=0 && "Not implemented");
  assert(call_proc_id != NULL);
  rc_call_proc_id_t avoid_warning;
  return avoid_warning;
}

rc_ctrl_hdr_t rc_dec_ctrl_hdr_asn(size_t len, uint8_t const ctrl_hdr[len])
{
  assert(0!=0 && "Not implemented");
  assert(ctrl_hdr != NULL);
  rc_ctrl_hdr_t avoid_warning;
  return avoid_warning;
}

rc_ctrl_msg_t rc_dec_ctrl_msg_asn(size_t len, uint8_t const ctrl_msg[len])
{
  assert(0!=0 && "Not implemented");
  assert(ctrl_msg != NULL);
  rc_ctrl_msg_t  avoid_warning;
  return avoid_warning;
}

rc_ctrl_out_t rc_dec_ctrl_out_asn(size_t len, uint8_t const ctrl_out[len]) 
{
  assert(0!=0 && "Not implemented");
  assert( ctrl_out != NULL);
 rc_ctrl_out_t avoid_warning;
  return avoid_warning;
}

rc_func_def_t rc_dec_func_def_asn(size_t len, uint8_t const func_def[len])
{
  assert(0!=0 && "Not implemented");
  assert(func_def != NULL);
 rc_func_def_t  avoid_warning;
  return avoid_warning;
}

