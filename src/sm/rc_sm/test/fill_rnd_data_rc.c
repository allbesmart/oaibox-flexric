#include "fill_rnd_data_rc.h"

#include "../ie/ir/ran_param_struct.h"
#include "../ie/ir/ran_param_list.h"


#include <assert.h>


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
double rand_double()
{
  union {
    double a;
    uint8_t b[sizeof(double)];
  } tmp;

  for(size_t i = 0; i < sizeof(double); ++i){
    tmp.b[i] = rand();
  }

  return tmp.a;
}


/////////////////////////////
/////////////////////////////
//////////RC Event Trigger  //////////
/////////////////////////////
/////////////////////////////




static
network_interface_e2rc_t fill_rnd_network_interface(void)
{
  network_interface_e2rc_t dst = {0}; 

  // NI Type
  // Mandatory
  // 9.3.32
  dst.ni_type = rand() % END_NETWORK_INTERFACE_TYPE;

  // NI Identifier
  // Optional
  // 9.3.33
  dst.ni_id = NULL;

  // NI Message
  // Optional
  // 9.3.34
  dst.ni_msg_id = NULL;

  return dst;
}

static
rrc_msg_id_t fill_rnd_rrc_msg_id(void)
{
  rrc_msg_id_t dst = {0}; 

  // Mandatory
  dst.type = rand() % END_RRC_MESSAGE_ID;
  if(dst.type == LTE_RRC_MESSAGE_ID){
    dst.lte = rand() % END_LTE_RRC_CLASS;
  } else if(dst.type == NR_RRC_MESSAGE_ID){
    dst.nr = rand() % END_NR_RRC_CLASS;
  } else {
    assert(0 != 0 && "Unknown type");
  }

  // Mandatory
  // Integer
  // Number starts from 0 from the first
  // entry of a given RRC message class
  // defined in TS 36.331 [14] or TS
  // 38.331 [15].
  dst.rrc_msg_id = rand();

  return dst;
}


static
msg_ev_trg_t fill_rnd_msg_ev_trg(void)
{
  msg_ev_trg_t dst = {0}; 

  // Event Trigger Condition ID
  // Mandatory
  // 9.3.21
  // [1- 65535]
  dst.ev_trigger_cond_id = (rand()% 65535) + 1;

  // CHOICE Message Type
  // Mandatory
  dst.msg_type = rand() % END_MSG_MSG_TYPE_EV_TRG; 
  if(dst.msg_type == NETWORK_INTERFACE_MSG_TYPE_EV_TRG){
    dst.net = fill_rnd_network_interface();
  } else if(dst.msg_type == RRC_MSG_MSG_TYPE_EV_TRG){
    dst.rrc_msg = fill_rnd_rrc_msg_id();
  } else {
    assert( 0 != 0 && "Unknown type");
  }

  //Message Direction
  //Optinonal
  dst.msg_dir = NULL;

  //  Associated UE Info
  //  Optional
  //  9.3.26
  dst.assoc_ue_info = NULL;

  // Logical OR
  // Optional
  // 9.3.25
  dst.log_or = NULL;

  return dst;
}

static
e2sm_rc_ev_trg_frmt_1_t fill_rnd_rc_event_trigger_frmt_1(void)
{
  e2sm_rc_ev_trg_frmt_1_t dst = {0}; 

  // [1 - 65535]
  dst.sz_msg_ev_trg = (rand() % 64) + 1; // Limited for memory constraints 65535

  dst.msg_ev_trg = calloc(dst.sz_msg_ev_trg, sizeof(msg_ev_trg_t));
  assert(dst.msg_ev_trg != NULL && "Memory exhausted");

  for(size_t i = 0; i < dst.sz_msg_ev_trg; ++i){
    dst.msg_ev_trg[i] = fill_rnd_msg_ev_trg(); 
  }

  // Global Associated UE Info
  // Optional
  // 9.3.26
  dst.global_assoc_ue_info = NULL;

  return dst;
}

static
e2sm_rc_ev_trg_frmt_2_t fill_rnd_rc_event_trigger_frmt_2(void)
{
  e2sm_rc_ev_trg_frmt_2_t dst = {0}; 

  //  Call Process Type ID
  //  Mandatory
  //  9.3.15
  //  INTEGER (1.. 65535, …)
  dst.call_proc_type_id = rand();

  // Call Breakpoint ID
  // Mandatory
  // 9.3.49
  // INTEGER (1.. 65535, …)
  dst.call_break_id = rand(); 

  // Associated E2 Node Info
  // Optional
  // 9.3.29
  // ran_param_cond_crit_def_t* assoc_e2_node_info;

  // Associated UE Info
  // Optional
  // 9.3.26
  // ev_trigger_ue_info_t* assoc_ue_info;

  return dst;
}

static
e2_node_info_chng_t fill_rnd_e2_node_info_chng(void)
{
  e2_node_info_chng_t dst = {0}; 

  //Event Trigger Condition ID
  //Mandatory
  //9.3.21
  // INTEGER (1..65535, …)
  dst.ev_trigger_cond_id = (rand()% 65535) + 1 ; 
  
  // E2 Node Information Change ID
  // Mandatory
  // INTEGER (1..512, ...)
  dst.e2_node_info_chng_id = (rand()% 512) + 1;

  // Associated Cell Info
  // Optional
  // 9.3.27
  // ev_trigger_cell_info_t* ev_trigger_cell_info;

  // Logical OR
  // Optional
  // 9.3.25
  //  logical_or_e* log_or; 

  return dst;
}

e2sm_rc_ev_trg_frmt_3_t fill_rnd_rc_event_trigger_frmt_3(void) 
{
  e2sm_rc_ev_trg_frmt_3_t dst = {0}; 

  // Sequence of E2 Node
  // Information Change
  // [1 - 65535]
  dst.sz_e2_node_info_chng = (rand() % 128) + 1; // For not exhasuting the memory


  dst.e2_node_info_chng = calloc(dst.sz_e2_node_info_chng, sizeof(e2_node_info_chng_t));
  assert(dst.e2_node_info_chng != NULL && "Memory exhasuted");

  for(size_t i = 0; i < dst.sz_e2_node_info_chng; ++i){
    dst.e2_node_info_chng[i] = fill_rnd_e2_node_info_chng();
  }

  return dst;
}

static
rrc_state_t fill_rnd_state_chng_to(void)
{
  rrc_state_t dst = {0}; 

  // 9.3.37
  dst.state_chngd_to = rand() % END_RRC_STATE_E2SM_RC;

  // 9.3.25
  // Logical OR
  dst.log_or = NULL;

  return dst;
}

static
rrc_state_lst_t fill_rnd_rrc_state_lst(void)
{
  rrc_state_lst_t dst = {0}; 

  // 9.3.37
  // [1 - 8]
  dst.sz_rrc_state = (rand()% 8) + 1;

  dst.state_chng_to = calloc(dst.sz_rrc_state , sizeof(rrc_state_t));
  assert(dst.state_chng_to != NULL && "Memory exhausted" );

  for(size_t i = 0; i <  dst.sz_rrc_state; ++i){
    dst.state_chng_to[i] = fill_rnd_state_chng_to();
  }

  return dst;
}

static
ran_param_test_t fill_rnd_ran_param_test(void);


static
ran_param_test_lst_t fill_rnd_ran_param_test_lst(void)
{
  ran_param_test_lst_t dst = {0}; 

// [1- 65535]
  dst.sz_lst = 1; //(rand() % 2) + 1; // This can grow the tree very quickly
  dst.ran_param_test = calloc(dst.sz_lst, sizeof( ran_param_test_t));
  assert(dst.ran_param_test != NULL && "Memory exhausted");

  for(size_t i = 0; i < dst.sz_lst; ++i){
    dst.ran_param_test[i] = fill_rnd_ran_param_test();
  }

  return dst;
}

static
ran_param_test_strct_t fill_rnd_ran_param_test_struct(void) 
{
  ran_param_test_strct_t dst = {0}; 

  // [1-65535]
  dst.sz_strct = 1; //(rand()%2) + 1; // This can grow vey quickly if not...

  dst.ran_param_test = calloc(dst.sz_strct, sizeof(ran_param_test_t));
  assert(dst.ran_param_test != NULL && "Memory exhausted" );

  for(size_t i = 0; i <  dst.sz_strct; ++i){
    dst.ran_param_test[i] = fill_rnd_ran_param_test();
  }

  return dst;
}

static
ran_parameter_value_t fill_rnd_ran_param_val(void)
{
  ran_parameter_value_t dst = {0}; 

  dst.type = rand() % END_RAN_PARAMETER_VALUE ;

  if(dst.type == BOOLEAN_RAN_PARAMETER_VALUE){
    dst.bool_ran = rand()%2;
  } else if(dst.type == INTEGER_RAN_PARAMETER_VALUE) {
    dst.int_ran = rand()%4098;
  } else if(dst.type == REAL_RAN_PARAMETER_VALUE) {
    dst.real_ran = (float)rand_double(); 
  } else if(dst.type == BIT_STRING_RAN_PARAMETER_VALUE ) {
    dst.bit_str_ran = cp_str_to_ba("Bit string copy ");
  } else if(dst.type == OCTET_STRING_RAN_PARAMETER_VALUE){
    dst.octet_str_ran = cp_str_to_ba("Octet string copy");
  } else if(dst.type == PRINTABLESTRING_RAN_PARAMETER_VALUE){
    dst.printable_str_ran = cp_str_to_ba("Printable string");
  } else {
    assert(0!=0 && "Unknown type");
  }

  return dst;
}

static
ran_parameter_value_t fill_rnd_ran_param_elm_key_true(void)
{
  //  9.3.14
 return fill_rnd_ran_param_val();
}

static
ran_param_struct_t fill_rnd_ran_param_struct(void);

static
lst_ran_param_t fill_rnd_lst_ran_param(void)
{
  lst_ran_param_t dst = {0};

  // RAN Parameter ID
  // Mandatory
  // 9.3.8
  //1.. 4294967295
  dst.ran_param_id = rand() + 1;

  // RAN Parameter Structure
  // Mandatory
  // 9.3.12
  dst.ran_param_struct = fill_rnd_ran_param_struct();

  return dst;
}

static
ran_param_list_t fill_rnd_ran_param_lst(void)
{
  ran_param_list_t dst = {0};

  // [0- 65535]
  dst.sz_lst_ran_param = (rand() % 2) + 1;
  dst.lst_ran_param = calloc(dst.sz_lst_ran_param, sizeof(lst_ran_param_t )); 
  assert(dst.lst_ran_param != NULL && "Memory exhausted");

  for(size_t i = 0 ; i < dst.sz_lst_ran_param; ++i){
    dst.lst_ran_param[i] = fill_rnd_lst_ran_param();
  }
  
  return dst;
}

static
seq_ran_param_t fill_rnd_seq_ran_param(void);

static
ran_param_struct_t fill_rnd_ran_param_struct(void)
{
  ran_param_struct_t dst = {0}; 
 
  // [1-65535]
  dst.sz_ran_param_struct = (rand() % 2 ) +1 ;

  dst.ran_param_struct = calloc(dst.sz_ran_param_struct, sizeof(seq_ran_param_t));
  assert(dst.ran_param_struct != NULL && "Memory exhausted" );

  for(size_t i = 0; i < dst.sz_ran_param_struct ; ++i){
    dst.ran_param_struct[i] =  fill_rnd_seq_ran_param();
  }

  return dst;
}

static
ran_param_test_cond_t fill_rnd_ran_param_test_cond(void)
{
  ran_param_test_cond_t dst = {0};

  dst.cond = rand() % END_RAN_PARAM_TEST_COND;

  if(dst.cond == COMPARISON_RAN_PARAM_TEST_COND){
    dst.comp = rand() % END_RAN_PARAM_TEST_COND_COMP;
  } else if(dst.cond == PRESENCE_RAN_PARAM_TEST_COND){
    dst.presence = rand() % END_RAN_PARAM_TEST_COND_PRESENCE;
  } else {
    assert(0!=0 && "Unknown type");
  }

  return dst;
}

static
ran_param_elm_key_false_t fill_rnd_ran_param_elm_key_false()
{
  ran_param_elm_key_false_t dst = {0}; 

  // RAN Parameter Test Condition
  // 9.3.31
  // Mandatory
  dst.test_cond = fill_rnd_ran_param_test_cond();

  // RAN Parameter Value
  // Optional
  // 9.3.14
  dst.value = NULL;

  // Logical OR
  // Optional
  // 9.3.25
  dst.logical_or = NULL;

  return dst;
}

static
ran_param_test_t fill_rnd_ran_param_test(void)
{
  ran_param_test_t dst = {0}; 

 //RAN Parameter ID
  //Mandatory
  //Bug in the standard. 9.3.9 wrote in section 9. 
  //9.3.8 in ASN language. Probably 9.3.8 intended
  //1.. 4294967295
  dst.ran_param_id = (rand() %  4294967295) + 1; 

  dst.type = rand() % END_RAN_PARAMETER_TYPE;

  if(dst.type == LIST_RAN_PARAMETER_TYPE){
    dst.lst = fill_rnd_ran_param_test_lst();
  } else if(dst.type == STRUCTURE_RAN_PARAMETER_TYPE ){
    dst.strct = fill_rnd_ran_param_test_struct() ;
  } else if(dst.type ==  ELEMENT_WITH_KEY_FLAG_TRUE_RAN_PARAMETER_TYPE){
    dst.flag_true = fill_rnd_ran_param_elm_key_true();
  } else if(dst.type == ELEMENT_WITH_KEY_FLAG_FALSE_RAN_PARAMETER_TYPE ){
    dst.flag_false = fill_rnd_ran_param_elm_key_false();
  }

  return dst;
}

static
ran_param_cond_crit_def_t fill_rnd_ran_param_cond_crit_def(void)
{
  ran_param_cond_crit_def_t dst = {0}; 

  // [1 - 255 ]
  dst.sz_ran_param_test = 1; //(rand()%16) + 1; 

  // RAN Parameter Test
  // 9.3.30
  dst.ran_param_test = calloc(dst.sz_ran_param_test, sizeof(ran_param_test_t));
  assert(dst.ran_param_test != NULL && "Memory exhausted");

  for(size_t i = 0; i < dst.sz_ran_param_test; ++i){
    dst.ran_param_test[i] = fill_rnd_ran_param_test();
  }

  return dst;
}

static
ue_info_chng_t fill_rnd_ue_info_chng()
{
  ue_info_chng_t dst = {0}; 

  //  Event Trigger Condition ID
  //  Mandatory
  //  9.3.21
  // INTEGER (1..65535, …)
  dst.ev_trig_cond_id = (rand()%65535) + 1;

  // CHOICE Trigger Type

  dst.type =  L2_STATE_UE_INFO_CHNG_TRIGGER_TYPE; //rand()%END_UE_INFO_CHNG_TRIGGER_TYPE;

  if( dst.type == RRC_STATE_UE_INFO_CHNG_TRIGGER_TYPE){
    // RRC State
    dst.rrc_state = fill_rnd_rrc_state_lst();  

  } else if(dst.type == UE_ID_CHANGE_UE_INFO_CHNG_TRIGGER_TYPE){
    // UE Identifier Change
    // [1 - 512]
    dst.ue_id_chng = (rand() % 512) + 1;

  } else if(dst.type == L2_STATE_UE_INFO_CHNG_TRIGGER_TYPE){
    // 9.3.29
    // RAN Parameter Conditional Criteria Definition
    dst.l2_state = fill_rnd_ran_param_cond_crit_def();

  } else {
    assert(0!=0 && "Unknown type");
  }


  // Associated UE Info 
  // Optional
  // 9.3.26
  dst.assoc_ue_info = NULL;

  // Logical OR
  // Optional
  // 9.3.25
  dst.log_or = NULL;

  return dst;
}


static
e2sm_rc_ev_trg_frmt_4_t fill_rnd_rc_event_trigger_frmt_4(void) 
{
  e2sm_rc_ev_trg_frmt_4_t dst = {0}; 

 // Sequence of UE Information Change
 // [ 1 - 65535]
  dst.sz_ue_info_chng = 1; //(rand()% 128) + 1;
  
  dst.ue_info_chng = calloc(dst.sz_ue_info_chng, sizeof(ue_info_chng_t) );
  assert(dst.ue_info_chng != NULL && "Memory exhausted"); 

  for(size_t i = 0; i <  dst.sz_ue_info_chng; ++i){
   dst.ue_info_chng[i] = fill_rnd_ue_info_chng();   
  }

  return dst;
}


static
e2sm_rc_ev_trg_frmt_5_t fill_rnd_rc_event_trigger_frmt_5()
{
  e2sm_rc_ev_trg_frmt_5_t dst = {0} ;
 
  // On Demand
  // Mandatory
  dst.on_demand = rand()% END_ON_DEMAND_FRMT_5 ;

  // Associated UE Info
  // Optional
  // 9.3.26
  // ev_trigger_ue_info_t* assoc_ue_info;

  // Associated Cell Info
  // Optional
  // 9.3.27
  // ev_trigger_cell_info_t* assoc_cell_info;

  return dst;
}


e2sm_rc_event_trigger_t fill_rnd_rc_event_trigger(void)
{
  e2sm_rc_event_trigger_t dst = {0}; 

  dst.format = rand() % END_E2SM_RC_EV_TRIGGER_FORMAT;

  dst.format = FORMAT_4_E2SM_RC_EV_TRIGGER_FORMAT; 

  if(dst.format == FORMAT_1_E2SM_RC_EV_TRIGGER_FORMAT){
    dst.frmt_1 = fill_rnd_rc_event_trigger_frmt_1() ;

  }else if(dst.format == FORMAT_2_E2SM_RC_EV_TRIGGER_FORMAT){
    dst.frmt_2 = fill_rnd_rc_event_trigger_frmt_2() ;

  }else if(dst.format == FORMAT_3_E2SM_RC_EV_TRIGGER_FORMAT){
    dst.frmt_3 = fill_rnd_rc_event_trigger_frmt_3() ;

  }else if(dst.format == FORMAT_4_E2SM_RC_EV_TRIGGER_FORMAT){
    dst.frmt_4 = fill_rnd_rc_event_trigger_frmt_4() ;

  }else if(dst.format == FORMAT_5_E2SM_RC_EV_TRIGGER_FORMAT){
    dst.frmt_5 = fill_rnd_rc_event_trigger_frmt_5() ;

  } else {
    assert(0!=0 && "Unknown format");
  }

    return dst;
}

/////////////////////////////
/////////////////////////////
////////// End of RC Event Trigger  //////////
/////////////////////////////
/////////////////////////////



/////////////////////////////
/////////////////////////////
////////// Start of RC Action Definition //////////////////
/////////////////////////////
/////////////////////////////

static
param_report_def_t fill_rnd_param_report_def(void) 
{
  param_report_def_t dst = {0};

  // RAN Parameter ID
  // Mandatory
  // 9.3.8
  // [1 - 4294967295]
  dst.ran_param_id = rand() + 1; 

  // RAN Parameter Definition
  // Optional
  // 9.3.51
  dst.ran_param_def = NULL; 

  return dst;
}


static
e2sm_rc_act_def_frmt_1_t fill_rnd_rc_action_def_frmt_1(void)
{
  e2sm_rc_act_def_frmt_1_t dst = {0}; 

  // Parameters to be Reported List
  // [1-65535]
  dst.sz_param_report_def = (rand()% 65535) + 1;

  dst.param_report_def = calloc(dst.sz_param_report_def, sizeof( param_report_def_t));
  assert(dst.param_report_def != NULL && "Memory exhausyted");

  for(size_t i = 0; i < dst.sz_param_report_def; ++i){
    dst.param_report_def[i] = fill_rnd_param_report_def() ;
  }

  return dst;
}

static
int recursion_fill_rnd_ran_param_val_type = 0;

static
ran_param_val_type_t fill_rnd_ran_param_val_type()
{
  ran_param_val_type_t dst = {0}; 

  dst.type =  STRUCTURE_RAN_PARAMETER_VAL_TYPE; //rand() % END_RAN_PARAMETER_VAL_TYPE;

  recursion_fill_rnd_ran_param_val_type += 1; 
  if(recursion_fill_rnd_ran_param_val_type > 4){
//    recursion_fill_rnd_ran_param_val_type = 0; 
    dst.type = ELEMENT_KEY_FLAG_TRUE_RAN_PARAMETER_VAL_TYPE;
  }

  if(dst.type == ELEMENT_KEY_FLAG_TRUE_RAN_PARAMETER_VAL_TYPE){
    dst.flag_true = calloc(1, sizeof( ran_parameter_value_t));
    assert(dst.flag_true != NULL && "Memory exhausted" );
    *dst.flag_true = fill_rnd_ran_param_val();
  } else if(dst.type == ELEMENT_KEY_FLAG_FALSE_RAN_PARAMETER_VAL_TYPE ){
    dst.flag_false = calloc(1, sizeof( ran_parameter_value_t));
    assert(dst.flag_false != NULL && "Memory exhausted" );
    *dst.flag_false = fill_rnd_ran_param_val();
  }else if(dst.type == STRUCTURE_RAN_PARAMETER_VAL_TYPE){
    dst.strct = calloc(1, sizeof(ran_param_struct_t));
    assert(dst.strct != NULL && "Memory exhausted" );
    *dst.strct = fill_rnd_ran_param_struct();
  }else if(dst.type == LIST_RAN_PARAMETER_VAL_TYPE ){
    dst.lst = calloc(1, sizeof(ran_param_list_t)); 
    assert(dst.lst != NULL && "memory exhausted");    
    *dst.lst = fill_rnd_ran_param_lst();
  } else {
    assert(0!=0 && "not implemented" );
  }
 
  return dst;
}

static
seq_ran_param_t fill_rnd_seq_ran_param(void)
{
  seq_ran_param_t dst = {0}; 

  //RAN Parameter ID
  //Mandatory
  //9.3.8
  // [1 - 4294967295]
  dst.ran_param_id = (rand()% 4098) +1 ;

  // RAN Parameter Value Type
  // 9.3.11
  // Mandatory
  dst.ran_param_val = fill_rnd_ran_param_val_type();  

  return dst;
}

static
policy_action_t fill_rnd_policy_action(void)
{
  policy_action_t dst = {0}; 

  //  Policy Action ID
  //  Mandatory
  //  9.3.6
  //  [1 - 65535]
  dst.policy_act_id = (rand()% 65535) +1;

  // Sequence of RAN Parameters
  // [0- 65535]
  dst.sz_seq_ran_param = rand()% 2; //65535;
   
  if(dst.sz_seq_ran_param > 0){
    dst.seq_ran_param = calloc(dst.sz_seq_ran_param, sizeof(seq_ran_param_t)); 
    assert(dst.seq_ran_param != NULL && "Memory exhausted" );
  }

  for(size_t i = 0 ; i < dst.sz_seq_ran_param; ++i){
    dst.seq_ran_param[i] = fill_rnd_seq_ran_param();
  }

  // RIC Policy decision
  // Optional
  dst.pol_dec = NULL; 

  return dst;
}

static
policy_cond_t fill_rnd_policy_cond(void)
{
  policy_cond_t dst = {0}; 

  // Policy Action Definition
  // Mandatory
  // 9.3.20
  dst.pol_act = fill_rnd_policy_action();

  // Policy Condition Definition
  // Optional
  // 9.3.29
  dst.pol = NULL;

  return dst;
}

static
e2sm_rc_act_def_frmt_2_t fill_rnd_rc_action_def_frmt_2(void)
{
  e2sm_rc_act_def_frmt_2_t dst = {0}; 

  // Sequence of Policy Conditions
  // [1 - 65535]
  dst.sz_policy_cond = (rand() % 2) + 1; // Too large  65535

  dst.policy_cond = calloc(dst.sz_policy_cond, sizeof(policy_cond_t) );
  assert(dst.policy_cond != NULL && "memory exhausted" );

  for(size_t i = 0; i <  dst.sz_policy_cond; ++i){
    dst.policy_cond[i] = fill_rnd_policy_cond(); 
  }

  return dst;
}


e2sm_rc_action_def_t fill_rnd_rc_action_def(void)
{
  e2sm_rc_action_def_t dst = {0}; 

  //  RIC Style Type
  //  Mandatory
  //  9.3.3
  // Defined in common 6.2.2.2.
  dst.ric_style_type = (rand()%1024) + 1;

  dst.format = FORMAT_2_E2SM_RC_ACT_DEF; //  rand() % END_E2SM_RC_ACT_DEF;

  if(dst.format == FORMAT_1_E2SM_RC_ACT_DEF ){
    dst.frmt_1 = fill_rnd_rc_action_def_frmt_1();

  } else if(dst.format == FORMAT_2_E2SM_RC_ACT_DEF){
    dst.frmt_2 = fill_rnd_rc_action_def_frmt_2();

  } else if(dst.format == FORMAT_3_E2SM_RC_ACT_DEF){
    assert(0!=0 && "Not implemented");
  } else if(dst.format == FORMAT_4_E2SM_RC_ACT_DEF){
    assert(0!=0 && "Not implemented");
  } else {
    assert(0 != 0 && "Unknown format");
  }


  //9.2.1.2.1
//  e2sm_rc_act_def_frmt_2_t frmt_2;
//  e2sm_rc_act_def_frmt_3_t frmt_3;
//  e2sm_rc_act_def_frmt_4_t frmt_4;

  return dst;
}


