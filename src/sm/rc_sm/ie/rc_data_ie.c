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

bool eq_e2sm_rc_event_trigger(e2sm_rc_event_trigger_t const* m0, e2sm_rc_event_trigger_t const* m1)
{
  if(m0 == m1)
    return true;

  if(m0 == NULL || m1 == NULL)
    return false;

  if(m0->format == FORMAT_1_E2SM_RC_EV_TRIGGER_FORMAT){
    return eq_e2sm_rc_ev_trg_frmt_1(&m0->frmt_1, &m1->frmt_1);

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


e2sm_rc_event_trigger_t cp_e2sm_rc_event_trigger(e2sm_rc_event_trigger_t const* src)
{
  assert(src != NULL);

  e2sm_rc_event_trigger_t dst = {.format = src->format};

  if(src->format == FORMAT_1_E2SM_RC_EV_TRIGGER_FORMAT){
    dst.frmt_1 = cp_e2sm_rc_ev_trg_frmt_1(&src->frmt_1); 

  } else if(src->format == FORMAT_2_E2SM_RC_EV_TRIGGER_FORMAT){
    dst.frmt_2 = cp_e2sm_rc_ev_trg_frmt_2(&src->frmt_2);

  }else if(src->format == FORMAT_3_E2SM_RC_EV_TRIGGER_FORMAT ){
    dst.frmt_3 = cp_e2sm_rc_ev_trg_frmt_3(&src->frmt_3);

  }else if(src->format == FORMAT_4_E2SM_RC_EV_TRIGGER_FORMAT ){
     dst.frmt_4 = cp_e2sm_rc_ev_trg_frmt_4(&src->frmt_4);

  }else if(src->format == FORMAT_5_E2SM_RC_EV_TRIGGER_FORMAT ){
     dst.frmt_5 = cp_e2sm_rc_ev_trg_frmt_5(&src->frmt_5);

  } else {
    assert(0!=0 && "Not implemented");
  }

  return dst;
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
  e2sm_rc_ind_hdr_t dst = {.format = src->format}; 

  if(src->format == FORMAT_1_E2SM_RC_IND_HDR){
    dst.frmt_1 = cp_e2sm_rc_ind_hdr_frmt_1(&src->frmt_1);
  } else if(src->format == FORMAT_2_E2SM_RC_IND_HDR){
    dst.frmt_2 = cp_e2sm_rc_ind_hdr_frmt_2(&src->frmt_2);
  } else if(src->format == FORMAT_3_E2SM_RC_IND_HDR){
    dst.frmt_3 = cp_e2sm_rc_ind_hdr_frmt_3(&src->frmt_3);
  } else {
    assert(0!=0 && "Unknown type");
  }

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

e2sm_rc_ind_msg_t cp_e2sm_rc_ind_msg(e2sm_rc_ind_msg_t const* src)
{
  assert(src != NULL);

  e2sm_rc_ind_msg_t dst = {.format = src->format}; 

  if(src->format == FORMAT_1_E2SM_RC_IND_MSG){
    dst.frmt_1 = cp_e2sm_rc_ind_msg_frmt_1(&src->frmt_1);
  } else if(src->format == FORMAT_2_E2SM_RC_IND_MSG){
    dst.frmt_2 = cp_e2sm_rc_ind_msg_frmt_2(&src->frmt_2);
  } else if(src->format == FORMAT_3_E2SM_RC_IND_MSG){
     dst.frmt_3 = cp_e2sm_rc_ind_msg_frmt_3(&src->frmt_3);
  } else if(src->format ==  FORMAT_4_E2SM_RC_IND_MSG){
     dst.frmt_4 = cp_e2sm_rc_ind_msg_frmt_4(&src->frmt_4);
  } else if(src->format == FORMAT_5_E2SM_RC_IND_MSG){
     dst.frmt_5 = cp_e2sm_rc_ind_msg_frmt_5(&src->frmt_5);
  } else if(src->format == FORMAT_6_E2SM_RC_IND_MSG){
     dst.frmt_6 = cp_e2sm_rc_ind_msg_frmt_6(&src->frmt_6);
  } else{
    assert(0 != 0 && "Unknown format");
  }

  return dst;
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
    free_e2sm_rc_ctrl_hdr_frmt_2(&src->frmt_2);
  } else {
    assert(0!=0 && "Unknown type");
  }

}

e2sm_rc_ctrl_hdr_t cp_e2sm_rc_ctrl_hdr(e2sm_rc_ctrl_hdr_t const* src)
{
  assert(src != NULL);
  e2sm_rc_ctrl_hdr_t dst = {.format = src->format};

  if(dst.format == FORMAT_1_E2SM_RC_CTRL_HDR){
    dst.frmt_1 = cp_e2sm_rc_ctrl_hdr_frmt_1(&src->frmt_1);
  } else if(dst.format == FORMAT_2_E2SM_RC_CTRL_HDR){
    dst.frmt_2 = cp_e2sm_rc_ctrl_hdr_frmt_2(&src->frmt_2);
  } else{
    assert(0!=0 && "Unknown format type");
  } 

  return dst;
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
    if(eq_e2sm_rc_ctrl_hdr_frmt_2(&m0->frmt_2, &m1->frmt_2) == false)
      return false;
  } else {
    assert(0!=0 && "Unknown type");
  }

  return true;
}


//////////////////////////////////////
// RIC Control Message 
/////////////////////////////////////


void free_e2sm_rc_ctrl_msg(e2sm_rc_ctrl_msg_t* src)
{
  assert(src != NULL);

  if(src->format == FORMAT_1_E2SM_RC_CTRL_MSG){
    free_e2sm_rc_ctrl_msg_frmt_1(&src->frmt_1);
  } else if(src->format == FORMAT_2_E2SM_RC_CTRL_MSG){
    free_e2sm_rc_ctrl_msg_frmt_2(&src->frmt_2);
  } else {
    assert(0 && "Unknown format");
  }

}

e2sm_rc_ctrl_msg_t cp_e2sm_rc_ctrl_msg(e2sm_rc_ctrl_msg_t const* src)
{
  assert(src != NULL);

  e2sm_rc_ctrl_msg_t dst = {.format = src->format};

  if(src->format == FORMAT_1_E2SM_RC_CTRL_MSG){
    dst.frmt_1 = cp_e2sm_rc_ctrl_msg_frmt_1(&src->frmt_1);   
  } else if(src->format ==  FORMAT_2_E2SM_RC_CTRL_MSG){
    dst.frmt_2 = cp_e2sm_rc_ctrl_msg_frmt_2(&src->frmt_2);   
  } else {
    assert(0!=0 && "Unknown format");
  }

  return dst;;
}

bool eq_e2sm_rc_ctrl_msg(e2sm_rc_ctrl_msg_t const* m0, e2sm_rc_ctrl_msg_t const* m1)
{
  if(m0 == m1)
    return true;

  if(m0 == NULL || m1 == NULL)
    return false;

  if(m0->format != m1->format)
    return false;

  if(m0->format == FORMAT_1_E2SM_RC_CTRL_MSG){
    if(eq_e2sm_rc_ctrl_msg_frmt_1(&m0->frmt_1, &m1->frmt_1) == false)
      return false;
  } else if(m0->format == FORMAT_2_E2SM_RC_CTRL_MSG){
    if(eq_e2sm_rc_ctrl_msg_frmt_2(&m0->frmt_2, &m1->frmt_2) == false)
      return false;
  } else {
    assert(0 && "Unknown format");
  }

  return true;
}


//////////////////////////////////////
// RIC Control Outcome 
/////////////////////////////////////

void free_e2sm_rc_ctrl_out(e2sm_rc_ctrl_out_t* src)
{
  assert(src != NULL);

  if(src->format == FORMAT_1_E2SM_RC_CTRL_OUT){
    free_e2sm_rc_ctrl_out_frmt_1(&src->frmt_1);
  } else if(src->format == FORMAT_2_E2SM_RC_CTRL_OUT){
    free_e2sm_rc_ctrl_out_frmt_2(&src->frmt_2);
  } else if(src->format == FORMAT_3_E2SM_RC_CTRL_OUT){
    free_e2sm_rc_ctrl_out_frmt_3(&src->frmt_3);
  } else {
    assert(0!=0 && "Unknown format");
  }

}

e2sm_rc_ctrl_out_t cp_e2sm_rc_ctrl_out(e2sm_rc_ctrl_out_t const* src)
{
  assert(src != NULL);

  e2sm_rc_ctrl_out_t dst = {.format = src->format}; 
  
  if(dst.format == FORMAT_1_E2SM_RC_CTRL_OUT ){
    dst.frmt_1 = cp_e2sm_rc_ctrl_out_frmt_1(&src->frmt_1) ;
  } else if(dst.format ==FORMAT_2_E2SM_RC_CTRL_OUT ){
    dst.frmt_2 = cp_e2sm_rc_ctrl_out_frmt_2(&src->frmt_2);
  } else if(dst.format ==FORMAT_3_E2SM_RC_CTRL_OUT ){
    dst.frmt_3 = cp_e2sm_rc_ctrl_out_frmt_3(&src->frmt_3) ;
  }  else{
    assert(0!=0 && "Unknown format");
  }

  return dst;
}

bool eq_e2sm_rc_ctrl_out(e2sm_rc_ctrl_out_t const* m0, e2sm_rc_ctrl_out_t const* m1)
{
  if(m0 == m1)
    return true;

  if(m0 == NULL || m1 == NULL)
    return false;

  if(m0->format != m1->format)
    return false;

  if(m0->format == FORMAT_1_E2SM_RC_CTRL_OUT){
    if(eq_e2sm_rc_ctrl_out_frmt_1(&m0->frmt_1, &m1->frmt_1) == false )
      return false;
  } else if(m0->format == FORMAT_2_E2SM_RC_CTRL_OUT){
    if(eq_e2sm_rc_ctrl_out_frmt_2(&m0->frmt_2, &m1->frmt_2) == false )
      return false;
  } else if(m0->format == FORMAT_3_E2SM_RC_CTRL_OUT){
    if(eq_e2sm_rc_ctrl_out_frmt_3(&m0->frmt_3, &m1->frmt_3) == false )
      return false;
  } else {
    assert(0!=0 && "Unknown format");
  }

  return true;
}


//////////////////////////////////////
// RAN Function Definition 
/////////////////////////////////////

void free_e2sm_rc_func_def(e2sm_rc_func_def_t* src)
{
  assert(src != NULL);
  //  RAN Function Name
  //  Mandatory
  //  9.3.2
  //  6.2.2.1.
  free_ran_function_name(&src->name);

  // RAN Function Definition for EVENT TRIGGER
  // Optional
  // 9.2.2.2
  assert(src->ev_trig == NULL && "Not implemented");

  // RAN Function Definition for REPORT
  // Optional
  // 9.2.2.3
  assert(src->report == NULL && "Not implemented");

  // RAN Function Definition for INSERT
  // Optional
  // 9.2.2.4
  assert(src->insert == NULL && "Not implemented");

  // RAN Function Definition for CONTROL
  // Optional
  // 9.2.2.5
  assert(src->ctrl == NULL && "Not implemented");

  // RAN Function Definition for POLICY
  // Optional
  // 9.2.2.6
  assert(src->policy == NULL && "Not implemented");

}

e2sm_rc_func_def_t cp_e2sm_rc_func_def(e2sm_rc_func_def_t const* src)
{
  assert(src != NULL);
 
  e2sm_rc_func_def_t dst = {0}; 
  
  //  RAN Function Name
  //  Mandatory
  //  9.3.2
  //  6.2.2.1.
  dst.name = cp_ran_function_name(&src->name);

  // RAN Function Definition for EVENT TRIGGER
  // Optional
  // 9.2.2.2
  assert(src->ev_trig == NULL && "not implemented"); 

  // RAN Function Definition for REPORT
  // Optional
  // 9.2.2.3
  assert(src->report == NULL && "not implemented"); 

  // RAN Function Definition for INSERT
  // Optional
  // 9.2.2.4
  assert(src->insert == NULL && "not implemented"); 

  // RAN Function Definition for CONTROL
  // Optional
  // 9.2.2.5
  assert(src->ctrl == NULL && "not implemented"); 

  // RAN Function Definition for POLICY
  // Optional
  // 9.2.2.6
  assert(src->policy == NULL && "not implemented"); 

  return dst;
}

bool eq_e2sm_rc_func_def(e2sm_rc_func_def_t const* m0, e2sm_rc_func_def_t const* m1)
{
  if(m0 == m1)
    return true;

  if(m0 == NULL || m1 == NULL)
    return false;

  //  RAN Function Name
  //  Mandatory
  //  9.3.2
  //  6.2.2.1.
  if(eq_ran_function_name(&m0->name, &m1->name) == false) 
    return false;

  // RAN Function Definition for EVENT TRIGGER
  // Optional
  // 9.2.2.2
  assert(m0->ev_trig == NULL && "Not implemented");
  assert(m1->ev_trig == NULL && "Not implemented");

  // RAN Function Definition for REPORT
  // Optional
  // 9.2.2.3
  assert(m0->report == NULL && "Not implemented");
  assert(m1->report == NULL && "Not implemented");

  // RAN Function Definition for INSERT
  // Optional
  // 9.2.2.4
  assert(m0->insert == NULL && "Not implemented");
  assert(m1->insert == NULL && "Not implemented");

  // RAN Function Definition for CONTROL
  // Optional
  // 9.2.2.5
  assert(m0->ctrl == NULL && "Not implemented");
  assert(m1->ctrl == NULL && "Not implemented");

  // RAN Function Definition for POLICY
  // Optional
  // 9.2.2.6
  assert(m0->policy == NULL && "Not implemented");
  assert(m1->policy == NULL && "Not implemented");

  return true;
}

///////////////
/// RIC Subscription
///////////////

void free_rc_sub_data(rc_sub_data_t* src)
{
  assert(src != NULL);

  free_e2sm_rc_event_trigger(&src->et);
  if(src->ad != NULL){
    free_e2sm_rc_action_def(src->ad);
    free(src->ad);
  }
}

bool eq_rc_sub_data(rc_sub_data_t const* m0, rc_sub_data_t const* m1)
{
  if(m0 == m1)
    return true;

  if(m0 == NULL || m1 == NULL)
    return false;

  if(eq_e2sm_rc_event_trigger(&m0->et, &m1->et) == false)
    return false;

  if(eq_e2sm_rc_action_def(m0->ad, m1->ad) == false)
    return false;

  return true;
}

rc_sub_data_t cp_rc_sub_data(rc_sub_data_t const* src)
{
  assert(src != NULL);
  rc_sub_data_t dst = {0}; 

  dst.et = cp_e2sm_rc_event_trigger(&src->et);
  if(src->ad != NULL){
    dst.ad = calloc(1, sizeof(e2sm_rc_action_def_t));
    assert(dst.ad != NULL && "Memory exhausted");
    *dst.ad = cp_e2sm_rc_action_def(src->ad); 
  }

  return dst;
}


///////////////
// RIC Indication
///////////////

void free_rc_ind_data(rc_ind_data_t* ind)
{
  assert(ind != NULL);
  
  free_e2sm_rc_ind_hdr(&ind->hdr);
  free_e2sm_rc_ind_msg(&ind->msg);
  if(ind->proc_id != NULL)
    free_e2sm_rc_cpid(ind->proc_id); 
}

bool eq_rc_ind_data(rc_ind_data_t const* m0, rc_ind_data_t const* m1)
{
  if(m0 == m1)
    return true;

  if(m0 == NULL || m1 == NULL)
    return false;

  if(eq_e2sm_rc_ind_hdr(&m0->hdr, &m1->hdr) == false)
    return false;

  if(eq_e2sm_rc_ind_msg(&m0->msg, &m1->msg) == false)
    return false;

  if(eq_e2sm_rc_cpid(m0->proc_id, m1->proc_id) == false)
    return false;

  return true;
}


rc_ind_data_t cp_rc_ind_data(rc_ind_data_t const* src)
{
  assert(src != NULL);
  rc_ind_data_t dst = {0};

  dst.hdr = cp_e2sm_rc_ind_hdr(&src->hdr);
  dst.msg = cp_e2sm_rc_ind_msg(&src->msg);

  if(src->proc_id != NULL){
    dst.proc_id = malloc(sizeof(e2sm_rc_cpid_t));
    assert(dst.proc_id != NULL && "Memory exhausted");
    *dst.proc_id = cp_e2sm_rc_cpid(src->proc_id);
  }

  return dst;
}


///////////////
// RIC Control
///////////////

void free_rc_ctrl_req_data(rc_ctrl_req_data_t* src)
{
  assert(src != NULL);

  free_e2sm_rc_ctrl_hdr(&src->hdr);
  free_e2sm_rc_ctrl_msg(&src->msg);
}

bool eq_rc_ctrl_req_data(rc_ctrl_req_data_t const* m0, rc_ctrl_req_data_t  const* m1)
{
  if(m0 == m1)
    return true;

  if(m0 == NULL || m1 == NULL)
    return false;

  if(eq_e2sm_rc_ctrl_hdr(&m0->hdr, &m1->hdr) == false)
    return false;

  if(eq_e2sm_rc_ctrl_msg(&m0->msg, &m1->msg ) == false)
    return false;

  return true;
}

rc_ctrl_req_data_t cp_rc_ctrl_req_data(rc_ctrl_req_data_t const* src)
{
  assert(src != NULL);
  rc_ctrl_req_data_t dst = {0};

  dst.hdr = cp_e2sm_rc_ctrl_hdr(&src->hdr);
  dst.msg = cp_e2sm_rc_ctrl_msg(&src->msg);

  return dst;
}

