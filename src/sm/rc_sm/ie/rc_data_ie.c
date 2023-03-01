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
    assert(0!=0 && "Not implemented");

  } else {
    assert("Unknown format" );
  }

  //9.2.1.2.1
//  e2sm_rc_act_def_frmt_1_t frmt_1;
//  e2sm_rc_act_def_frmt_2_t frmt_2;
//  e2sm_rc_act_def_frmt_3_t frmt_3;
//  e2sm_rc_act_def_frmt_4_t frmt_4;

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

  } else if(m0->format == FORMAT_3_E2SM_RC_ACT_DEF){

  }else if(m0->format == FORMAT_4_E2SM_RC_ACT_DEF ){

  } else {
    assert( 0!= 0 && "Unknown format type");
  }

  return true;
}


//////////////////////////////////////
// RIC Indication Header 
/////////////////////////////////////


void free_rc_ind_hdr(rc_ind_hdr_t* src)
{
  assert(src != NULL);
  (void)src;
}

rc_ind_hdr_t cp_rc_ind_hdr(rc_ind_hdr_t const* src)
{
  assert(src != NULL);
  rc_ind_hdr_t dst = {0}; 
  dst.dummy = src->dummy;
  return dst;
}

bool eq_rc_ind_hdr(rc_ind_hdr_t* m0, rc_ind_hdr_t* m1)
{
  assert(m0 != 0);
  assert(m1 != 0);

  if(m0->dummy != m1->dummy)
    return false;
  return true;
}






//////////////////////////////////////
// RIC Indication Message 
/////////////////////////////////////

void free_rc_ind_msg(rc_ind_msg_t* src)
{
  assert(src != NULL);

  if(src->len > 0){
    assert(src->rb != NULL);
    free(src->rb);
  }
}

rc_ind_msg_t cp_rc_ind_msg(rc_ind_msg_t const* src)
{
  assert(src != NULL);

  rc_ind_msg_t cp = {.len = src->len, .tstamp = src->tstamp}; 

  if(cp.len > 0){
    cp.rb = calloc(cp.len, sizeof(rc_radio_bearer_stats_t));
    assert(cp.rb != NULL && "memory exhausted");
  }

  memcpy(cp.rb, src->rb, sizeof(rc_radio_bearer_stats_t)*cp.len);

  return cp;
}

bool eq_rc_ind_msg(rc_ind_msg_t* m0, rc_ind_msg_t* m1)
{
  assert(m0 != NULL);
  assert(m1 != NULL);

  if(m0->tstamp != m1->tstamp ||
      m0->len != m1->len)
    return false;

  for(uint32_t i =0; i < m0->len; ++i){
 rc_radio_bearer_stats_t const* rb0 = &m0->rb[i];
 rc_radio_bearer_stats_t const* rb1 = &m1->rb[i];
 if(
     rb0->txpdu_pkts != rb1->txpdu_pkts   ||
     rb0->txpdu_bytes != rb1->txpdu_bytes ||  
     rb0->txpdu_wt_ms != rb1->txpdu_wt_ms  ||
     rb0->txpdu_dd_pkts != rb1->txpdu_dd_pkts ||
     rb0->txpdu_dd_bytes != rb1->txpdu_dd_bytes ||
     rb0->txpdu_retx_pkts != rb1->txpdu_retx_pkts ||
     rb0->txpdu_retx_bytes != rb1->txpdu_retx_bytes ||
     rb0->txpdu_segmented != rb1->txpdu_segmented ||
     rb0->txpdu_status_pkts != rb1->txpdu_status_pkts ||
     rb0->txpdu_status_bytes != rb1->txpdu_status_bytes ||
     rb0->txbuf_occ_bytes != rb1-> txbuf_occ_bytes ||
     rb0->txbuf_occ_pkts != rb1->txbuf_occ_pkts ||
     rb0->rxpdu_pkts != rb1->rxpdu_pkts ||
     rb0->rxpdu_bytes != rb1->rxpdu_bytes ||
     rb0->rxpdu_dup_pkts != rb1->rxpdu_dup_pkts ||
     rb0->rxpdu_dup_bytes != rb1->rxpdu_dup_bytes ||
     rb0->rxpdu_dd_pkts != rb1->rxpdu_dd_pkts ||
     rb0->rxpdu_dd_bytes != rb1->rxpdu_dd_bytes ||
     rb0->rxpdu_ow_pkts != rb1->rxpdu_ow_pkts ||
     rb0->rxpdu_ow_bytes != rb1->rxpdu_ow_bytes ||
     rb0->rxpdu_status_pkts != rb1->rxpdu_status_pkts ||
     rb0->rxpdu_status_bytes != rb1->rxpdu_status_bytes ||
     rb0->rxbuf_occ_bytes != rb1->rxbuf_occ_bytes ||
     rb0->rxbuf_occ_pkts != rb1->rxbuf_occ_pkts ||
     rb0->txsdu_pkts != rb1->txsdu_pkts ||
     rb0->txsdu_bytes != rb1->txsdu_bytes ||
     rb0->rxsdu_pkts != rb1->rxsdu_pkts ||
     rb0->rxsdu_bytes != rb1->rxsdu_bytes ||
     rb0->rxsdu_dd_pkts != rb1->rxsdu_dd_pkts ||
     rb0->rxsdu_dd_bytes != rb1->rxsdu_dd_bytes ||
     rb0->rnti != rb1->rnti ||
     rb0->mode != rb1->mode ||
     rb0->rbid != rb1->rbid 
     )
  return false;
  }
    return true;
}

//////////////////////////////////////
// RIC Call Process ID 
/////////////////////////////////////

void free_rc_call_proc_id(rc_call_proc_id_t* src)
{
  // Note that the src could be NULL
  free(src);
}

rc_call_proc_id_t cp_rc_call_proc_id( rc_call_proc_id_t* src)
{
  assert(src != NULL); 
  rc_call_proc_id_t dst = {0};

  dst.dummy = src->dummy;

  return dst;
}

bool eq_rc_call_proc_id(rc_call_proc_id_t* m0, rc_call_proc_id_t* m1)
{
  if(m0 == NULL && m1 == NULL)
    return true;
  if(m0 == NULL)
    return false;
  if(m1 == NULL)
    return false;

  if(m0->dummy != m1->dummy)
    return false;

  return true;
}


//////////////////////////////////////
// RIC Control Header 
/////////////////////////////////////

void free_rc_ctrl_hdr( rc_ctrl_hdr_t* src)
{

  assert(src != NULL);
  assert(0!=0 && "Not implemented" ); 
}

rc_ctrl_hdr_t cp_rc_ctrl_hdr(rc_ctrl_hdr_t* src)
{
  assert(src != NULL);
  assert(0!=0 && "Not implemented" ); 
  rc_ctrl_hdr_t ret = {0};
  return ret;
}

bool eq_rc_ctrl_hdr(rc_ctrl_hdr_t* m0, rc_ctrl_hdr_t* m1)
{
  assert(m0 != NULL);
  assert(m1 != NULL);

  assert(0!=0 && "Not implemented" ); 

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
  
  free_rc_ind_hdr(&ind->hdr);
  free_rc_ind_msg(&ind->msg);
  free_rc_call_proc_id(ind->proc_id); 
}

rc_ind_data_t cp_rc_ind_data(rc_ind_data_t const* src)
{
  assert(src != NULL);
  rc_ind_data_t dst = {0};

  dst.hdr = cp_rc_ind_hdr(&src->hdr);
  dst.msg = cp_rc_ind_msg(&src->msg);

  if(src->proc_id != NULL){
    dst.proc_id = malloc(sizeof(rc_call_proc_id_t));
    assert(dst.proc_id != NULL && "Memory exhausted");
    *dst.proc_id = cp_rc_call_proc_id(src->proc_id);
  }

  return dst;
}


