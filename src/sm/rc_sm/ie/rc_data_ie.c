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


#include "rc_data_ie.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "ir/e2sm_rc_ev_trg_frmt_1.h"
#include "ir/e2sm_rc_ev_trg_frmt_2.h"
#include "ir/e2sm_rc_ev_trg_frmt_3.h"
#include "ir/e2sm_rc_ev_trg_frmt_4.h"

//////////////////////////////////////
// RIC Event Trigger Definition
/////////////////////////////////////



void free_e2sm_rc_event_trigger(e2sm_rc_event_trigger_t* src)
{
  assert(src != NULL);

  if(src->format == FORMAT_1_E2SM_RC_EV_TRIGGER_FORMAT){
    free_e2sm_rc_ev_trg_frmt_1(&src->frmt_1); 

  } else if(src->format == FORMAT_2_E2SM_RC_EV_TRIGGER_FORMAT ){
    free_e2sm_rc_ev_trg_frmt_2(&src->frmt_2); 

  }else if(src->format == FORMAT_3_E2SM_RC_EV_TRIGGER_FORMAT ){
    free_e2sm_rc_ev_trg_frmt_3(&src->frmt_3); 

  }else if(src->format == FORMAT_4_E2SM_RC_EV_TRIGGER_FORMAT ){
    free_e2sm_rc_ev_trg_frmt_4(&src->frmt_4); 

  }else if(src->format == FORMAT_5_E2SM_RC_EV_TRIGGER_FORMAT ){
    free_e2sm_rc_ev_trg_frmt_5(&src->frmt_5); 

  } else {
    assert(0!=0 && "Not implemented");
  }

}

static
bool eq_e2sm_rc_event_trigger_frmt_1(e2sm_rc_ev_trg_frmt_1_t const* m0, e2sm_rc_ev_trg_frmt_1_t const* m1)
{
  if(m0 == m1)
    return true;

  if(m0 == NULL || m1 == NULL)
    return false;

  // [1 - 65535]
  assert(m0->sz_msg_ev_trg > 0 && m0->sz_msg_ev_trg < 65535 + 1);
  assert(m1->sz_msg_ev_trg > 0 && m1->sz_msg_ev_trg < 65535 + 1);
  assert(m0->msg_ev_trg != NULL);
  assert(m1->msg_ev_trg != NULL);

  if(m0->sz_msg_ev_trg  != m1->sz_msg_ev_trg)
    return false;

  for(size_t i = 0; i < m0->sz_msg_ev_trg; ++i){
    if(eq_msg_ev_trg(&m0->msg_ev_trg[i], &m1->msg_ev_trg[i]) == false)
      return false;
  }

  // Global Associated UE Info
  // Optional
  // 9.3.26
  assert(m0->global_assoc_ue_info == NULL && "Not implemented");
  assert(m1->global_assoc_ue_info == NULL && "Not implemented");

  return true;
}


bool eq_e2sm_rc_event_trigger(e2sm_rc_event_trigger_t const* m0, e2sm_rc_event_trigger_t const* m1)
{
  if(m0 == m1)
    return true;

  if(m0 == NULL || m1 == NULL)
    return false;

  if(m0->format == FORMAT_1_E2SM_RC_EV_TRIGGER_FORMAT){
    return eq_e2sm_rc_event_trigger_frmt_1(&m0->frmt_1, &m1->frmt_1);

  } else if(m0->format == FORMAT_2_E2SM_RC_EV_TRIGGER_FORMAT ){
    return eq_e2sm_rc_ev_trg_frmt_2(&m0->frmt_2, &m1->frmt_2);

  }else if(m0->format == FORMAT_3_E2SM_RC_EV_TRIGGER_FORMAT ){
    return eq_e2sm_rc_ev_trg_frmt_3(&m0->frmt_3, &m1->frmt_3);

  }else if(m0->format == FORMAT_4_E2SM_RC_EV_TRIGGER_FORMAT ){
    return eq_e2sm_rc_ev_trg_frmt_4(&m0->frmt_4, &m1->frmt_4);

  }else if(m0->format == FORMAT_5_E2SM_RC_EV_TRIGGER_FORMAT ){
    return eq_e2sm_rc_ev_trg_frmt_5(&m0->frmt_5, &m1->frmt_5);

  } else {
    assert(0!=0 && "Not implemented");
  }

  assert(0!=0 && "Impossible path");
  return false;
}




/*
e2sm_rc_event_trigger_t cp_rc_event_trigger( rc_event_trigger_t* src)
{
  assert(src != NULL);
  assert(0!=0 && "Not implemented" ); 

  rc_event_trigger_t et = {0};
  return et;
}

bool eq_rc_event_trigger(rc_event_trigger_t* m0, rc_event_trigger_t* m1)
{
  assert(m0 != NULL);
  assert(m1 != NULL);

  assert(0!=0 && "Not implemented" ); 

  return true;
}
*/

//////////////////////////////////////
// RIC Action Definition 
/////////////////////////////////////

void free_e2sm_rc_action_def(e2sm_rc_action_def_t* src)
{
  assert(src != NULL);

  //  RIC Style Type
  //  Mandatory
  //  9.3.3
  // Defined in common 6.2.2.2.
  // uint32_t ric_style_type; 

  if(src->format == FORMAT_1_E2SM_RC_ACT_DEF ){
    free_e2sm_rc_act_def_frmt_1(&src->frmt_1);  
  } else if(src->format ==  FORMAT_2_E2SM_RC_ACT_DEF ){
    free_e2sm_rc_act_def_frmt_2(&src->frmt_2);  
  }else if(src->format ==  FORMAT_3_E2SM_RC_ACT_DEF ){
    free_e2sm_rc_act_def_frmt_3(&src->frmt_3);  
  }else if(src->format ==  FORMAT_4_E2SM_RC_ACT_DEF ){
    free_e2sm_rc_act_def_frmt_4(&src->frmt_4);  
  } else {
    assert("Unknown format" );
  }

}

e2sm_rc_action_def_t cp_e2sm_rc_action_def(e2sm_rc_action_def_t* src)
{
  assert(src != NULL);

  assert(0!=0 && "Not implemented" ); 
  e2sm_rc_action_def_t ad = {0};
  return ad;
}


bool eq_e2sm_rc_action_def(e2sm_rc_action_def_t* m0,  e2sm_rc_action_def_t* m1)
{
  if(m0 == m1)
    return true;

  if(m0 == NULL || m1 == NULL)
    return false;

  if(m0->ric_style_type != m1->ric_style_type)
    return false;

  if(m0->format != m1->format)
    return false;

  if(m0->format == FORMAT_1_E2SM_RC_ACT_DEF){
    return eq_e2sm_rc_act_def_frmt_1(&m0->frmt_1, &m1->frmt_1);
  } else if(m0->format == FORMAT_2_E2SM_RC_ACT_DEF){
    return eq_e2sm_rc_act_def_frmt_2(&m0->frmt_2, &m1->frmt_2);
  } else if(m0->format == FORMAT_3_E2SM_RC_ACT_DEF){
    return eq_e2sm_rc_act_def_frmt_3(&m0->frmt_3, &m1->frmt_3);
  }else if(m0->format == FORMAT_4_E2SM_RC_ACT_DEF ){
    return eq_e2sm_rc_act_def_frmt_4(&m0->frmt_4, &m1->frmt_4);
  } else {
    assert( 0!= 0 && "Unknown format type");
  }

  assert( 0!= 0 && "Impossible path");
  return true;
}


//////////////////////////////////////
// RIC Indication Header 
/////////////////////////////////////


void free_e2sm_rc_ind_hdr(e2sm_rc_ind_hdr_t* src)
{
  assert(src != NULL);
 
  if(src->format == FORMAT_1_E2SM_RC_IND_HDR){
    free_e2sm_rc_ind_hdr_frmt_1(&src->frmt_1);
  } else if(src->format == FORMAT_2_E2SM_RC_IND_HDR){
    free_e2sm_rc_ind_hdr_frmt_2(&src->frmt_2);
  } else if(src->format == FORMAT_3_E2SM_RC_IND_HDR){
    free_e2sm_rc_ind_hdr_frmt_3(&src->frmt_3);
  } else {
    assert(0!=0 && "Unknown type");
  }

}

e2sm_rc_ind_hdr_t cp_e2sm_rc_ind_hdr(e2sm_rc_ind_hdr_t const* src)
{
  assert(src != NULL);
  e2sm_rc_ind_hdr_t dst = {0}; 

  assert(0!=0 && "Not implemented");
  return dst;
}

bool eq_e2sm_rc_ind_hdr(e2sm_rc_ind_hdr_t const* m0, e2sm_rc_ind_hdr_t const* m1)
{

  if(m0 == m1)
    return true;

  if(m0 == NULL || m1 == NULL)
    return false;

  if(m0->format != m1->format)
    return false;

  if(m0->format == FORMAT_1_E2SM_RC_IND_HDR  ){
    return eq_e2sm_rc_ind_hdr_frmt_1(&m0->frmt_1, &m1->frmt_1);
  } else if(m0->format == FORMAT_2_E2SM_RC_IND_HDR ){
    return eq_e2sm_rc_ind_hdr_frmt_2(&m0->frmt_2, &m1->frmt_2);
  }else if(m0->format == FORMAT_3_E2SM_RC_IND_HDR ){
    return eq_e2sm_rc_ind_hdr_frmt_3(&m0->frmt_3, &m1->frmt_3);
  } else {
    assert(0!=0 && "Unknown format");
  }

  assert(0!=0 && "Not implemented");

  return true;
}


//////////////////////////////////////
// RIC Indication Message 
/////////////////////////////////////

void free_e2sm_rc_ind_msg(e2sm_rc_ind_msg_t* src)
{
  assert(src != NULL);

  if(src->format == FORMAT_1_E2SM_RC_IND_MSG){
    free_e2sm_rc_ind_msg_frmt_1(&src->frmt_1);
  } else if(src->format == FORMAT_2_E2SM_RC_IND_MSG){
    free_e2sm_rc_ind_msg_frmt_2(&src->frmt_2);
  } else if(src->format == FORMAT_3_E2SM_RC_IND_MSG){
    free_e2sm_rc_ind_msg_frmt_3(&src->frmt_3);
  } else if(src->format ==  FORMAT_4_E2SM_RC_IND_MSG){
    free_e2sm_rc_ind_msg_frmt_4(&src->frmt_4);
  } else if(src->format == FORMAT_5_E2SM_RC_IND_MSG){
    free_e2sm_rc_ind_msg_frmt_5(&src->frmt_5);
  } else if(src->format == FORMAT_6_E2SM_RC_IND_MSG){
    free_e2sm_rc_ind_msg_frmt_6(&src->frmt_6);
  } else{
    assert(0 != 0 && "Unknown format");
  }


}

e2sm_rc_ind_msg_t cp_rc_ind_msg(e2sm_rc_ind_msg_t const* src)
{
  assert(src != NULL);

  assert(0!=0 && "Not implemented");

  e2sm_rc_ind_msg_t cp = {0}; 

  return cp;
}

bool eq_e2sm_rc_ind_msg(e2sm_rc_ind_msg_t const* m0, e2sm_rc_ind_msg_t const* m1)
{
  if(m0 == m1) 
    return true;

  if(m0 == NULL || m1 == NULL)
    return false;

  if(m0->format != m1->format)
    return false;

  if(m0->format == FORMAT_1_E2SM_RC_IND_MSG ){ 
    return eq_e2sm_rc_ind_msg_frmt_1(&m0->frmt_1, &m1->frmt_1);
  } else if(m0->format == FORMAT_2_E2SM_RC_IND_MSG){
    return eq_e2sm_rc_ind_msg_frmt_2(&m0->frmt_2, &m1->frmt_2);
  }else if(m0->format == FORMAT_3_E2SM_RC_IND_MSG){
    return eq_e2sm_rc_ind_msg_frmt_3(&m0->frmt_3, &m1->frmt_3);
  }else if(m0->format == FORMAT_4_E2SM_RC_IND_MSG){
    return eq_e2sm_rc_ind_msg_frmt_4(&m0->frmt_4, &m1->frmt_4);
  }else if(m0->format ==  FORMAT_5_E2SM_RC_IND_MSG ){
    return eq_e2sm_rc_ind_msg_frmt_5(&m0->frmt_5, &m1->frmt_5);
  }else if(m0->format ==  FORMAT_6_E2SM_RC_IND_MSG ){
    return eq_e2sm_rc_ind_msg_frmt_6(&m0->frmt_6, &m1->frmt_6);
  } else {
    assert(0 != 0 && "Unknown format");
  }

  assert(0 != 0 && "Impossible path");


  return true;
}

//////////////////////////////////////
// RIC Call Process ID
/////////////////////////////////////

void free_e2sm_rc_cpid(e2sm_rc_cpid_t *src) 
{
 // RIC Call Process ID
  // Mandatory
  // 9.3.18
  // [ 1 - 4294967295]
  assert(src->ric_cpid > 0);
  // uint32_t ric_cpid;

}

e2sm_rc_cpid_t cp_e2sm_rc_cpid(e2sm_rc_cpid_t const* src)
{
  assert(src != NULL); 
 
  // RIC Call Process ID
  // Mandatory
  // 9.3.18
  // [ 1 - 4294967295]
  assert(src->ric_cpid > 0);
  
  e2sm_rc_cpid_t dst = { .ric_cpid = src->ric_cpid};
  return dst;
}

bool eq_e2sm_rc_cpid(e2sm_rc_cpid_t const* m0, e2sm_rc_cpid_t const* m1)
{
  if(m0 == m1)
    return true;

  if(m0 == NULL || m1 == NULL)
    return false;

  // RIC Call Process ID
  // Mandatory
  // 9.3.18
  // [ 1 - 4294967295]
  assert(m0->ric_cpid > 0);
  assert(m1->ric_cpid > 0);
  if(m0->ric_cpid != m1->ric_cpid)
    return false;

  return true;
}


//////////////////////////////////////
// RIC Control Header 
/////////////////////////////////////

void free_e2sm_rc_ctrl_hdr(e2sm_rc_ctrl_hdr_t* src)
{
  assert(src != NULL);
  if(src->format == FORMAT_1_E2SM_RC_CTRL_HDR){
    free_e2sm_rc_ctrl_hdr_frmt_1(&src->frmt_1);
  } else if(src->format == FORMAT_2_E2SM_RC_CTRL_HDR ){
    assert(0!=0 && "Not implemented");
  } else {
    assert(0!=0 && "Unknown type");
  }

}

e2sm_rc_ctrl_hdr_t cp_e2sm_rc_ctrl_hdr(e2sm_rc_ctrl_hdr_t* src)
{
  assert(src != NULL);
  assert(0!=0 && "Not implemented" ); 
  e2sm_rc_ctrl_hdr_t ret = {0};
  return ret;
}

bool eq_e2sm_rc_ctrl_hdr(e2sm_rc_ctrl_hdr_t const* m0, e2sm_rc_ctrl_hdr_t const* m1)
{
  if(m0 == m1)
    return true;

  if(m0 == NULL || m1 == NULL)
    return false;

  
  if(m0->format != m1->format)
    return false;

  if(m0->format == FORMAT_1_E2SM_RC_CTRL_HDR){
    if(eq_e2sm_rc_ctrl_hdr_frmt_1(&m0->frmt_1, &m1->frmt_1) == false)
      return false;
  } else if(m0->format == FORMAT_2_E2SM_RC_CTRL_HDR){

    assert(0!=0 && "Not implemented");
  } else {
    assert(0!=0 && "Unknown type");
  }

  return true;
}


//////////////////////////////////////
// RIC Control Message 
/////////////////////////////////////


void free_rc_ctrl_msg( rc_ctrl_msg_t* src)
{
  assert(src != NULL);

  assert(0!=0 && "Not implemented" ); 
}

rc_ctrl_msg_t cp_rc_ctrl_msg(rc_ctrl_msg_t* src)
{
  assert(src != NULL);

  assert(0!=0 && "Not implemented" ); 
  rc_ctrl_msg_t ret = {0};
  return ret;
}

bool eq_rc_ctrl_msg(rc_ctrl_msg_t* m0, rc_ctrl_msg_t* m1)
{
  assert(m0 != NULL);
  assert(m1 != NULL);

  assert(0!=0 && "Not implemented" ); 

  return true;
}


//////////////////////////////////////
// RIC Control Outcome 
/////////////////////////////////////

void free_rc_ctrl_out(rc_ctrl_out_t* src)
{
  assert(src != NULL);

  assert(0!=0 && "Not implemented" ); 
}

rc_ctrl_out_t cp_rc_ctrl_out(rc_ctrl_out_t* src)
{
  assert(src != NULL);

  assert(0!=0 && "Not implemented" ); 
  rc_ctrl_out_t ret = {0}; 
  return ret;
}

bool eq_rc_ctrl_out(rc_ctrl_out_t* m0, rc_ctrl_out_t* m1)
{
  assert(m0 != NULL);
  assert(m1 != NULL);

  assert(0!=0 && "Not implemented" ); 

  return true;
}


//////////////////////////////////////
// RAN Function Definition 
/////////////////////////////////////

void free_rc_func_def( rc_func_def_t* src)
{
  assert(src != NULL);

  assert(0!=0 && "Not implemented" ); 
}

rc_func_def_t cp_rc_func_def(rc_func_def_t* src)
{
  assert(src != NULL);

  assert(0!=0 && "Not implemented" ); 
  rc_func_def_t ret = {0};
  return ret;
}

bool eq_rc_func_def(rc_func_def_t* m0, rc_func_def_t* m1)
{
  assert(m0 != NULL);
  assert(m1 != NULL);

  assert(0!=0 && "Not implemented" ); 
  return true;
}


///////////////
// RIC Indication
///////////////

void free_rc_ind_data(rc_ind_data_t* ind)
{
  assert(ind != NULL);
  
  free_e2sm_rc_ind_hdr(&ind->hdr);
  free_e2sm_rc_ind_msg(&ind->msg);
  free_e2sm_rc_cpid(ind->proc_id); 
}

rc_ind_data_t cp_rc_ind_data(rc_ind_data_t const* src)
{
  assert(src != NULL);
  rc_ind_data_t dst = {0};

  dst.hdr = cp_e2sm_rc_ind_hdr(&src->hdr);
  dst.msg = cp_rc_ind_msg(&src->msg);

  if(src->proc_id != NULL){
    dst.proc_id = malloc(sizeof(e2sm_rc_cpid_t));
    assert(dst.proc_id != NULL && "Memory exhausted");
    *dst.proc_id = cp_e2sm_rc_cpid(src->proc_id);
  }

  return dst;
}


