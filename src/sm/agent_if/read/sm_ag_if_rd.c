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


#include "sm_ag_if_rd.h"
#include "../../mac_sm/ie/mac_data_ie.h"
#include "../../rlc_sm/ie/rlc_data_ie.h"
#include "../../pdcp_sm/ie/pdcp_data_ie.h"
#include "../../slice_sm/ie/slice_data_ie.h"
#include "../../tc_sm/ie/tc_data_ie.h"
#include "../../gtp_sm/ie/gtp_data_ie.h"
#include "../../kpm_sm_v03.00/ie/kpm_data_ie.h"

#include <assert.h>
#include <stdlib.h>

void free_sm_ag_if_rd_ind(sm_ag_if_rd_ind_t* d)
{
  assert(d != NULL);
  
  if(d->type == MAC_STATS_V0){
    free_mac_ind_data(&d->mac_ind);
  } else if(d->type == RLC_STATS_V0){
    free_rlc_ind_data(&d->rlc_ind);
  } else if(d->type == PDCP_STATS_V0){
    free_pdcp_ind_data(&d->pdcp_ind);
  } else if(d->type == SLICE_STATS_V0){
    free_slice_ind_data(&d->slice_ind);
  } else if(d->type == TC_STATS_V0){
    free_tc_ind_data(&d->tc_ind);
  } else if(d->type == GTP_STATS_V0){
    free_gtp_ind_data(&d->gtp_ind);
  } else if(d->type == KPM_STATS_V0){
    free_kpm_ind_data(&d->kpm_ind);
  } else if(d->type == RAN_CTRL_STATS_V1_03 ){
    free_rc_ind_data(&d->rc_ind);
  } else {
    assert(0!=0 && "Unforeseen case");
  }

}

sm_ag_if_rd_ind_t cp_sm_ag_if_rd_ind(sm_ag_if_rd_ind_t const* d)
{
  assert(d != NULL);

  sm_ag_if_rd_ind_t ans = {.type = d->type};

  if(ans.type == MAC_STATS_V0){
    ans.mac_ind = cp_mac_ind_data(&d->mac_ind);
  } else if(ans.type == RLC_STATS_V0 ){
    ans.rlc_ind = cp_rlc_ind_data(&d->rlc_ind);
  } else if(ans.type == PDCP_STATS_V0) {
    ans.pdcp_ind = cp_pdcp_ind_data(&d->pdcp_ind);
  } else if(ans.type == SLICE_STATS_V0) {
    ans.slice_ind = cp_slice_ind_data(&d->slice_ind);
  } else if(ans.type == TC_STATS_V0) {
    ans.tc_ind = cp_tc_ind_data(&d->tc_ind);
  } else if(ans.type == GTP_STATS_V0) {
    ans.gtp_ind = cp_gtp_ind_data(&d->gtp_ind);
  } else if(ans.type == KPM_STATS_V0) {
    ans.kpm_ind = cp_kpm_ind_data(&d->kpm_ind);
  } else if(ans.type == RAN_CTRL_STATS_V1_03) {
    ans.rc_ind = cp_rc_ind_data(&d->rc_ind);
  }  else {
    assert("Unknown type or not implemented");
  }

  return ans;
}

void free_sm_ag_if_rd(sm_ag_if_rd_t* src)
{
  assert(src != NULL);

  if(src->type == INDICATION_MSG_AGENT_IF_ANS_V0){
    free_sm_ag_if_rd_ind(&src->ind);
  } else if(src->type == E2_SETUP_AGENT_IF_ANS_V0){
    assert(0!=0 && "Not implemented ");
  } else if(src->type == RIC_SERV_UPDATE_AGENT_IF_ANS_V0){
    assert(0!=0 && "Not implemented ");
  } else {
    assert(0!=0 && "Unknown type");
  }

}

sm_ag_if_rd_t cp_sm_ag_if_rd(sm_ag_if_rd_t const* src)
{
  assert(src != NULL);
  sm_ag_if_rd_t dst = {.type = src->type}; 

  if(src->type == INDICATION_MSG_AGENT_IF_ANS_V0){
    dst.ind = cp_sm_ag_if_rd_ind(&src->ind);
  } else if(src->type == E2_SETUP_AGENT_IF_ANS_V0){
    assert(0!=0 && "Not implemented ");
  } else if(src->type == RIC_SERV_UPDATE_AGENT_IF_ANS_V0){
    assert(0!=0 && "Not implemented ");
  } else {
    assert(0!=0 && "Unknown type");
  }

  return dst;
}

