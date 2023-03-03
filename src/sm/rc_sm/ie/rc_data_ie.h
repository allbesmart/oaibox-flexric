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

#ifndef RC_DATA_INFORMATION_ELEMENTS_H
#define RC_DATA_INFORMATION_ELEMENTS_H

#ifdef __cplusplus
extern "C" {
#endif

/*
 * 9 Information Elements (IE) , RIC Event Trigger Definition, RIC Action Definition, RIC Indication Header, RIC Indication Message, RIC Call Process ID, RIC Control Header, RIC Control Message, RIC Control Outcome and RAN Function Definition defined by ORAN-WG3.E2SM-v01.00.00 at Section 5
 */

#include <stdbool.h>
#include <stdint.h>



//////////////////////////////////////
// RIC Event Trigger Definition
/////////////////////////////////////

#include "ir/e2sm_rc_ev_trg_frmt_1.h"
#include "ir/e2sm_rc_ev_trg_frmt_2.h"
#include "ir/e2sm_rc_ev_trg_frmt_3.h"
#include "ir/e2sm_rc_ev_trg_frmt_4.h"
#include "ir/e2sm_rc_ev_trg_frmt_5.h"


//////////////////////////////////////
// RIC Action Definition 
/////////////////////////////////////

#include "ir/e2sm_rc_act_def_frmt_1.h"
#include "ir/e2sm_rc_act_def_frmt_2.h"
#include "ir/e2sm_rc_act_def_frmt_3.h"
#include "ir/e2sm_rc_act_def_frmt_4.h"


/////////////////////////////////////
// RIC Indication Header 
/////////////////////////////////////

#include "ir/e2sm_rc_ind_hdr_frmt_1.h"
#include "ir/e2sm_rc_ind_hdr_frmt_2.h"
#include "ir/e2sm_rc_ind_hdr_frmt_3.h"


//////////////////////////////////////
// RIC Event Trigger Definition
/////////////////////////////////////

typedef enum{
  FORMAT_1_E2SM_RC_EV_TRIGGER_FORMAT ,
  FORMAT_2_E2SM_RC_EV_TRIGGER_FORMAT ,
  FORMAT_3_E2SM_RC_EV_TRIGGER_FORMAT ,
  FORMAT_4_E2SM_RC_EV_TRIGGER_FORMAT ,
  FORMAT_5_E2SM_RC_EV_TRIGGER_FORMAT ,

  END_E2SM_RC_EV_TRIGGER_FORMAT
} e2sm_rc_ev_trigger_format_e ;



typedef struct {
  e2sm_rc_ev_trigger_format_e format;
  union{
    e2sm_rc_ev_trg_frmt_1_t frmt_1;     
    e2sm_rc_ev_trg_frmt_2_t frmt_2;     
    e2sm_rc_ev_trg_frmt_3_t frmt_3;     
    e2sm_rc_ev_trg_frmt_4_t frmt_4;     
    e2sm_rc_ev_trg_frmt_5_t frmt_5;     
  };

} e2sm_rc_event_trigger_t;

void free_e2sm_rc_event_trigger(e2sm_rc_event_trigger_t* src); 

e2sm_rc_event_trigger_t cp_e2sm_rc_event_trigger( e2sm_rc_event_trigger_t* src);

bool eq_e2sm_rc_event_trigger(e2sm_rc_event_trigger_t const* m0, e2sm_rc_event_trigger_t const* m1);
     


//////////////////////////////////////
// RIC Action Definition 
/////////////////////////////////////

typedef enum{
  FORMAT_1_E2SM_RC_ACT_DEF ,
  FORMAT_2_E2SM_RC_ACT_DEF ,
  FORMAT_3_E2SM_RC_ACT_DEF ,
  FORMAT_4_E2SM_RC_ACT_DEF ,

  END_E2SM_RC_ACT_DEF

} e2sm_rc_act_def_format_e; 

typedef struct {
  //  RIC Style Type
  //  Mandatory
  //  9.3.3
  // Defined in common 6.2.2.2.
  uint32_t ric_style_type; 

  e2sm_rc_act_def_format_e format;
  union{
  //9.2.1.2.1
  e2sm_rc_act_def_frmt_1_t frmt_1;
  e2sm_rc_act_def_frmt_2_t frmt_2;
  e2sm_rc_act_def_frmt_3_t frmt_3;
  e2sm_rc_act_def_frmt_4_t frmt_4;
  };
} e2sm_rc_action_def_t;

void free_e2sm_rc_action_def(e2sm_rc_action_def_t* src); 

e2sm_rc_action_def_t cp_e2sm_rc_action_def(e2sm_rc_action_def_t* src);

bool eq_e2sm_rc_action_def(e2sm_rc_action_def_t* m0,  e2sm_rc_action_def_t* m1);



//////////////////////////////////////
// RIC Indication Header 
/////////////////////////////////////

typedef enum{
  FORMAT_1_E2SM_RC_IND_HDR ,
  FORMAT_2_E2SM_RC_IND_HDR ,
  FORMAT_3_E2SM_RC_IND_HDR ,

  END_E2SM_RC_IND_HDR

} e2sm_rc_ind_hdr_format_e; 

typedef struct{
  e2sm_rc_ind_hdr_format_e format;
  union{
    e2sm_rc_ind_hdr_frmt_1_t frmt_1; // 9.2.1.3.1
    e2sm_rc_ind_hdr_frmt_2_t frmt_2; // 9.2.1.3.1
    e2sm_rc_ind_hdr_frmt_3_t frmt_3; // 9.2.1.3.1
  };
} e2sm_rc_ind_hdr_t;

void free_e2sm_rc_ind_hdr(e2sm_rc_ind_hdr_t* src); 

e2sm_rc_ind_hdr_t cp_e2sm_rc_ind_hdr(e2sm_rc_ind_hdr_t const* src);

bool eq_e2sm_rc_ind_hdr(e2sm_rc_ind_hdr_t const* m0, e2sm_rc_ind_hdr_t const* m1);


//////////////////////////////////////
// RIC Indication Message 
/////////////////////////////////////

typedef struct {
  /* PDU stats */
  /* TX */
  uint32_t txpdu_pkts;         /* aggregated number of transmitted RC PDUs */
  uint32_t txpdu_bytes;        /* aggregated amount of transmitted bytes in RC PDUs */
  /* TODO? */
  uint32_t txpdu_wt_ms;      /* aggregated head-of-line tx packet waiting time to be transmitted (i.e. send to the MAC layer) */
  uint32_t txpdu_dd_pkts;      /* aggregated number of dropped or discarded tx packets by RC */
  uint32_t txpdu_dd_bytes;     /* aggregated amount of bytes dropped or discarded tx packets by RC */
  uint32_t txpdu_retx_pkts;    /* aggregated number of tx pdus/pkts to be re-transmitted (only applicable to RC AM) */
  uint32_t txpdu_retx_bytes;   /* aggregated amount of bytes to be re-transmitted (only applicable to RC AM) */
  uint32_t txpdu_segmented;    /* aggregated number of segmentations */
  uint32_t txpdu_status_pkts;  /* aggregated number of tx status pdus/pkts (only applicable to RC AM) */
  uint32_t txpdu_status_bytes; /* aggregated amount of tx status bytes  (only applicable to RC AM) */
  /* TODO? */
  uint32_t txbuf_occ_bytes;    /* current tx buffer occupancy in terms of amount of bytes (average: NOT IMPLEMENTED) */
  /* TODO? */
  uint32_t txbuf_occ_pkts;     /* current tx buffer occupancy in terms of number of packets (average: NOT IMPLEMENTED) */
  /* txbuf_wd_ms: the time window for which the txbuf  occupancy value is obtained - NOT IMPLEMENTED */

  /* RX */
  uint32_t rxpdu_pkts;         /* aggregated number of received RC PDUs */
  uint32_t rxpdu_bytes;        /* amount of bytes received by the RC */
  uint32_t rxpdu_dup_pkts;     /* aggregated number of duplicate packets */
  uint32_t rxpdu_dup_bytes;    /* aggregated amount of duplicated bytes */
  uint32_t rxpdu_dd_pkts;      /* aggregated number of rx packets dropped or discarded by RC */
  uint32_t rxpdu_dd_bytes;     /* aggregated amount of rx bytes dropped or discarded by RC */
  uint32_t rxpdu_ow_pkts;      /* aggregated number of out of window received RC pdu */
  uint32_t rxpdu_ow_bytes;     /* aggregated number of out of window bytes received RC pdu */
  uint32_t rxpdu_status_pkts;  /* aggregated number of rx status pdus/pkts (only applicable to RC AM) */
  uint32_t rxpdu_status_bytes; /* aggregated amount of rx status bytes  (only applicable to RC AM) */
  /* rxpdu_rotout_ms: flag indicating rx reordering  timeout in ms - NOT IMPLEMENTED */
  /* rxpdu_potout_ms: flag indicating the poll retransmit time out in ms - NOT IMPLEMENTED */
  /* rxpdu_sptout_ms: flag indicating status prohibit timeout in ms - NOT IMPLEMENTED */
  /* TODO? */
  uint32_t rxbuf_occ_bytes;    /* current rx buffer occupancy in terms of amount of bytes (average: NOT IMPLEMENTED) */
  /* TODO? */
  uint32_t rxbuf_occ_pkts;     /* current rx buffer occupancy in terms of number of packets (average: NOT IMPLEMENTED) */

  /* SDU stats */
  /* TX */
  uint32_t txsdu_pkts;         /* number of SDUs delivered */
  uint32_t txsdu_bytes;        /* number of bytes of SDUs delivered */

  /* RX */
  uint32_t rxsdu_pkts;         /* number of SDUs received */
  uint32_t rxsdu_bytes;        /* number of bytes of SDUs received */
  uint32_t rxsdu_dd_pkts;      /* number of dropped or discarded SDUs */
  uint32_t rxsdu_dd_bytes;     /* number of bytes of SDUs dropped or discarded */

  uint32_t rnti;
  uint8_t mode;               /* 0: RC AM, 1: RC UM, 2: RC TM */
  uint8_t rbid;

} rc_radio_bearer_stats_t;

typedef struct {
  rc_radio_bearer_stats_t* rb; 
  uint32_t len;

  int64_t tstamp;
} rc_ind_msg_t;

void free_rc_ind_msg(rc_ind_msg_t* src); 

rc_ind_msg_t cp_rc_ind_msg(rc_ind_msg_t const* src);

bool eq_rc_ind_msg(rc_ind_msg_t* m0, rc_ind_msg_t* m1);


//////////////////////////////////////
// RIC Call Process ID 
/////////////////////////////////////

typedef struct {
  uint32_t dummy;
} rc_call_proc_id_t;

void free_rc_call_proc_id( rc_call_proc_id_t* src); 

rc_call_proc_id_t cp_rc_call_proc_id( rc_call_proc_id_t* src);

bool eq_rc_call_proc_id(rc_call_proc_id_t* m0, rc_call_proc_id_t* m1);



//////////////////////////////////////
// RIC Control Header 
/////////////////////////////////////


typedef struct {
  uint32_t dummy;
} rc_ctrl_hdr_t;

void free_rc_ctrl_hdr( rc_ctrl_hdr_t* src); 

rc_ctrl_hdr_t cp_rc_ctrl_hdr(rc_ctrl_hdr_t* src);

bool eq_rc_ctrl_hdr(rc_ctrl_hdr_t* m0, rc_ctrl_hdr_t* m1);



//////////////////////////////////////
// RIC Control Message 
/////////////////////////////////////


typedef struct {
  uint32_t action;
} rc_ctrl_msg_t;

void free_rc_ctrl_msg( rc_ctrl_msg_t* src); 

rc_ctrl_msg_t cp_rc_ctrl_msg(rc_ctrl_msg_t* src);

bool eq_rc_ctrl_msg(rc_ctrl_msg_t* m0, rc_ctrl_msg_t* m1);



//////////////////////////////////////
// RIC Control Outcome 
/////////////////////////////////////

typedef enum{
  RC_CTRL_OUT_OK,

  RC_CTRL_OUT_END
} rc_ctrl_out_e;


typedef struct {
  rc_ctrl_out_e ans;
} rc_ctrl_out_t;

void free_rc_ctrl_out(rc_ctrl_out_t* src); 

rc_ctrl_out_t cp_rc_ctrl_out(rc_ctrl_out_t* src);

bool eq_rc_ctrl_out(rc_ctrl_out_t* m0, rc_ctrl_out_t* m1);


//////////////////////////////////////
// RAN Function Definition 
/////////////////////////////////////

typedef struct {
  uint32_t dummy;
} rc_func_def_t;

void free_rc_func_def( rc_func_def_t* src); 

rc_func_def_t cp_rc_func_def(rc_func_def_t* src);

bool eq_rc_func_def(rc_func_def_t* m0, rc_func_def_t* m1);

/////////////////////////////////////////////////
//////////////////////////////////////////////////
/////////////////////////////////////////////////


/*
 * O-RAN defined 5 Procedures: RIC Subscription, RIC Indication, RIC Control, E2 Setup and RIC Service Update 
 * */


///////////////
/// RIC Subscription
///////////////

typedef struct{
  e2sm_rc_event_trigger_t et; 
  e2sm_rc_action_def_t* ad;
} rc_sub_data_t;

///////////////
// RIC Indication
///////////////

typedef struct{
  e2sm_rc_ind_hdr_t hdr;
  rc_ind_msg_t msg;
  rc_call_proc_id_t* proc_id;
} rc_ind_data_t;

void free_rc_ind_data(rc_ind_data_t* ind);

rc_ind_data_t cp_rc_ind_data(rc_ind_data_t const* src);

///////////////
// RIC Control
///////////////

typedef struct{
  rc_ctrl_hdr_t hdr;
  rc_ctrl_msg_t msg;
} rc_ctrl_req_data_t;

typedef struct{
  rc_ctrl_out_t* out;
} rc_ctrl_out_data_t;

///////////////
// E2 Setup
///////////////

typedef struct{
  rc_func_def_t func_def;
} rc_e2_setup_data_t;

///////////////
// RIC Service Update
///////////////

typedef struct{
  rc_func_def_t func_def;
} rc_ric_service_update_t;


#ifdef __cplusplus
}
#endif

#endif

