#include "../common/fill_ind_data.h"
#include "../../../src/util/alg_ds/alg/defer.h"
#include "../../../src/sm/rc_sm/rc_sm_agent.h"
#include "../../../src/sm/rc_sm/rc_sm_ric.h"
#include "../../../src/sm/rc_sm/ie/rc_data_ie.h"
#include "../../../src/sm/rc_sm/rc_sm_id.h"


#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////

//static
//tc_ctrl_req_data_t cp_ctrl;

//
// Functions 
static
byte_array_t cp_str_to_ba(const char* str)
{
  assert(str != NULL);
  
  const size_t sz = strlen(str);

  byte_array_t dst = {.len = sz};

  dst.buf = calloc(sz,sizeof(uint8_t));
  assert(dst.buf != NULL && "Memory exhausted");

  memcpy(dst.buf, str, sz);

  return dst;
}

static
ran_function_name_t fill_rc_ran_func_name(void)
{
  ran_function_name_t dst = {0}; 

    // RAN Function Short Name
    // Mandatory
    // PrintableString [1-150]
    dst.name = cp_str_to_ba(SM_RAN_CTRL_SHORT_NAME);

    // RAN Function Service Model OID
    // Mandatory
    // PrintableString [1-1000]
    
    //iso(1) identified-organization(3)
    //dod(6) internet(1) private(4)
    //enterprise(1) 53148 e2(1)
    // version1 (1) e2sm(2) e2sm-RC-
    // IEs (3)
    dst.oid = cp_str_to_ba(SM_RAN_CTRL_OID);

    // RAN Function Description
    // Mandatory
    // PrintableString [1- 150]
    //RAN function RC “RAN Control” performs the following
    //functionalities:
    //- Exposure of RAN control and UE context related
    //information.
    //- Modification and initiation of RAN control related call
    //processes and messages
    //- Execution of policies that may result in change of
    //RAN control behavior 

    dst.description = cp_str_to_ba( SM_RAN_CTRL_DESCRIPTION);

    // RAN Function Instance
    // Optional
    // INTEGER
//    long* instance;	/* OPTIONAL: it is suggested to be used when E2 Node declares
//                                multiple RAN Function ID supporting the same  E2SM specification   ask Mikel */

  return dst;
}

static
e2sm_rc_func_def_t fill_rc_ran_func_def(void)
{
  e2sm_rc_func_def_t dst = {0}; 

  //  RAN Function Name
  //  Mandatory
  //  9.3.2
  //  6.2.2.1.
  dst.name = fill_rc_ran_func_name();  

  // RAN Function Definition for EVENT TRIGGER
  // Optional
  // 9.2.2.2
  // ran_func_def_ev_trig_t* ev_trig;

  // RAN Function Definition for REPORT
  // Optional
  // 9.2.2.3
  // ran_func_def_report_t* report;

  // RAN Function Definition for INSERT
  // Optional
  // 9.2.2.4
  // ran_func_def_insert_t* insert;

  // RAN Function Definition for CONTROL
  // Optional
  // 9.2.2.5
  // ran_func_def_ctrl_t* ctrl;

  // RAN Function Definition for POLICY
  // Optional
  // 9.2.2.6
  // ran_func_def_policy_t* policy;

  return dst;
}




/////
// AGENT
////

// For testing purposes
static
rc_ind_data_t cp_ind;

static
rc_e2_setup_t cp_e2_setup; 

static
void read_RAN(sm_ag_if_rd_t* read)
{
  assert(read != NULL);
  if(read->type == INDICATION_MSG_AGENT_IF_ANS_V0){ 
  assert(read->ind.type == RAN_CTRL_STATS_V1_03);

  read->ind.rc_ind = fill_rnd_rc_ind_data();
  cp_ind = cp_rc_ind_data(&read->ind.rc_ind);

  } else if(read->type == E2_SETUP_AGENT_IF_ANS_V0 ){
    assert(read->e2ap.type == RAN_CTRL_V1_3_AGENT_IF_E2_SETUP_ANS_V0);
    read->e2ap.rc.func_def = fill_rc_ran_func_def();
    cp_e2_setup.func_def = cp_e2sm_rc_func_def(&read->e2ap.rc.func_def);
  } else {
    assert(0!=0 && "Unknown type");
  }
}

// For testing purposes
static
rc_sub_data_t cp_rc_sub; 

static
rc_ctrl_req_data_t cp_rc_ctrl; 

static
e2sm_rc_ctrl_out_t cp_rc_ctrl_out; 

static 
sm_ag_if_ans_t write_RAN(sm_ag_if_wr_t const* data)
{
  assert(data != NULL); 

  sm_ag_if_ans_t ans = {.type = NONE_SM_AG_IF_ANS_V0};

  if(data->type == SUBSCRIPTION_SM_AG_IF_WR){
    assert(data->subs.type == RAN_CTRL_SUBS_V1_03); 
    assert(data->subs.rc_sub.ad == NULL && "Not implemented");

    cp_rc_sub = cp_rc_sub_data(&data->subs.rc_sub);

  } else if(data->type == CONTROL_SM_AG_IF_WR){
    assert(data->ctrl.type == RAN_CONTROL_CTRL_V1_03);
    
    // RAN Input
    cp_rc_ctrl = cp_rc_ctrl_req_data(&data->ctrl.rc_ctrl);

    // RAN Output
    ans.type = CTRL_OUTCOME_SM_AG_IF_ANS_V0; 
    ans.ctrl_out.type = RAN_CTRL_V1_3_AGENT_IF_CTRL_ANS_V0;
    ans.ctrl_out.rc = fill_rc_ctrl_out();
    cp_rc_ctrl_out = cp_e2sm_rc_ctrl_out( &ans.ctrl_out.rc );

  } else {
    assert(0!=0 && "Unknown type");
  }

  return ans;
}


/////////////////////////////
// Check Functions
// //////////////////////////

/*
static
void check_eq_ran_function(sm_agent_t const* ag, sm_ric_t const* ric)
{
  assert(ag != NULL);
  assert(ric != NULL);


  assert(ag->ran_func_id == ric->ran_func_id);
}

*/

// RIC -> E2
static
void check_subscription(sm_agent_t* ag, sm_ric_t* ric)
{
  assert(ag != NULL);
  assert(ric != NULL);

  sm_ag_if_wr_subs_t sub = {.type = RAN_CTRL_SUBS_V1_03};
  sub.rc_sub = fill_rnd_rc_subscription();
  defer({ free_rc_sub_data(&sub.rc_sub); });

  sm_subs_data_t data = ric->proc.on_subscription(ric, &sub);
  defer({ free_sm_subs_data(&data); });

  subscribe_timer_t t = ag->proc.on_subscription(ag, &data); 
  defer({  free_rc_sub_data(&cp_rc_sub); });
  assert(t.ms == -1);

  assert(eq_rc_sub_data(&sub.rc_sub, &cp_rc_sub) == true);
}

// E2 -> RIC
static
void check_indication(sm_agent_t* ag, sm_ric_t* ric)
{
  assert(ag != NULL);
  assert(ric != NULL);

  sm_ind_data_t sm_data = ag->proc.on_indication(ag);
  defer({ free_sm_ind_data(&sm_data); }); 
  defer({ free_rc_ind_data(&cp_ind); });

  sm_ag_if_rd_ind_t msg = ric->proc.on_indication(ric, &sm_data);
  assert(msg.type == RAN_CTRL_STATS_V1_03);
  defer({ free_rc_ind_data(&msg.rc_ind); });

  rc_ind_data_t const* data = &msg.rc_ind;

  assert(eq_rc_ind_data(&cp_ind, data) == true);
}


static
void check_ctrl(sm_agent_t* ag, sm_ric_t* ric)
{
  assert(ag != NULL);
  assert(ric != NULL);

  sm_ag_if_wr_t wr = {.type = CONTROL_SM_AG_IF_WR };
  wr.ctrl.type = RAN_CONTROL_CTRL_V1_03;

  wr.ctrl.rc_ctrl = fill_rc_ctrl();
  defer({ free_rc_ctrl_req_data(&wr.ctrl.rc_ctrl); });

  sm_ctrl_req_data_t ctrl_req = ric->proc.on_control_req(ric, &wr.ctrl);
  defer({ free_sm_ctrl_req_data(&ctrl_req); });

  sm_ctrl_out_data_t out_data = ag->proc.on_control(ag, &ctrl_req);
  defer({ free_rc_ctrl_req_data(&cp_rc_ctrl); });

  assert(eq_rc_ctrl_req_data(&wr.ctrl.rc_ctrl, &cp_rc_ctrl));

  sm_ag_if_ans_ctrl_t ans = ric->proc.on_control_out(ric, &out_data);
  assert(ans.type == RAN_CTRL_V1_3_AGENT_IF_CTRL_ANS_V0);
  defer({ free_e2sm_rc_ctrl_out(&ans.rc); });
  defer({ free_e2sm_rc_ctrl_out(&cp_rc_ctrl_out); });

  assert(eq_e2sm_rc_ctrl_out(&ans.rc, &cp_rc_ctrl_out));
}

void check_e2_setup(sm_agent_t* ag, sm_ric_t* ric)
{
  assert(ag != NULL);
  assert(ric != NULL);

  sm_e2_setup_data_t data = ag->proc.on_e2_setup(ag);
  defer({ free_sm_e2_setup(&data); });

  sm_ag_if_rd_e2setup_t out = ric->proc.on_e2_setup(ric, &data);
  assert(out.type == RAN_CTRL_V1_3_AGENT_IF_E2_SETUP_ANS_V0);
  defer({ free_e2sm_rc_func_def(&out.rc.func_def); });

  assert(eq_e2sm_rc_func_def(&out.rc.func_def, &cp_e2_setup.func_def) == true);
}


int main()
{
  srand(time(0)); 

  sm_io_ag_t io_ag = {.read = read_RAN, .write = write_RAN};  
  sm_agent_t* sm_ag = make_rc_sm_agent(io_ag);

  sm_ric_t* sm_ric = make_rc_sm_ric();

//  for(int i =0 ; i < 256*4096; ++i){
 //   check_eq_ran_function(sm_ag, sm_ric);
 //
    //check_indication(sm_ag, sm_ric);
    //check_subscription(sm_ag, sm_ric);
    // check_ctrl(sm_ag, sm_ric);
    check_e2_setup(sm_ag, sm_ric);
//    check_ric_service_update(sm_ag, sm_ric);

//  }

  sm_ag->free_sm(sm_ag);
  sm_ric->free_sm(sm_ric);

  printf("RAN Control (RC-SM) version 1.3 Release 3 run with success\n");
  return EXIT_SUCCESS;
}

