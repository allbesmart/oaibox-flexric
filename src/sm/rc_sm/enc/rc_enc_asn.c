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

#include "../ie/asn/E2SM-RC-EventTrigger.h"
#include "../ie/asn/E2SM-RC-ActionDefinition.h"

#include "../ie/asn/E2SM-RC-EventTrigger-Format1.h"
#include "../ie/asn/E2SM-RC-EventTrigger-Format2.h"
#include "../ie/asn/E2SM-RC-EventTrigger-Format3.h"
#include "../ie/asn/E2SM-RC-EventTrigger-Format4.h"
#include "../ie/asn/E2SM-RC-EventTrigger-Format5.h"

#include "../ie/asn/E2SM-RC-EventTrigger-Format1-Item.h"
#include "../ie/asn/E2SM-RC-EventTrigger-Format3-Item.h"
#include "../ie/asn/E2SM-RC-EventTrigger-Format4-Item.h"

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

#include "../ie/ir/ran_param_struct.h"
#include "../ie/ir/ran_param_list.h"

//#include "../ie/asn/E2SM-RC-ActionDefinition-Format4.h"
//#include "../ie/asn/E2SM-RC-ActionDefinition-Format4-Item.h"


#include "../ie/asn/MessageType-Choice-NI.h"
#include "../ie/asn/MessageType-Choice-RRC.h"

#include "../ie/asn/TriggerType-Choice-UEID.h"
#include "../ie/asn/TriggerType-Choice-RRCstate.h"
#include "../ie/asn/TriggerType-Choice-RRCstate-Item.h"
#include "../ie/asn/TriggerType-Choice-L2state.h"
#include "../ie/asn/RANParameter-Testing-Item.h"
#include "../ie/asn/RANParameter-Testing-Item-Choice-List.h"
#include "../ie/asn/RANParameter-Testing-LIST.h"
#include "../ie/asn/RANParameter-Testing-Item-Choice-Structure.h"
#include "../ie/asn/RANParameter-Testing-STRUCTURE.h"
#include "../ie/asn/RANParameter-Testing-Item-Choice-ElementTrue.h"
#include "../ie/asn/RANParameter-Testing-Item-Choice-ElementFalse.h"
#include "../ie/ir/ran_parameter_test_condition.h"
#include "../ie/asn/RIC-PolicyAction-RANParameter-Item.h"

#include "../ie/asn/RANParameter-Testing-Item.h"

#include "../ie/asn/RANParameter-Testing-STRUCTURE.h"

#include "../ie/asn/RANParameter-ValueType-Choice-Structure.h"
#include "../ie/asn/RANParameter-STRUCTURE.h"
#include "../ie/asn/RANParameter-ValueType-Choice-ElementTrue.h"
#include "../ie/asn/RANParameter-ValueType-Choice-ElementFalse.h"
#include "../ie/asn/RANParameter-ValueType-Choice-Structure.h"
#include "../ie/asn/RANParameter-STRUCTURE-Item.h"
#include "../ie/asn/RANParameter-Testing-Item-Choice-List.h"
#include "../ie/asn/RANParameter-ValueType-Choice-List.h"
#include "../ie/asn/RANParameter-LIST.h"

#include "../ie/asn/E2SM-RC-IndicationHeader.h"
#include "../ie/asn/E2SM-RC-IndicationHeader-Format1.h"
#include "../ie/asn/E2SM-RC-IndicationHeader-Format2.h"
#include "../ie/asn/E2SM-RC-IndicationHeader-Format3.h"


#include "../ie/asn/E2SM-RC-IndicationMessage.h"
#include "../ie/asn/E2SM-RC-IndicationMessage-Format1.h"
#include "../ie/asn/E2SM-RC-IndicationMessage-Format2.h"
#include "../ie/asn/E2SM-RC-IndicationMessage-Format3.h"
#include "../ie/asn/E2SM-RC-IndicationMessage-Format4.h"
#include "../ie/asn/E2SM-RC-IndicationMessage-Format5.h"
#include "../ie/asn/E2SM-RC-IndicationMessage-Format6.h"

#include "../ie/asn/E2SM-RC-IndicationMessage-Format1-Item.h"



#include "../../../lib/sm/enc_asn_sm_common/enc_ue_id.h"


#include "rc_enc_asn.h"

#include "../../../util/alg_ds/alg/defer.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

static inline
OCTET_STRING_t copy_ba_to_ostring(byte_array_t ba)
{
  OCTET_STRING_t os = { .size = ba.len }; 
  os.buf = malloc(ba.len);
  memcpy(os.buf, ba.buf, ba.len);
  return os;
}
static inline
BIT_STRING_t copy_ba_to_bit_string(byte_array_t ba)
{
  BIT_STRING_t bs = {0};
  
  bs.buf = calloc (ba.len, sizeof(uint8_t ) );
  memcpy(bs.buf, ba.buf, ba.len);
  bs.size = ba.len;
  bs.bits_unused = 0; // FixME

  return bs;
}



static
MessageType_Choice_NI_t* cp_msg_type_ni(network_interface_e2rc_t const* src)
{
  assert(src != NULL);

  MessageType_Choice_NI_t* dst = calloc(1, sizeof(MessageType_Choice_NI_t)); 
  assert(dst != NULL);

  // NI Type
  // Mandatory
  // 9.3.32
  if(src->ni_type == NG_NETWORK_INTERFACE_TYPE ){
    dst->nI_Type = InterfaceType_nG	;
  } else if (src->ni_type == XN_NETWORK_INTERFACE_TYPE){
    dst->nI_Type = InterfaceType_xn	;
  }else if (src->ni_type == F1_NETWORK_INTERFACE_TYPE){
    dst->nI_Type = InterfaceType_f1;
  }else if (src->ni_type == E1_NETWORK_INTERFACE_TYPE){
    dst->nI_Type = InterfaceType_e1;
  }else if (src->ni_type == S1_NETWORK_INTERFACE_TYPE){
    dst->nI_Type = InterfaceType_s1;	
  }else if (src->ni_type == X2_NETWORK_INTERFACE_TYPE  ){
    dst->nI_Type = InterfaceType_x2;	
  }else if (src->ni_type ==W1_NETWORK_INTERFACE_TYPE ){
    dst->nI_Type = InterfaceType_w1;	
  } else {
    assert(0 != 0 && "Unknown type"); 
  }

  // NI Identifier
  // Optional
  // 9.3.33
  assert(src->ni_id == NULL && "Not implemented");

  // NI Message
  // Optional
  // 9.3.34
  assert(src->ni_msg_id == NULL && "Not implemented"); 

  return dst;
}

static
RRCclass_LTE_t cp_rrc_msg_type_lte(lte_rrc_class_e src)
{
  RRCclass_LTE_t dst = {0}; 
    
  if(src == BCCH_BCH_LTE_RRC_CLASS){
    dst = RRCclass_LTE_bCCH_BCH;	
  } else if(src == BCCH_BCH_MBMS_LTE_RRC_CLASS){
    dst = RRCclass_LTE_bCCH_BCH_MBMS	;
  }else if(src == BCCH_DL_SCH_LTE_RRC_CLASS){
    dst = RRCclass_LTE_bCCH_DL_SCH	;
  }else if(src == BCCH_DL_SCH_BR_LTE_RRC_CLASS){
    dst = RRCclass_LTE_bCCH_DL_SCH_BR	;
  }else if(src == BCCH_DL_SCH_MBMS_LTE_RRC_CLASS){
    dst = RRCclass_LTE_bCCH_DL_SCH_MBMS	;
  }else if(src == MCCH_LTE_RRC_CLASS){
    dst = RRCclass_LTE_mCCH	;
  }else if(src == PCCH_LTE_RRC_CLASS){
    dst = RRCclass_LTE_pCCH	;
  }else if(src == DL_CCCH_LTE_RRC_CLASS){
    dst = RRCclass_LTE_dL_CCCH	;
  }else if(src == DL_DCCH_LTE_RRC_CLASS){
    dst = RRCclass_LTE_dL_DCCH	;
  }else if(src == UL_CCCH_LTE_RRC_CLASS){
    dst = RRCclass_LTE_uL_CCCH	;
  }else if(src == UL_DCCH_LTE_RRC_CLASS){
    dst = RRCclass_LTE_uL_DCCH	;
  }else if(src == SC_MCCH_LTE_RRC_CLASS){
    dst = RRCclass_LTE_sC_MCCH	;
  }else {
    assert( 0!=0 && "Unknown type");
  } 

  return dst;
}

static
RRCclass_NR_t	cp_rrc_msg_type_nr(nr_rrc_class_e src)
{
  RRCclass_NR_t dst = {0};

  if(src == BCCH_BCH_NR_RRC_CLASS){
    dst = RRCclass_NR_bCCH_BCH;
  } else if(src == BCCH_DL_SCH_NR_RRC_CLASS){
    dst = RRCclass_NR_bCCH_DL_SCH;
  }else if(src == DL_CCCH_NR_RRC_CLASS){
    dst = RRCclass_NR_dL_CCCH;
  }else if(src == DL_DCCH_NR_RRC_CLASS){
    dst = RRCclass_NR_dL_DCCH	;
  }else if(src == PCCH_NR_RRC_CLASS){

    dst = RRCclass_NR_pCCH	;
  }else if(src == UL_CCCH_NR_RRC_CLASS){

    dst = RRCclass_NR_uL_CCCH	;
  }else if(src == UL_CCCH1_NR_RRC_CLASS){

    dst = RRCclass_NR_uL_CCCH1	;
  }else if(src == UL_DCCH_NR_RRC_CLASS){

    dst = RRCclass_NR_uL_DCCH	;
  }else {
    assert(0!=0 && "Unknown type");
  }

  return dst;
}


static
MessageType_Choice_RRC_t*	cp_msg_type_rrc(rrc_msg_id_t const* src)
{
  assert(src != NULL);

  MessageType_Choice_RRC_t* dst = calloc(1, sizeof(MessageType_Choice_RRC_t));
  assert(dst != NULL && "Memory exhausted");

  // Mandatory
  //rrc_message_id_e type;
  if(src->type == LTE_RRC_MESSAGE_ID){
    dst->rRC_Message.rrcType.present = RRC_MessageID__rrcType_PR_lTE;
    dst->rRC_Message.rrcType.choice.lTE = cp_rrc_msg_type_lte(src->lte) ; 
  } else if(src->type == NR_RRC_MESSAGE_ID){
    dst->rRC_Message.rrcType.present = RRC_MessageID__rrcType_PR_nR;
    dst->rRC_Message.rrcType.choice.nR = cp_rrc_msg_type_nr(src->nr); 
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
  dst->rRC_Message.messageID = src->rrc_msg_id;

  return dst;
}

static
E2SM_RC_EventTrigger_Format1_Item_t* cp_rc_ev_trigger_format_1_it(msg_ev_trg_t const* src)
{
  assert(src != NULL);

  E2SM_RC_EventTrigger_Format1_Item_t* dst = calloc(1, sizeof(E2SM_RC_EventTrigger_Format1_Item_t));
  assert(dst != NULL && "Memory exhausted");
 

  // Event Trigger Condition ID
  // Mandatory
  // 9.3.21
  // [1- 65535]
  assert(src->ev_trigger_cond_id > 0);
  dst->ric_eventTriggerCondition_ID = src->ev_trigger_cond_id;

  // CHOICE Message Type
  // Mandatory
  if(src->msg_type == NETWORK_INTERFACE_MSG_TYPE_EV_TRG){
    dst->messageType.present = MessageType_Choice_PR_messageType_Choice_NI;
    dst->messageType.choice.messageType_Choice_NI = cp_msg_type_ni(&src->net);
  } else if(src->msg_type == RRC_MSG_MSG_TYPE_EV_TRG){
    dst->messageType.present = MessageType_Choice_PR_messageType_Choice_RRC;
    dst->messageType.choice.messageType_Choice_RRC = cp_msg_type_rrc(&src->rrc_msg);
  } else {
    assert(0!=0 && "Unknown type");
  }

  //Message Direction
  //Optional
  assert(src->msg_dir == NULL && "Not implemented");

  //  Associated UE Info
  //  Optional
  //  9.3.26
  assert(src->assoc_ue_info == NULL && "Not implemented");

  // Logical OR
  // Optional
  // 9.3.25
  assert(src->log_or == NULL && "Not implemented");

  return dst;
}


static
E2SM_RC_EventTrigger_Format1_t*	cp_rc_ev_trigger_format_1(e2sm_rc_ev_trg_frmt_1_t const* src)
{
  assert(src != NULL);

  E2SM_RC_EventTrigger_Format1_t* dst = calloc(1, sizeof(E2SM_RC_EventTrigger_Format1_t));
  assert(dst != NULL && "Memory exhausted");

  assert(src->sz_msg_ev_trg > 0 && src->sz_msg_ev_trg <  65535 + 1);
  for(size_t i = 0; i < src->sz_msg_ev_trg; ++i){
    E2SM_RC_EventTrigger_Format1_Item_t* ie =	cp_rc_ev_trigger_format_1_it(&src->msg_ev_trg[i]); 
    int rc = ASN_SEQUENCE_ADD(&dst->message_List.list, ie);
    assert(rc == 0);
  }


  assert(src->global_assoc_ue_info == NULL && "Not implemented");

  return dst;
}

static
E2SM_RC_EventTrigger_Format2_t*	cp_rc_ev_trigger_format_2(e2sm_rc_ev_trg_frmt_2_t const* src)
{
  assert(src != NULL);

  E2SM_RC_EventTrigger_Format2_t* dst = calloc(1, sizeof(E2SM_RC_EventTrigger_Format2_t));
  assert(dst != NULL && "Memory exhausted");

  //  Call Process Type ID
  //  Mandatory
  //  9.3.15
  //  INTEGER (1.. 65535, …)
  assert(src-> call_proc_type_id > 0);
  dst->ric_callProcessType_ID = src->call_proc_type_id;

  // Call Breakpoint ID
  // Mandatory
  // 9.3.49
  // INTEGER (1.. 65535, …)
  assert(src->call_break_id > 0);
  dst->ric_callProcessBreakpoint_ID = src->call_break_id;

  // Associated E2 Node Info
  // Optional
  // 9.3.29
  assert(src->assoc_e2_node_info == NULL && "Not implmeneted");

  // Associated UE Info
  // Optional
  // 9.3.26
  assert(src->assoc_ue_info == NULL && "Not implmeented");

  return dst;
}

static
E2SM_RC_EventTrigger_Format3_Item_t* cp_rc_ev_trigger_format_3_it(e2_node_info_chng_t const* src)
{
  assert(src != NULL);

  E2SM_RC_EventTrigger_Format3_Item_t* dst = calloc(1, sizeof(E2SM_RC_EventTrigger_Format3_Item_t)); 
  assert(dst != NULL && "Memory exhausted");

  //Event Trigger Condition ID
  //Mandatory
  //9.3.21
  // INTEGER (1..65535, …)
  assert(src->ev_trigger_cond_id > 0);
  dst->ric_eventTriggerCondition_ID = src->ev_trigger_cond_id;

  // E2 Node Information Change ID
  // Mandatory
  // INTEGER (1..512, ...)
  assert(src->e2_node_info_chng_id > 0 && src->e2_node_info_chng_id < 512 + 1); 
  dst->e2NodeInfoChange_ID = src->e2_node_info_chng_id;

  // Associated Cell Info
  // Optional
  // 9.3.27
  // ev_trigger_cell_info_t* ev_trigger_cell_info;

  // Logical OR
  // Optional
  // 9.3.25
  // logical_or_e* log_or; 

  return dst;
}


static
E2SM_RC_EventTrigger_Format3_t* cp_rc_ev_trigger_format_3(e2sm_rc_ev_trg_frmt_3_t const* src)
{
  assert(src != NULL);

  E2SM_RC_EventTrigger_Format3_t* dst = calloc(1, sizeof(E2SM_RC_EventTrigger_Format3_t));
  assert(dst != NULL && "Memory exhausted");

  for(size_t i = 0; i < src->sz_e2_node_info_chng; ++i){
    E2SM_RC_EventTrigger_Format3_Item_t* ie =	cp_rc_ev_trigger_format_3_it(&src->e2_node_info_chng[i]); 
    int rc = ASN_SEQUENCE_ADD(&dst->e2NodeInfoChange_List.list, ie);
    assert(rc == 0);
  } 

  return dst;
}

static
TriggerType_Choice_RRCstate_Item_t* cp_rrc_state(rrc_state_t const* src)
{
  assert(src != NULL);

  TriggerType_Choice_RRCstate_Item_t* dst = calloc(1, sizeof(TriggerType_Choice_RRCstate_Item_t));
  assert(dst != NULL && "Memory exhausted");

  if(src->state_chngd_to == RRC_CONNECTED_RRC_STATE_E2SM_RC){
    dst->stateChangedTo = RRC_State_rrc_connected;
  } else if(src->state_chngd_to == RRC_INACTIVE_RRC_STATE_E2SM_RC ){
    dst->stateChangedTo = RRC_State_rrc_inactive;	
  } else if(src->state_chngd_to == RRC_IDLE_RRC_STATE_E2SM_RC){
    dst->stateChangedTo = RRC_State_rrc_idle;
  } else if(src->state_chngd_to == ANY_RRC_STATE_E2SM_RC){
    dst->stateChangedTo = RRC_State_any;
  } else {
    assert( 0!=0 && "unknown type");
  }

  // 9.3.25
  // Logical OR
  assert(src->log_or == NULL && "Not implemented");

  return dst;
}

static
RANParameter_Value_t cp_ran_param_val(ran_parameter_value_t const* src)
{
  RANParameter_Value_t dst = {0}; 

  if(src->type == BOOLEAN_RAN_PARAMETER_VALUE){
    dst.present = RANParameter_Value_PR_valueBoolean;
    dst.choice.valueBoolean = src->bool_ran;
  } else if(src->type == INTEGER_RAN_PARAMETER_VALUE){
    dst.present = RANParameter_Value_PR_valueInt;
    dst.choice.valueInt = src->int_ran;
  }else if(src->type == REAL_RAN_PARAMETER_VALUE){
    dst.present = RANParameter_Value_PR_valueReal;
    dst.choice.valueReal = src->real_ran;
  }else if(src->type == BIT_STRING_RAN_PARAMETER_VALUE){
    dst.present = RANParameter_Value_PR_valueBitS;
    dst.choice.valueBitS = copy_ba_to_bit_string(src->bit_str_ran);
  }else if(src->type == OCTET_STRING_RAN_PARAMETER_VALUE){
    dst.present = RANParameter_Value_PR_valueOctS;
    dst.choice.valueOctS = copy_ba_to_ostring(src->octet_str_ran);
  } else if(src->type == PRINTABLESTRING_RAN_PARAMETER_VALUE){
    dst.present = RANParameter_Value_PR_valuePrintableString;
    dst.choice.valuePrintableString = copy_ba_to_ostring(src->printable_str_ran);
  } else {
    assert(0!=0 && "Not implemented");
  }

  return dst;
}

static
RANParameter_Testing_Item_Choice_ElementTrue_t cp_elm_true(ran_parameter_value_t const* src)
{
  assert(src != NULL);

  RANParameter_Testing_Item_Choice_ElementTrue_t dst = {0}; 

  dst.ranParameter_value = cp_ran_param_val(src);

  return dst;
}

static
e_RANParameter_TestingCondition__ranP_Choice_comparison cp_ran_param_test_cond_comp(ran_param_test_cond_comp_e src)
{
  e_RANParameter_TestingCondition__ranP_Choice_comparison dst = {0}; 

  if(src == EQUAL_RAN_PARAM_TEST_COND_COMP ){
    dst = RANParameter_TestingCondition__ranP_Choice_comparison_equal;	 
  } else if(src == DIFFERENCE_RAN_PARAM_TEST_COND_COMP ){
    dst = RANParameter_TestingCondition__ranP_Choice_comparison_difference	;
  }else if(src == GREATERTHAN_RAN_PARAM_TEST_COND_COMP){
    dst = RANParameter_TestingCondition__ranP_Choice_comparison_greaterthan	;
  }else if(src == LESSTHAN_RAN_PARAM_TEST_COND_COMP){
    dst = RANParameter_TestingCondition__ranP_Choice_comparison_lessthan	;
  }else if(src == CONTAINS_RAN_PARAM_TEST_COND_COMP){
    dst = RANParameter_TestingCondition__ranP_Choice_comparison_contains	;
  }else if(src == STARTS_WITH_RAN_PARAM_TEST_COND_COMP){
    dst = RANParameter_TestingCondition__ranP_Choice_comparison_starts_with	;
  } else {
    assert(0 != 0 && "Unknown type");
  }

  return dst;
}

static
e_RANParameter_TestingCondition__ranP_Choice_presence cp_ran_param_test_cond_presence(ran_param_test_cond_presence_e src)
{
  e_RANParameter_TestingCondition__ranP_Choice_presence dst = {0}; 

  if(src == PRESENT_RAN_PARAM_TEST_COND_PRESENCE){
    dst = RANParameter_TestingCondition__ranP_Choice_presence_present;
  } else if(src == CONFIGURED_RAN_PARAM_TEST_COND_PRESENCE){
    dst = RANParameter_TestingCondition__ranP_Choice_presence_configured;
  } else if(src == ROLLOVER_RAN_PARAM_TEST_COND_PRESENCE ){
    dst = RANParameter_TestingCondition__ranP_Choice_presence_rollover;
  } else if(src == NON_ZERO_RAN_PARAM_TEST_COND_PRESENCE){
    dst = RANParameter_TestingCondition__ranP_Choice_presence_non_zero;
  } else {
    assert(0 !=0 && "Unknown type");
  }

  return dst;
}

static
RANParameter_TestingCondition_t cp_ran_param_test_cond(ran_param_test_cond_t const* src)
{
  assert(src != NULL);

  RANParameter_TestingCondition_t dst = {0}; 

  if(src->cond == COMPARISON_RAN_PARAM_TEST_COND){
    dst.present = RANParameter_TestingCondition_PR_ranP_Choice_comparison;
    dst.choice.ranP_Choice_comparison = cp_ran_param_test_cond_comp(src->comp);
  } else if(src->cond == PRESENCE_RAN_PARAM_TEST_COND){
    dst.present = RANParameter_TestingCondition_PR_ranP_Choice_presence;
    dst.choice.ranP_Choice_presence = cp_ran_param_test_cond_presence(src->presence);
  } else {
    assert(0!=0 && "Unknown type" );
  }

  return dst;
}

static
RANParameter_Testing_Item_Choice_ElementFalse_t	cp_elm_false(ran_param_elm_key_false_t const* src)
{
  assert(src != NULL);

  RANParameter_Testing_Item_Choice_ElementFalse_t dst = {0};

  // RAN Parameter Test Condition
  // 9.3.31
  // Mandatory
  dst.ranParameter_TestCondition = cp_ran_param_test_cond(&src->test_cond);  

  // RAN Parameter Value
  // Optional
  // 9.3.14
  assert(src->value == NULL);

  // Logical OR
  // Optional
  // 9.3.25
  assert(src->logical_or == NULL);

  return dst;
}

static
RANParameter_Testing_Item_t* cp_ran_param_test(ran_param_test_t const* src)
{
  assert(src != NULL);

  RANParameter_Testing_Item_t* dst = calloc(1, sizeof(RANParameter_Testing_Item_t));
  assert(dst != NULL && "Memory exhausted");

  //RAN Parameter ID
  //Mandatory
  //Bug in the standard. 9.3.9 wrote in section 9. 
  //9.3.8 in ASN language. Probably 9.3.8 intended
  //1.. 4294967295
  assert(src->ran_param_id > 0); 
  dst->ranParameter_ID = src->ran_param_id;

  if(src->type == LIST_RAN_PARAMETER_TYPE){

    dst->ranParameter_Type.present = RANParameter_Testing_Item__ranParameter_Type_PR_ranP_Choice_List;
    
    dst->ranParameter_Type.choice.ranP_Choice_List = calloc(1, sizeof(RANParameter_Testing_Item_Choice_List_t));
    assert(dst->ranParameter_Type.choice.ranP_Choice_List != NULL && "Memory exhausted" );

    dst->ranParameter_Type.choice.ranP_Choice_List->ranParameter_List = calloc(1, sizeof(RANParameter_Testing_LIST_t ));
    assert(dst->ranParameter_Type.choice.ranP_Choice_List->ranParameter_List != NULL && "Memory exhausted");

    for(size_t i = 0; i < src->lst.sz_lst; ++i ) {
      RANParameter_Testing_Item_t* ie = cp_ran_param_test(&src->lst.ran_param_test[i]);
      int rc = ASN_SEQUENCE_ADD(&dst->ranParameter_Type.choice.ranP_Choice_List->ranParameter_List->list, ie);
      assert(rc == 0);
    }

  } else if(src->type == STRUCTURE_RAN_PARAMETER_TYPE){

    dst->ranParameter_Type.present = RANParameter_Testing_Item__ranParameter_Type_PR_ranP_Choice_Structure;
    
    dst->ranParameter_Type.choice.ranP_Choice_Structure = calloc(1, sizeof(RANParameter_Testing_Item_Choice_Structure_t));
    assert(dst->ranParameter_Type.choice.ranP_Choice_Structure != NULL && "Memory exhausted" );

    dst->ranParameter_Type.choice.ranP_Choice_Structure->ranParameter_Structure = calloc(1, sizeof(RANParameter_Testing_STRUCTURE_t));
    assert(dst->ranParameter_Type.choice.ranP_Choice_Structure->ranParameter_Structure != NULL && "Memory exhausted");

    for(size_t i = 0; i < src->strct.sz_strct; ++i){
      RANParameter_Testing_Item_t* ie = cp_ran_param_test(&src->strct.ran_param_test[i]);
      int rc = ASN_SEQUENCE_ADD(&dst->ranParameter_Type.choice.ranP_Choice_Structure->ranParameter_Structure->list, ie);
      assert(rc == 0);
    }

  } else if(src->type == ELEMENT_WITH_KEY_FLAG_TRUE_RAN_PARAMETER_TYPE){

    dst->ranParameter_Type.present = RANParameter_Testing_Item__ranParameter_Type_PR_ranP_Choice_ElementTrue;

    dst->ranParameter_Type.choice.ranP_Choice_ElementTrue = calloc(1, sizeof(RANParameter_Testing_Item_Choice_ElementTrue_t)); 
    assert(dst->ranParameter_Type.choice.ranP_Choice_ElementTrue != NULL && "Memory exhausted" );

    *dst->ranParameter_Type.choice.ranP_Choice_ElementTrue = cp_elm_true(&src->flag_true); 

  } else if(src->type == ELEMENT_WITH_KEY_FLAG_FALSE_RAN_PARAMETER_TYPE){

    dst->ranParameter_Type.present = RANParameter_Testing_Item__ranParameter_Type_PR_ranP_Choice_ElementFalse;

    dst->ranParameter_Type.choice.ranP_Choice_ElementFalse = calloc(1, sizeof(RANParameter_Testing_Item_Choice_ElementFalse_t)); 
    assert(dst->ranParameter_Type.choice.ranP_Choice_ElementFalse != NULL && "Memory exhausted" );

    *dst->ranParameter_Type.choice.ranP_Choice_ElementFalse = cp_elm_false(&src->flag_false); 

  } else{
    assert(0!=0 && "Unknown type" );
  }

  return dst;
}


static
E2SM_RC_EventTrigger_Format4_Item_t* cp_rc_ev_trigger_format_4_it(ue_info_chng_t const* src)
{
  assert(src != NULL);

  E2SM_RC_EventTrigger_Format4_Item_t* dst = calloc(1, sizeof(E2SM_RC_EventTrigger_Format4_Item_t));
  assert(dst != NULL && "Memory exhausted");

  //  Event Trigger Condition ID
  //  Mandatory
  //  9.3.21
  // INTEGER (1..65535, …)
  assert(src->ev_trig_cond_id > 0);
  dst->ric_eventTriggerCondition_ID = src->ev_trig_cond_id;

  // CHOICE Trigger Type
  if(src->type == RRC_STATE_UE_INFO_CHNG_TRIGGER_TYPE){
    dst->triggerType.present = TriggerType_Choice_PR_triggerType_Choice_RRCstate;

    dst->triggerType.choice.triggerType_Choice_RRCstate = calloc(1, sizeof( TriggerType_Choice_RRCstate_t	));
    assert(dst->triggerType.choice.triggerType_Choice_RRCstate != NULL && "Memory exhausted");
    
    TriggerType_Choice_RRCstate_t* dst_rrc = dst->triggerType.choice.triggerType_Choice_RRCstate; 

    // [1 - 8]
    assert(src->rrc_state.sz_rrc_state > 0 &&  src->rrc_state.sz_rrc_state < 9); 
    for(size_t i = 0; i < src->rrc_state.sz_rrc_state; ++i){
      TriggerType_Choice_RRCstate_Item_t* ie = cp_rrc_state(&src->rrc_state.state_chng_to[i]);
      int rc = ASN_SEQUENCE_ADD(&dst_rrc->rrcState_List.list, ie);
      assert(rc == 0);
    }

  } else if(src->type == UE_ID_CHANGE_UE_INFO_CHNG_TRIGGER_TYPE){
    dst->triggerType.present = TriggerType_Choice_PR_triggerType_Choice_UEID;

    dst->triggerType.choice.triggerType_Choice_UEID = calloc(1, sizeof(TriggerType_Choice_UEID_t));
    assert(dst->triggerType.choice.triggerType_Choice_UEID != NULL && "Memory exhausted" );

    dst->triggerType.choice.triggerType_Choice_UEID->ueIDchange_ID = src->ue_id_chng;

  } else if(src->type == L2_STATE_UE_INFO_CHNG_TRIGGER_TYPE) {

    dst->triggerType.present = TriggerType_Choice_PR_triggerType_Choice_L2state;

    dst->triggerType.choice.triggerType_Choice_L2state = calloc(1, sizeof(TriggerType_Choice_L2state_t));
    assert(dst->triggerType.choice.triggerType_Choice_L2state != NULL && "Memory exhausted" );
    
    TriggerType_Choice_L2state_t* dst_l2 = dst->triggerType.choice.triggerType_Choice_L2state; 
    // [1-255]
    assert(src->l2_state.sz_ran_param_test > 0 && src->l2_state.sz_ran_param_test < 256);  
    for(size_t i = 0; i < src->l2_state.sz_ran_param_test; ++i){
      RANParameter_Testing_Item_t* ie = cp_ran_param_test(&src->l2_state.ran_param_test[i]);
      int rc = ASN_SEQUENCE_ADD(&dst_l2->associatedL2variables.list, ie);
      assert(rc == 0);
    }

  } else {
    assert(0 != 0 && "Unknown type");
  }
	
  // Associated UE Info 
  // Optional
  // 9.3.26
  assert(src->assoc_ue_info == NULL && "Not implemented"); 

  // Logical OR
  // Optional
  // 9.3.25
  assert(src->log_or == NULL && "Not implemented" ); 

  return dst;
}

static
E2SM_RC_EventTrigger_Format4_t*	cp_rc_ev_trigger_format_4(e2sm_rc_ev_trg_frmt_4_t const* src)
{
  assert(src != NULL);

  E2SM_RC_EventTrigger_Format4_t* dst = calloc(1, sizeof(E2SM_RC_EventTrigger_Format4_t));
  assert(dst != NULL && "Memory exhausted");

 // Sequence of UE Information Change
 // [ 1 - 65535]
  assert(src->sz_ue_info_chng > 0 && src->sz_ue_info_chng <  65535 + 1 );
  assert(src->ue_info_chng != NULL);

  for(size_t i = 0; i < src->sz_ue_info_chng; ++i){
    E2SM_RC_EventTrigger_Format4_Item_t* ie = cp_rc_ev_trigger_format_4_it(&src->ue_info_chng[i]); 
    int rc = ASN_SEQUENCE_ADD(&dst->uEInfoChange_List.list, ie);
    assert(rc == 0);
  }

  return dst;
}

static
E2SM_RC_EventTrigger_Format5_t* cp_rc_ev_trigger_format_5(e2sm_rc_ev_trg_frmt_5_t const* src)
{
  assert(src != NULL);

  E2SM_RC_EventTrigger_Format5_t* dst = calloc(1, sizeof(E2SM_RC_EventTrigger_Format5_t));
  assert(dst != NULL && "Memory exhausted");

  // On Demand
  // Mandatory
  if(src->on_demand == TRUE_ON_DEMAND_FRMT_5){
    dst->onDemand =  E2SM_RC_EventTrigger_Format5__onDemand_true;	
  } else{
    assert(0!=0 && "Unknown type");
  }

  // Associated UE Info
  // Optional
  // 9.3.26
  assert(src->assoc_ue_info == NULL && "Not implemented");

  // Associated Cell Info
  // Optional
  // 9.3.27
  assert(src->assoc_cell_info == NULL && "Not implemented");

  return dst;
}


byte_array_t rc_enc_event_trigger_asn(e2sm_rc_event_trigger_t const* src)
{
  assert(src != NULL);

  E2SM_RC_EventTrigger_t dst = {0};
  defer({  ASN_STRUCT_RESET(asn_DEF_E2SM_RC_EventTrigger, &dst); });

  if(src->format == FORMAT_1_E2SM_RC_EV_TRIGGER_FORMAT){
    dst.ric_eventTrigger_formats.present = E2SM_RC_EventTrigger__ric_eventTrigger_formats_PR_eventTrigger_Format1;
    dst.ric_eventTrigger_formats.choice.eventTrigger_Format1 = cp_rc_ev_trigger_format_1(&src->frmt_1);

  } else if(src->format == FORMAT_2_E2SM_RC_EV_TRIGGER_FORMAT){
    dst.ric_eventTrigger_formats.present = E2SM_RC_EventTrigger__ric_eventTrigger_formats_PR_eventTrigger_Format2;
    dst.ric_eventTrigger_formats.choice.eventTrigger_Format2 = cp_rc_ev_trigger_format_2(&src->frmt_2);

  } else if(src->format ==  FORMAT_3_E2SM_RC_EV_TRIGGER_FORMAT){
    dst.ric_eventTrigger_formats.present = E2SM_RC_EventTrigger__ric_eventTrigger_formats_PR_eventTrigger_Format3;
    dst.ric_eventTrigger_formats.choice.eventTrigger_Format3 = cp_rc_ev_trigger_format_3(&src->frmt_3);

  } else if(src->format == FORMAT_4_E2SM_RC_EV_TRIGGER_FORMAT){
    dst.ric_eventTrigger_formats.present = E2SM_RC_EventTrigger__ric_eventTrigger_formats_PR_eventTrigger_Format4;
    dst.ric_eventTrigger_formats.choice.eventTrigger_Format4 = cp_rc_ev_trigger_format_4(&src->frmt_4);

  } else if(src->format == FORMAT_5_E2SM_RC_EV_TRIGGER_FORMAT){
    dst.ric_eventTrigger_formats.present = E2SM_RC_EventTrigger__ric_eventTrigger_formats_PR_eventTrigger_Format5;
    dst.ric_eventTrigger_formats.choice.eventTrigger_Format5 = cp_rc_ev_trigger_format_5(&src->frmt_5);

  } else {
    assert(0!=0 && "Unknown format");
  }

  xer_fprint(stdout, &asn_DEF_E2SM_RC_EventTrigger, &dst);
  fflush(stdout);

  byte_array_t ba = {.buf = malloc(512*1024), .len = 512*1024};
  const enum asn_transfer_syntax syntax = ATS_ALIGNED_BASIC_PER;
  asn_enc_rval_t er = asn_encode_to_buffer(NULL, syntax, &asn_DEF_E2SM_RC_EventTrigger, &dst, ba.buf, ba.len);
  assert(er.encoded > -1 && (size_t)er.encoded <= ba.len);
  ba.len = er.encoded;

  return ba;

}

static
E2SM_RC_ActionDefinition_Format1_Item_t* cp_rc_act_def_frmt_1_it(param_report_def_t const* src)
{
  assert(src != NULL);

  E2SM_RC_ActionDefinition_Format1_Item_t* dst = calloc(1, sizeof(E2SM_RC_ActionDefinition_Format1_Item_t));
  assert(dst != NULL && "Memory exhausted");

  // RAN Parameter ID
  // Mandatory
  // 9.3.8
  // [1 - 4294967295]
  assert(src->ran_param_id > 0);
  dst->ranParameter_ID = src->ran_param_id;

  // RAN Parameter Definition
  // Optional
  // 9.3.51
  assert(src->ran_param_def == NULL && "Not implemented");

  return dst;
}

static
E2SM_RC_ActionDefinition_Format1_t*	cp_act_def_frmt_1(e2sm_rc_act_def_frmt_1_t const* src)
{
  assert(src != NULL);

  E2SM_RC_ActionDefinition_Format1_t* dst = calloc(1, sizeof(E2SM_RC_ActionDefinition_Format1_t)); 
  
  assert(src->sz_param_report_def > 0 && src->sz_param_report_def < 65535+1);

  for(size_t i = 0; i < src->sz_param_report_def; ++i){
    E2SM_RC_ActionDefinition_Format1_Item_t* ie =	cp_rc_act_def_frmt_1_it(&src->param_report_def[i]); 
    int rc = ASN_SEQUENCE_ADD(&dst->ranP_ToBeReported_List.list, ie);
    assert(rc == 0);
  }


  return dst;
}

// Forward declaration to avoid the cycle between  cp_ran_param_value_type and cp_ran_param_struct
static
RANParameter_ValueType_t cp_ran_param_value_type(ran_param_val_type_t const* src);

static
RANParameter_STRUCTURE_Item_t* cp_ran_param_struct(seq_ran_param_t const* src)
{
  assert(src != NULL);

  RANParameter_STRUCTURE_Item_t* dst = calloc(1, sizeof(RANParameter_STRUCTURE_Item_t) );
  assert(dst != NULL && "memory exhausted");

  //RAN Parameter ID
  //Mandatory
  //9.3.8
  // [1 - 4294967295]
  assert(src->ran_param_id > 0);
  dst->ranParameter_ID = src->ran_param_id;

  // RAN Parameter Value Type
  // 9.3.11
  // Mandatory
  dst->ranParameter_valueType = calloc(1, sizeof(RANParameter_ValueType_t ));
  assert(dst->ranParameter_valueType != NULL && "Memory exhausted");

  *dst->ranParameter_valueType = cp_ran_param_value_type(&src->ran_param_val); 

  return dst;
}

static
RANParameter_STRUCTURE_t* cp_lst_ran_param(lst_ran_param_t const* src)
{
  assert(src != NULL);

  RANParameter_STRUCTURE_t* dst = calloc(1, sizeof(RANParameter_STRUCTURE_t));
  assert(dst != NULL);
  
  dst->sequence_of_ranParameters = calloc(1, sizeof(struct RANParameter_STRUCTURE__sequence_of_ranParameters));
  assert(dst->sequence_of_ranParameters != NULL && "Memory exhausted" );

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

  for(size_t i = 0; i < src->ran_param_struct.sz_ran_param_struct; ++i){
    RANParameter_STRUCTURE_Item_t* ie = cp_ran_param_struct(&src->ran_param_struct.ran_param_struct[i]);
    int rc = ASN_SEQUENCE_ADD(&dst->sequence_of_ranParameters->list, ie);
    assert(rc == 0);
  }

  return dst;
}



static
RANParameter_ValueType_t cp_ran_param_value_type(ran_param_val_type_t const* src)
{
  assert(src != NULL);

  RANParameter_ValueType_t dst = {0};	

  if(src->type == ELEMENT_KEY_FLAG_TRUE_RAN_PARAMETER_VAL_TYPE){

    dst.present = RANParameter_ValueType_PR_ranP_Choice_ElementTrue;

    dst.choice.ranP_Choice_ElementTrue = calloc(1, sizeof(RANParameter_ValueType_Choice_ElementTrue_t));
    assert(dst.choice.ranP_Choice_ElementTrue != NULL && "Memory exhausted" );

    dst.choice.ranP_Choice_ElementTrue->ranParameter_value = cp_ran_param_val(src->flag_true) ;

  } else if(src->type == ELEMENT_KEY_FLAG_FALSE_RAN_PARAMETER_VAL_TYPE ){

    dst.present = RANParameter_ValueType_PR_ranP_Choice_ElementFalse;

    dst.choice.ranP_Choice_ElementFalse = calloc(1, sizeof(RANParameter_ValueType_Choice_ElementFalse_t));
    assert(dst.choice.ranP_Choice_ElementFalse != NULL && "Memory exhausted" );

    dst.choice.ranP_Choice_ElementFalse->ranParameter_value = calloc(1, sizeof(   RANParameter_Value_t));
    assert(dst.choice.ranP_Choice_ElementFalse->ranParameter_value != NULL && "Memory exhausted");

    *dst.choice.ranP_Choice_ElementFalse->ranParameter_value = cp_ran_param_val(src->flag_false);

  } else if(src->type == STRUCTURE_RAN_PARAMETER_VAL_TYPE ){

    dst.present = RANParameter_ValueType_PR_ranP_Choice_Structure;

    dst.choice.ranP_Choice_Structure = calloc(1, sizeof(RANParameter_ValueType_Choice_Structure_t));
    assert(dst.choice.ranP_Choice_Structure != NULL && "Memory exhausted" );

    dst.choice.ranP_Choice_Structure->ranParameter_Structure = calloc(1, sizeof( RANParameter_STRUCTURE_t ));	
    assert(dst.choice.ranP_Choice_Structure->ranParameter_Structure != NULL && "Memory exhausted");

    dst.choice.ranP_Choice_Structure->ranParameter_Structure->sequence_of_ranParameters = calloc(1, sizeof(struct RANParameter_STRUCTURE__sequence_of_ranParameters));
    assert(dst.choice.ranP_Choice_Structure->ranParameter_Structure->sequence_of_ranParameters != NULL && "Memory exhausted");

    for(size_t i = 0; i < src->strct->sz_ran_param_struct; ++i){
      RANParameter_STRUCTURE_Item_t* ie = cp_ran_param_struct(&src->strct->ran_param_struct[i]);
      int rc = ASN_SEQUENCE_ADD(&dst.choice.ranP_Choice_Structure->ranParameter_Structure->sequence_of_ranParameters->list, ie);
      assert(rc == 0);
    }

  } else if(src->type == LIST_RAN_PARAMETER_VAL_TYPE){
    dst.present = RANParameter_ValueType_PR_ranP_Choice_List;

    dst.choice.ranP_Choice_List = calloc(1, sizeof(RANParameter_ValueType_Choice_List_t)); 
    assert(dst.choice.ranP_Choice_List != NULL && "Memory exhausted");

    dst.choice.ranP_Choice_List->ranParameter_List = calloc(1, sizeof(RANParameter_LIST_t));
    assert(dst.choice.ranP_Choice_List->ranParameter_List != NULL && "Memory exhausted" );

    for(size_t i = 0; i < src->lst->sz_lst_ran_param; ++i){
      RANParameter_STRUCTURE_t* ie = cp_lst_ran_param(&src->lst->lst_ran_param[i]);
      int rc = ASN_SEQUENCE_ADD(&dst.choice.ranP_Choice_List->ranParameter_List->list_of_ranParameter.list, ie);
      assert(rc == 0);
    }

  } else {
    assert(0!=0 && "Unknown type");
  }

  return dst;
}

static
RIC_PolicyAction_RANParameter_Item_t* cp_ric_policy_action_ran_param(seq_ran_param_t const* src)
{
  assert(src != NULL);

  RIC_PolicyAction_RANParameter_Item_t* dst = calloc(1,sizeof( RIC_PolicyAction_RANParameter_Item_t));
  assert(dst != NULL && "Memory exhausted");

  //RAN Parameter ID
  //Mandatory
  //9.3.8
  // [1 - 4294967295]
  assert(src->ran_param_id > 0);
  dst->ranParameter_ID = src->ran_param_id;

  // RAN Parameter Value Type
  // 9.3.11
  // Mandatory
  dst->ranParameter_valueType = cp_ran_param_value_type(&src->ran_param_val); 

  return dst;
}

static
RIC_PolicyAction_t cp_ric_policy_action(policy_action_t const* src)
{
  assert(src != NULL);

  RIC_PolicyAction_t dst = {0}; 

  //  Policy Action ID
  //  Mandatory
  //  9.3.6
  //  [1 - 65535]
  assert(src-> policy_act_id > 0);
  dst.ric_PolicyAction_ID = src->policy_act_id;

  // Sequence of RAN Parameters
  // [0- 65535]
  if(src->sz_seq_ran_param > 0){
    dst.ranParameters_List = calloc(1, sizeof(struct RIC_PolicyAction__ranParameters_List));
    assert(dst.ranParameters_List != NULL && "Memory exhausted");
  } 

  for(size_t i = 0; i < src->sz_seq_ran_param; ++i){
    RIC_PolicyAction_RANParameter_Item_t* ie = cp_ric_policy_action_ran_param(&src->seq_ran_param[i]) ; 
    int rc = ASN_SEQUENCE_ADD(&dst.ranParameters_List->list, ie);
    assert(rc == 0);
  }
  
  // RIC Policy decision
  // Optional
  assert(src->pol_dec == NULL && "Not implemented");

  return dst;
}

static
E2SM_RC_ActionDefinition_Format2_Item_t* cp_rc_act_def_frmt_2_it(policy_cond_t const* src)
{
  assert(src != NULL);

  E2SM_RC_ActionDefinition_Format2_Item_t* dst = calloc(1, sizeof(E2SM_RC_ActionDefinition_Format2_Item_t));

  // Policy Action Definition
  // Mandatory
  // 9.3.20
  dst->ric_PolicyAction = cp_ric_policy_action(&src->pol_act); 

  // Policy Condition Definition
  // Optional
  // 9.3.29
  assert(src->pol == NULL && "Not implemented");

  return dst;
}

static
E2SM_RC_ActionDefinition_Format2_t* cp_act_def_frmt_2(e2sm_rc_act_def_frmt_2_t const* src)
{
  assert(src != NULL);

  E2SM_RC_ActionDefinition_Format2_t* dst = calloc(1, sizeof(E2SM_RC_ActionDefinition_Format2_t));
  assert(dst != NULL && "Memory exhausted");

  // Sequence of Policy Conditions
  // [1 - 65535]
  assert(src->sz_policy_cond > 0);

  for(size_t i = 0; i < src->sz_policy_cond; ++i){
    E2SM_RC_ActionDefinition_Format2_Item_t* ie =	cp_rc_act_def_frmt_2_it(&src->policy_cond[i]); 
    int rc = ASN_SEQUENCE_ADD(&dst->ric_PolicyConditions_List.list, ie);
    assert(rc == 0);
  }

  return dst;
}

static
E2SM_RC_ActionDefinition_Format3_Item_t* cp_rc_act_def_frmt_3_it(ran_param_ins_t const* src)
{
  assert(src != NULL);

  E2SM_RC_ActionDefinition_Format3_Item_t* dst = calloc(1, sizeof(E2SM_RC_ActionDefinition_Format3_Item_t));
  assert(dst != NULL && "memory exhausted");

  // RAN Parameter ID
  // Mandatory
  // 9.3.8
  // [1 - 4294967295]
  assert(src->ran_id > 0);
  dst->ranParameter_ID = src->ran_id;

  // RAN Parameter Definition
  // Optional
  // 9.3.51
  assert(src->def == NULL && "Not implemented");

  return dst;
}


static
E2SM_RC_ActionDefinition_Format3_t* cp_act_def_frmt_3(e2sm_rc_act_def_frmt_3_t const* src)
{
  assert(src != NULL);

  E2SM_RC_ActionDefinition_Format3_t* dst = calloc(1, sizeof(E2SM_RC_ActionDefinition_Format3_t));
  assert(dst != NULL && "Memory exhausted");

  // Insert Indication ID
  // Mandatory
  // 9.3.16
  // [1 - 65535] 
  assert(src->id > 0); 
  dst->ric_InsertIndication_ID = src->id;

  // List of RAN parameters for Insert
  // Indication
  // [1 - 65535]
  assert(src->sz_ran_param_ins > 0);

  for(size_t i = 0; i < src->sz_ran_param_ins; ++i){
    E2SM_RC_ActionDefinition_Format3_Item_t* ie =	cp_rc_act_def_frmt_3_it(&src->ran_param[i]);
    int rc = ASN_SEQUENCE_ADD(&dst->ranP_InsertIndication_List.list, ie);
    assert(rc == 0);
  }

  //  UE ID
  //  Optional
  //  9.3.10
  assert(src->ue_id == NULL && "not implmeented");

  return dst;
}




static
E2SM_RC_ActionDefinition_Format4_RANP_Item_t* cp_ran_param_ins_ind(ran_param_ins_ind_t const* src)
{
  assert(src != NULL);
  
  E2SM_RC_ActionDefinition_Format4_RANP_Item_t* dst = calloc(1, sizeof(E2SM_RC_ActionDefinition_Format4_RANP_Item_t)); 
  assert(dst != NULL && "memory exhausted");

  // RAN Parameter ID
  // Mandatory
  // 9.3.8
  // [1.. 429496729 ]
  assert(src->ran_param_id > 0);
  dst->ranParameter_ID = src->ran_param_id;

  // RAN Parameter Definition
  // Optional
  // 9.3.51
  assert(src->ran_param_def == NULL && "Not implemented"); 

  return dst;
}

static
E2SM_RC_ActionDefinition_Format4_Indication_Item_t* cp_seq_ins_ind_act_def(seq_ins_ind_act_def_t const* src)
{
  assert(src != NULL);

  E2SM_RC_ActionDefinition_Format4_Indication_Item_t* dst = calloc(1, sizeof(E2SM_RC_ActionDefinition_Format4_Indication_Item_t) );
  assert(dst != NULL && "Memory exhausted");

  // Insert Indication ID
  // Mandatory
  // 9.3.16
  // [1 - 65535]
  assert(src->ind_id > 0);
  dst->ric_InsertIndication_ID = src->ind_id;

  // List of RAN parameters for
  // Insert Indication
  // [1-65535]
  assert(src->sz_ran_param_ins_ind > 0 && src->sz_ran_param_ins_ind < 65535+1);

  for(size_t i = 0; i < src->sz_ran_param_ins_ind; ++i){
    E2SM_RC_ActionDefinition_Format4_RANP_Item_t* ie = cp_ran_param_ins_ind(&src->ran_param_ins_ind[i]);
    int rc = ASN_SEQUENCE_ADD(&dst->ranP_InsertIndication_List.list, ie);
    assert(rc == 0);
  }

  return dst;
}

static
E2SM_RC_ActionDefinition_Format4_Style_Item_t* cp_seq_ins_styles(seq_ins_style_t const* src)
{
  assert(src != NULL);

  E2SM_RC_ActionDefinition_Format4_Style_Item_t* dst = calloc(1, sizeof(E2SM_RC_ActionDefinition_Format4_Style_Item_t));

  // Requested Insert Style
  // Mandatory
  // 9.3.3
  // 6.2.2.2. in E2 SM common 
  // Integer
  dst->requested_Insert_Style_Type = src->req_insert_style;

  // Sequence of Insert Indication
  // Action Definition
  // [1-63]
  assert(src->sz_seq_ins_ind_act_def > 0 && src->sz_seq_ins_ind_act_def < 64);

  for(size_t i = 0; i < src->sz_seq_ins_ind_act_def; ++i){
    E2SM_RC_ActionDefinition_Format4_Indication_Item_t* ie = cp_seq_ins_ind_act_def(&src->seq_ins_ind_act_def[i]); 
    int rc = ASN_SEQUENCE_ADD(&dst->ric_InsertIndication_List.list, ie);
    assert(rc == 0);
  }

  return dst;
}

static
E2SM_RC_ActionDefinition_Format4_t* cp_act_def_frmt_4(e2sm_rc_act_def_frmt_4_t const* src)
{
  assert(src != NULL);

  E2SM_RC_ActionDefinition_Format4_t* dst = calloc(1, sizeof(E2SM_RC_ActionDefinition_Format4_t));
  assert(dst != NULL && "Memory exhausted");

  // Sequence of Insert Styles for
  // Multiple Actions
  // [1-4]
  assert(src->sz_seq_ins_style > 0 && src->sz_seq_ins_style < 5);
  assert(src->seq_ins_style != NULL);

  for(size_t i = 0; i <src->sz_seq_ins_style; ++i){
    E2SM_RC_ActionDefinition_Format4_Style_Item_t* ie =	cp_seq_ins_styles(&src->seq_ins_style[i]);
    int rc = ASN_SEQUENCE_ADD(&dst->ric_InsertStyle_List.list, ie);
    assert(rc == 0);
  }

  // UE ID
  // Optional
  // 9.3.10
  assert(src->ue_id == NULL && "Not implemented"); 

  return dst;
}



byte_array_t rc_enc_action_def_asn(e2sm_rc_action_def_t const* src)
{
  assert(src != NULL);

  E2SM_RC_ActionDefinition_t dst = {0};
  defer({  ASN_STRUCT_RESET( asn_DEF_E2SM_RC_ActionDefinition, &dst); });

  //  RIC Style Type
  //  Mandatory
  //  9.3.3
  // Defined in common 6.2.2.2.
  dst.ric_Style_Type = src->ric_style_type;

  if(src->format == FORMAT_1_E2SM_RC_ACT_DEF){
    dst.ric_actionDefinition_formats.present = E2SM_RC_ActionDefinition__ric_actionDefinition_formats_PR_actionDefinition_Format1;
    dst.ric_actionDefinition_formats.choice.actionDefinition_Format1 = cp_act_def_frmt_1(&src->frmt_1) ;

  } else if(src->format == FORMAT_2_E2SM_RC_ACT_DEF){
    dst.ric_actionDefinition_formats.present = E2SM_RC_ActionDefinition__ric_actionDefinition_formats_PR_actionDefinition_Format2;
    dst.ric_actionDefinition_formats.choice.actionDefinition_Format2 = cp_act_def_frmt_2(&src->frmt_2) ;

  }else if(src->format ==  FORMAT_3_E2SM_RC_ACT_DEF){
    dst.ric_actionDefinition_formats.present = E2SM_RC_ActionDefinition__ric_actionDefinition_formats_PR_actionDefinition_Format3;
    dst.ric_actionDefinition_formats.choice.actionDefinition_Format3 = cp_act_def_frmt_3(&src->frmt_3) ;

  }else if(src->format == FORMAT_4_E2SM_RC_ACT_DEF){
    dst.ric_actionDefinition_formats.present = E2SM_RC_ActionDefinition__ric_actionDefinition_formats_PR_actionDefinition_Format4;
    dst.ric_actionDefinition_formats.choice.actionDefinition_Format4 = cp_act_def_frmt_4(&src->frmt_4);

  } else {
    assert(0!=0 && "not implemented");
  }

  xer_fprint(stdout, &asn_DEF_E2SM_RC_ActionDefinition, &dst);
  fflush(stdout);

  byte_array_t ba = {.buf = malloc(512*1024), .len = 512*1024};
  const enum asn_transfer_syntax syntax = ATS_ALIGNED_BASIC_PER;
  asn_enc_rval_t er = asn_encode_to_buffer(NULL, syntax, &asn_DEF_E2SM_RC_ActionDefinition  , &dst, ba.buf, ba.len);
  assert(er.encoded > -1 && (size_t)er.encoded <= ba.len);
  ba.len = er.encoded;

  return ba;
}


static
E2SM_RC_IndicationHeader_Format1_t* cp_ind_hdr_frmt_1(e2sm_rc_ind_hdr_frmt_1_t const* src)
{
  assert(src != NULL);

  E2SM_RC_IndicationHeader_Format1_t* dst = calloc(1, sizeof(E2SM_RC_IndicationHeader_Format1_t));
  assert(dst != NULL && "Memory exhausted");

  assert(src->ev_trigger_id !=NULL && "Optional but not much sense to not fill it"); 
  dst->ric_eventTriggerCondition_ID = calloc(1, sizeof(RIC_EventTriggerCondition_ID_t)) ;
  assert(dst->ric_eventTriggerCondition_ID != NULL && "Memory exhauested");

  // Event Trigger Condition ID
  // Optional
  // 9.3.21
  // [1 - 65535]
  assert(*src->ev_trigger_id > 0);
  *dst->ric_eventTriggerCondition_ID = *src->ev_trigger_id;

  return dst;
}

static
E2SM_RC_IndicationHeader_Format2_t* cp_ind_hdr_frmt_2(e2sm_rc_ind_hdr_frmt_2_t const* src)
{
  assert(src != NULL); 

  E2SM_RC_IndicationHeader_Format2_t* dst = calloc(1, sizeof(E2SM_RC_IndicationHeader_Format2_t)); 
  assert(dst != NULL && "Memory exhausted");

  // UE ID
  // Mandatory
  // 9.3.10
  dst->ueID = enc_ue_id_asn(&src->ue_id);

  // RIC Insert Style Type
  // Mandatory
  // 9.3.3
  // 6.2.2.2. From common SM
  // RIC Style Type 
  // Integer
  dst->ric_InsertStyle_Type = src->ric_style_type;

  // Insert Indication ID
  // Mandatory
  // 9.3.16
  // [1 - 65535]
  assert(src->ins_ind_id > 0); 
  dst->ric_InsertIndication_ID = src->ins_ind_id;

  return dst;
}

static
E2SM_RC_IndicationHeader_Format3_t* cp_ind_hdr_frmt_3(e2sm_rc_ind_hdr_frmt_3_t const* src)
{
  assert(src != NULL);

  E2SM_RC_IndicationHeader_Format3_t* dst = calloc(1, sizeof(E2SM_RC_IndicationHeader_Format3_t));
  assert(dst != NULL && "Memory exhausted");

  // Event Trigger Condition ID
  // Optional
  // 9.3.21
  // [1 - 65535]
  if(src->ev_trigger_cond != NULL) {
    assert(*src->ev_trigger_cond > 0);
    
    dst->ric_eventTriggerCondition_ID = calloc(1, sizeof(RIC_EventTriggerCondition_ID_t));
    assert(dst->ric_eventTriggerCondition_ID != NULL && "Memory exhausted" );
   
    *dst->ric_eventTriggerCondition_ID = *src->ev_trigger_cond;
  }

  // UE ID
  // Optional 
  // 9.3.10
  if(src->ue_id != NULL){
    dst->ueID = calloc(1, sizeof(UEID_t));
    assert(dst->ueID != NULL && "Memory exhausted");

    *dst->ueID = enc_ue_id_asn(src->ue_id);
  } 

  return dst;
}





byte_array_t rc_enc_ind_hdr_asn(e2sm_rc_ind_hdr_t const* src)
{
  assert(src != NULL);

  E2SM_RC_IndicationHeader_t dst = {0};
  defer({  ASN_STRUCT_RESET( asn_DEF_E2SM_RC_IndicationHeader, &dst); });

  if(src->format == FORMAT_1_E2SM_RC_IND_HDR ){
    dst.ric_indicationHeader_formats.present = E2SM_RC_IndicationHeader__ric_indicationHeader_formats_PR_indicationHeader_Format1;
    dst.ric_indicationHeader_formats.choice.indicationHeader_Format1 = cp_ind_hdr_frmt_1(&src->frmt_1);
  } else if(src->format == FORMAT_2_E2SM_RC_IND_HDR ){
    dst.ric_indicationHeader_formats.present = E2SM_RC_IndicationHeader__ric_indicationHeader_formats_PR_indicationHeader_Format2;
    dst.ric_indicationHeader_formats.choice.indicationHeader_Format2 = cp_ind_hdr_frmt_2(&src->frmt_2);
  }else if(src->format == FORMAT_3_E2SM_RC_IND_HDR ){
    dst.ric_indicationHeader_formats.present = E2SM_RC_IndicationHeader__ric_indicationHeader_formats_PR_indicationHeader_Format3;
    dst.ric_indicationHeader_formats.choice.indicationHeader_Format3 = cp_ind_hdr_frmt_3(&src->frmt_3);

  }else {
    assert( 0!=0 && "unknown format type");
  }

  xer_fprint(stdout, &asn_DEF_E2SM_RC_IndicationHeader, &dst);
  fflush(stdout);

  byte_array_t ba = {.buf = malloc(1024), .len = 1024};
  const enum asn_transfer_syntax syntax = ATS_ALIGNED_BASIC_PER;
  asn_enc_rval_t er = asn_encode_to_buffer(NULL, syntax, &asn_DEF_E2SM_RC_IndicationHeader, &dst, ba.buf, ba.len);
  assert(er.encoded > -1 && (size_t)er.encoded <= ba.len);
  ba.len = er.encoded;

  return ba;
}

static
E2SM_RC_IndicationMessage_Format1_Item_t* enc_ind_msg_frmt_1_it(seq_ran_param_t const* src)
{
  assert(src != NULL);

  E2SM_RC_IndicationMessage_Format1_Item_t* dst = calloc(1, sizeof( E2SM_RC_IndicationMessage_Format1_Item_t ));
  assert(dst != NULL && "memory exhausted");

  //RAN Parameter ID
  //Mandatory
  //9.3.8
  // [1 - 4294967295]
  assert(src->ran_param_id > 0);
  dst->ranParameter_ID = src->ran_param_id;

  // RAN Parameter Value Type
  // 9.3.11
  // Mandatory
  dst->ranParameter_valueType = cp_ran_param_value_type(&src->ran_param_val);

  return dst;
}


static
E2SM_RC_IndicationMessage_Format1_t* enc_ind_msg_frmt_1(e2sm_rc_ind_msg_frmt_1_t const* src) 
{
  assert(src != NULL);

  E2SM_RC_IndicationMessage_Format1_t* dst = calloc(1, sizeof(E2SM_RC_IndicationMessage_Format1_t  ));
  assert(dst != NULL && "Memorye exhausted");

  //  Sequence of RAN
  //  Parameters
  //  [1 - 65535]
  assert(src->sz_seq_ran_param > 0 && src->sz_seq_ran_param < 65535+1);

  for(size_t i = 0; i <  src->sz_seq_ran_param; ++i){
    E2SM_RC_IndicationMessage_Format1_Item_t* ie = enc_ind_msg_frmt_1_it(&src->seq_ran_param[i]);
    int rc = ASN_SEQUENCE_ADD(&dst->ranP_Reported_List.list, ie);
    assert(rc == 0);
  }

  return dst;
}


byte_array_t rc_enc_ind_msg_asn(e2sm_rc_ind_msg_t const* src)
{
  assert(src != NULL);
  E2SM_RC_IndicationMessage_t dst = {0};
  defer({  ASN_STRUCT_RESET( asn_DEF_E2SM_RC_IndicationMessage, &dst); });

  if(src->format == FORMAT_1_E2SM_RC_IND_MSG ){
    dst.ric_indicationMessage_formats.present = E2SM_RC_IndicationMessage__ric_indicationMessage_formats_PR_indicationMessage_Format1;
    dst.ric_indicationMessage_formats.choice.indicationMessage_Format1 = enc_ind_msg_frmt_1(&src->frmt_1) ;
  } else if(src->format == FORMAT_2_E2SM_RC_IND_MSG){
    dst.ric_indicationMessage_formats.present =E2SM_RC_IndicationMessage__ric_indicationMessage_formats_PR_indicationMessage_Format2;
    assert(0!=0 && "Not implemented");
  } else if(src->format == FORMAT_3_E2SM_RC_IND_MSG){
    dst.ric_indicationMessage_formats.present = E2SM_RC_IndicationMessage__ric_indicationMessage_formats_PR_indicationMessage_Format3;
    assert(0!=0 && "Not implemented");

  } else if(src->format == FORMAT_4_E2SM_RC_IND_MSG){
    dst.ric_indicationMessage_formats.present = E2SM_RC_IndicationMessage__ric_indicationMessage_formats_PR_indicationMessage_Format4;
    assert(0!=0 && "Not implemented");

  } else if(src->format == FORMAT_5_E2SM_RC_IND_MSG){
    dst.ric_indicationMessage_formats.present = E2SM_RC_IndicationMessage__ric_indicationMessage_formats_PR_indicationMessage_Format5;
    assert(0!=0 && "Not implemented");

  } else if(src->format == FORMAT_6_E2SM_RC_IND_MSG){
    dst.ric_indicationMessage_formats.present = E2SM_RC_IndicationMessage__ric_indicationMessage_formats_PR_indicationMessage_Format6;
    assert(0!=0 && "Not implemented");

  } else {
    assert(0!=0 && "Unknown format type");
  }

  xer_fprint(stdout, &asn_DEF_E2SM_RC_IndicationMessage, &dst);
  fflush(stdout);

  byte_array_t ba = {.buf = malloc(1024), .len = 1024};
  const enum asn_transfer_syntax syntax = ATS_ALIGNED_BASIC_PER;
  asn_enc_rval_t er = asn_encode_to_buffer(NULL, syntax, &asn_DEF_E2SM_RC_IndicationMessage, &dst, ba.buf, ba.len);
  assert(er.encoded > -1 && (size_t)er.encoded <= ba.len);
  ba.len = er.encoded;

  return ba;
}


byte_array_t rc_enc_call_proc_id_asn(rc_call_proc_id_t const* call_proc_id)
{
  assert(0!=0 && "Not implemented");

  assert(call_proc_id != NULL);
  byte_array_t  ba = {0};
  return ba;
}

byte_array_t rc_enc_ctrl_hdr_asn(rc_ctrl_hdr_t const* ctrl_hdr)
{
  assert(0!=0 && "Not implemented");

  assert(ctrl_hdr != NULL);
  byte_array_t  ba = {0};
  return ba;
}

byte_array_t rc_enc_ctrl_msg_asn(rc_ctrl_msg_t const* ctrl_msg)
{
  assert(0!=0 && "Not implemented");

  assert(ctrl_msg != NULL);
  byte_array_t  ba = {0};
  return ba;
}

byte_array_t rc_enc_ctrl_out_asn(rc_ctrl_out_t const* ctrl) 
{
  assert(0!=0 && "Not implemented");

  assert( ctrl != NULL );
  byte_array_t  ba = {0};
  return ba;
}

byte_array_t rc_enc_func_def_asn(rc_func_def_t const* func)
{
  assert(0!=0 && "Not implemented");

  assert(func != NULL);
  byte_array_t  ba = {0};
  return ba;
}

