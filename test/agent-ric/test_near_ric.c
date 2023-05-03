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

#include "../src/ric/near_ric_api.h"
#include "../src/agent/e2_agent_api.h"

#include "../rnd/fill_rnd_data_gtp.h"                  
#include "../rnd/fill_rnd_data_tc.h"                  
#include "../rnd/fill_rnd_data_mac.h"                  
#include "../rnd/fill_rnd_data_rlc.h"                  
#include "../rnd/fill_rnd_data_pdcp.h"                  
#include "../rnd/fill_rnd_data_rc.h"                  
#include "../rnd/fill_rnd_data_tc.h"                  
#include "../rnd/fill_rnd_data_kpm.h"                  
#include "../rnd/fill_rnd_data_slice.h"                  

#include <assert.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

static
pthread_t t;

static
void read_e2_setup_agent(sm_ag_if_rd_e2setup_t* e2ap)
{
  assert(e2ap != NULL);
  assert(e2ap->type == KPM_V3_0_AGENT_IF_E2_SETUP_ANS_V0 || e2ap->type == RAN_CTRL_V1_3_AGENT_IF_E2_SETUP_ANS_V0);
  if(e2ap->type == KPM_V3_0_AGENT_IF_E2_SETUP_ANS_V0 ){
    e2ap->kpm.ran_func_def = fill_kpm_ran_func_def(); 
  } else if(e2ap->type == RAN_CTRL_V1_3_AGENT_IF_E2_SETUP_ANS_V0 ){
    e2ap->rc.ran_func_def = fill_rc_ran_func_def();
  } else {
    assert(0 != 0 && "Unknown type");
  }
}

static
void read_ind_agent(sm_ag_if_rd_ind_t* ind)
{
  assert(ind != NULL);
  if(ind->type == MAC_STATS_V0){
    fill_mac_ind_data(&ind->mac);
  } else if(ind->type == RLC_STATS_V0){
    fill_rlc_ind_data(&ind->rlc);
  } else if (ind->type == PDCP_STATS_V0){
    fill_pdcp_ind_data(&ind->pdcp);
  } else if(ind->type == SLICE_STATS_V0){
    fill_slice_ind_data(&ind->slice);
  } else if(ind->type == GTP_STATS_V0){
    fill_gtp_ind_data(&ind->gtp);
  } else if(ind->type == TC_STATS_V0){
    fill_tc_ind_data(&ind->tc);
  } else if(ind->type == KPM_STATS_V3_0){
    ind->kpm.ind.hdr = fill_kpm_ind_hdr();
    ind->kpm.ind.msg = fill_kpm_ind_msg();
  } else if(ind->type == RAN_CTRL_STATS_V1_03){
    assert(0!=0 && "The logic in RAN Ctrl SM is different!"); 
  } else {
    assert(0!=0 && "Unknown type");
  } 
}

static
void read_RAN(sm_ag_if_rd_t* ag_rd)
{
  assert(ag_rd != NULL);
  assert(ag_rd->type == INDICATION_MSG_AGENT_IF_ANS_V0 || E2_SETUP_AGENT_IF_ANS_V0 );

  if(ag_rd->type == E2_SETUP_AGENT_IF_ANS_V0){
    read_e2_setup_agent(&ag_rd->e2ap);
  } else if(ag_rd->type == INDICATION_MSG_AGENT_IF_ANS_V0 ){
    read_ind_agent(&ag_rd->ind);
  } else {
    assert(0!=0 && "Unknown type");
  }
}

static
sm_ag_if_ans_t write_RAN_ctrl(sm_ag_if_wr_ctrl_t const* ctrl)
{
  assert(ctrl != NULL);
  if(ctrl->type == MAC_CTRL_REQ_V0){
    //printf("Control message called in the RAN \n");
    sm_ag_if_ans_t ans = {.type = CTRL_OUTCOME_SM_AG_IF_ANS_V0};
    ans.ctrl_out.type = MAC_AGENT_IF_CTRL_ANS_V0;
    ans.ctrl_out.mac.ans = MAC_CTRL_OUT_OK;
    return ans;
  } else if(ctrl->type == RAN_CONTROL_CTRL_V1_03){
    printf("RAN_CONTROL_CTRL_V1_03 message called in the RAN \n");

    sm_ag_if_ans_t ans = {.type = CTRL_OUTCOME_SM_AG_IF_ANS_V0};
    ans.ctrl_out.type = RAN_CTRL_V1_3_AGENT_IF_CTRL_ANS_V0;
    ans.ctrl_out.rc = fill_rnd_rc_ctrl_out();
    return ans;

  } else {
    assert(0 != 0 && "Not supported function ");
  }

  sm_ag_if_ans_t ans = {0};
  return ans;
}

static
void* emulate_rrc_msg(void* ptr)
{
  uint32_t* ric_id = (uint32_t*)ptr; 
  for(size_t i = 0; i < 5; ++i){
    usleep(rand()%4000);
    rc_ind_data_t* d = calloc(1, sizeof(rc_ind_data_t)); 
    assert(d != NULL && "Memory exhausted");
    *d = fill_rnd_rc_ind_data();
    async_event_agent_api(*ric_id, d);
    printf("Event for RIC Req ID %u generated\n", *ric_id);
  }

  free(ptr);
  return NULL;
}

static
void write_RAN_subs_rc(wr_rc_sub_data_t const* wr_rc)
{
  assert(wr_rc != NULL);

  printf("ric req id %d \n", wr_rc->ric_req_id);

  uint32_t* ptr = malloc(sizeof(uint32_t));
  assert(ptr != NULL);
  *ptr = wr_rc->ric_req_id;

  int rc = pthread_create(&t, NULL, emulate_rrc_msg, ptr);
  assert(rc == 0);
}

static
sm_ag_if_ans_t write_RAN_subs(sm_ag_if_wr_subs_t const* subs)
{
  assert(subs != NULL);
  
  if(subs->type == RAN_CTRL_SUBS_V1_03){
    write_RAN_subs_rc(&subs->wr_rc);
  } else {
    assert(0!=0 && "Unknown type");
  }

  sm_ag_if_ans_t ans = {0};
  return ans;
}

static
sm_ag_if_ans_t write_RAN(sm_ag_if_wr_t const* ag_wr)
{
  assert(ag_wr != NULL);
  assert(ag_wr->type == CONTROL_SM_AG_IF_WR
      || ag_wr->type == SUBSCRIPTION_SM_AG_IF_WR);

  if(ag_wr->type == CONTROL_SM_AG_IF_WR){
    return write_RAN_ctrl(&ag_wr->ctrl);
  } else if(ag_wr->type == SUBSCRIPTION_SM_AG_IF_WR){
    return write_RAN_subs(&ag_wr->subs);
  } else {
    assert(0!=0 && "Unknown type");
  }

  assert(0!=0 && "This point should not be reached");
  sm_ag_if_ans_t ans = {0};
  return ans;
}

int main(int argc, char *argv[])
{
  // Init the Agent
  const int mcc = 208; 
  const int mnc = 92; 
  const int mnc_digit_len = 2;
  const int nb_id = 42;
  const int cu_du_id = 0;
  ngran_node_t ran_type = ngran_gNB;
  sm_io_ag_t io = {.read = read_RAN, .write = write_RAN};
  fr_args_t args = init_fr_args(argc, argv);
  // Parse arguments
  init_agent_api( mcc, mnc, mnc_digit_len, nb_id, cu_du_id, ran_type, io, &args);
  sleep(1);

  // Init the RIC
  init_near_ric_api(&args);
  sleep(3);

  e2_nodes_api_t e2_nodes = e2_nodes_near_ric_api();
  assert(e2_nodes.len > 0 && "No E2 Nodes connected");

  global_e2_node_id_t const* id = &e2_nodes.n[0].id;

  const uint16_t MAC_ran_func_id = 142;
  char* cmd = "5_ms";
  uint16_t h = report_service_near_ric_api(id, MAC_ran_func_id, cmd );

  const uint16_t RLC_ran_func_id = 143;
  uint16_t h2 = report_service_near_ric_api(id, RLC_ran_func_id, cmd);

  const uint16_t PDCP_ran_func_id = 144;
  uint16_t h3 = report_service_near_ric_api(id, PDCP_ran_func_id, cmd);

  const uint16_t SLICE_ran_func_id = 145;
  uint16_t h4 = report_service_near_ric_api(id, SLICE_ran_func_id, cmd);

  const uint16_t TC_ran_func_id = 146;
  uint16_t h5 = report_service_near_ric_api(id, TC_ran_func_id, cmd);

  const uint16_t GTP_ran_func_id = 148;
  uint16_t h6 = report_service_near_ric_api(id, GTP_ran_func_id, cmd);
  const uint16_t KPM_ran_func_id = 2;
  kpm_sub_data_t kpm_sub = {.ev_trg_def.type = FORMAT_1_RIC_EVENT_TRIGGER,
                            .ev_trg_def.kpm_ric_event_trigger_format_1.report_period_ms = 5};
  // [1-16]
  kpm_sub.sz_ad = 1;
  kpm_sub.ad = calloc(kpm_sub.sz_ad, sizeof(kpm_act_def_t));
  assert(kpm_sub.ad != NULL && "Memory exhausted");
 
  kpm_sub.ad[0] = fill_kpm_action_def();

  const uint16_t h7 = report_service_near_ric_api(id, KPM_ran_func_id, &kpm_sub);


  /// RAN Control Indication 
  
  const uint16_t RC_ran_func_id = 3;

  rc_sub_data_t rc_sub = {0};
  rc_sub.et = fill_rnd_rc_event_trigger();

 // [1-16]
  rc_sub.sz_ad = 1;
  rc_sub.ad = calloc(rc_sub.sz_ad, sizeof(e2sm_rc_action_def_t));
  assert(rc_sub.ad != NULL && "Memory exhausted");
 
  rc_sub.ad[0] = fill_rnd_rc_action_def();

  const uint16_t h8 = report_service_near_ric_api(id, RC_ran_func_id, &rc_sub);

  /// RAN Control Control 
  rc_ctrl_req_data_t rc_ctrl = fill_rc_ctrl();

  control_service_near_ric_api(id, RC_ran_func_id, &rc_ctrl);

  sleep(10);

  rm_report_service_near_ric_api(id, MAC_ran_func_id, h);
  rm_report_service_near_ric_api(id, RLC_ran_func_id, h2);
  rm_report_service_near_ric_api(id, PDCP_ran_func_id, h3);
  rm_report_service_near_ric_api(id, SLICE_ran_func_id, h4);
  rm_report_service_near_ric_api(id, TC_ran_func_id, h5);
  rm_report_service_near_ric_api(id, GTP_ran_func_id, h6);
  rm_report_service_near_ric_api(id, KPM_ran_func_id, h7);
  rm_report_service_near_ric_api(id, RC_ran_func_id, h8);

  sleep(1);

  // Stop the Agent
  stop_agent_api();

  // Stop the RIC
  stop_near_ric_api();

  free_kpm_sub_data(&kpm_sub); 
  free_rc_sub_data(&rc_sub); 
  free_rc_ctrl_req_data(&rc_ctrl);

  free_e2_nodes_api(&e2_nodes); // e2_nodes_api_t* src);

  int rc = pthread_join(t, NULL);
  assert(rc == 0);

  printf("Test communicating E2-Agent and Near-RIC run SUCCESSFULLY\n");

}
