#include "fill_rnd_data_kpm.h"

#include <assert.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

kpm_event_trigger_def_t fill_kpm_event_trigger_def(void)
{
  kpm_event_trigger_def_t dst = {0};

  dst.type = rand()%END_FORMAT_RIC_EVENT_TRIGGER;

  if(dst.type == FORMAT_1_RIC_EVENT_TRIGGER  ){
    // Normally the period is not free, need to check in the specs
    dst.kpm_ric_event_trigger_format_1.report_period_ms = rand()%1000;
  } else {
    assert(0 != 0 && "unknown type");
  }

  return dst;
}

kpm_act_def_format_1_t fill_kpm_action_def_frm_1(void)
{
  kpm_act_def_format_1_t action_def_frm_1 = {0};

  // Measurement Information
  // [1, 65535]
  // mir: Here there is a bug. uncomment the following line i.e., (rand() % 65535)
  action_def_frm_1.meas_info_lst_len = 64; //(rand() % 65535) + 1;
                                            
  action_def_frm_1.meas_info_lst = calloc(action_def_frm_1.meas_info_lst_len, sizeof(meas_info_format_1_lst_t));
  assert(action_def_frm_1.meas_info_lst != NULL && "Memory exhausted" );
  
  for (size_t i = 0; i < action_def_frm_1.meas_info_lst_len; i++)
  {
    meas_info_format_1_lst_t* meas_info = &action_def_frm_1.meas_info_lst[i];
      // Measurement Type
      meas_info->meas_type.type = NAME_MEAS_TYPE;
      meas_info->meas_type.name.buf = calloc(strlen("test") + 1, sizeof(char));
      memcpy(meas_info->meas_type.name.buf, "test", strlen("test"));
      meas_info->meas_type.name.len = strlen("test");
      // Label Information
      // [1, 2147483647]
     meas_info->label_info_lst_len = 2 ; // With the real number, we can run out of memory i.e., 2147483647
     meas_info->label_info_lst = calloc(meas_info->label_info_lst_len, sizeof(label_info_lst_t));
      assert(meas_info->label_info_lst != NULL && "Memory exhausted" );
      for (size_t j = 0; j < meas_info->label_info_lst_len; j++)
      {
        meas_info->label_info_lst[j].plmn_id = malloc(sizeof(plmn_t));
        assert(meas_info->label_info_lst[j].plmn_id  != NULL);

        *meas_info->label_info_lst[j].plmn_id = (plmn_t) {.mcc = 505, .mnc = 1, .mnc_digit_len = 2};
        // action_def_frm_1.meas_info_lst[i].label_info_lst[j].noLabel = malloc(sizeof(enum_value_e));
        // *action_def_frm_1.meas_info_lst[i].label_info_lst[j].noLabel = TRUE_ENUM_VALUE;
      }
  }
  
  // Granularity Period
  action_def_frm_1.gran_period_ms = (rand() % 4294967295) + 0;
  
  // Cell Global ID - OPTIONAL
  action_def_frm_1.cell_global_id = calloc(1, sizeof(*action_def_frm_1.cell_global_id));
  action_def_frm_1.cell_global_id->type = NR_CGI_RAT_TYPE; // rand()%END_CGI_RAT_TYPE;
  
  switch (action_def_frm_1.cell_global_id->type)
  {
  case NR_CGI_RAT_TYPE:
    action_def_frm_1.cell_global_id->nr_cgi.plmn_id = (plmn_t) {.mcc = 505, .mnc = 1, .mnc_digit_len = 2};
    action_def_frm_1.cell_global_id->nr_cgi.nr_cell_id = (rand() % 2^36) + 1;
    break;

  case EUTRA_CGI_RAT_TYPE:
    action_def_frm_1.cell_global_id->eutra.plmn_id = (plmn_t) {.mcc = 505, .mnc = 1, .mnc_digit_len = 2};
    action_def_frm_1.cell_global_id->eutra.eutra_cell_id = (rand() % 2^28) + 0;
    break;
  
  default:
    assert(false && "Unknown Cell Global ID Type");
  }
  
  // Measurement Bin Range - OPTIONAL
  action_def_frm_1.meas_bin_range_info_lst_len = 0;
  action_def_frm_1.meas_bin_info_lst = NULL;

  return action_def_frm_1;
}

gnb_t fill_gnb_data(void)
{
  gnb_t gnb = {0};

  // 6.2.3.16
  // Mandatory
  // AMF UE NGAP ID
  gnb.amf_ue_ngap_id = (rand() % 2^40) + 0;

  // Mandatory
  //GUAMI 6.2.3.17 
  gnb.guami.plmn_id = (plmn_t) {.mcc = 505, .mnc = 1, .mnc_digit_len = 2};
  
  gnb.guami.amf_region_id = 1;  // 48 example in spec
  gnb.guami.amf_set_id = 1;  // 001 example in spec
  gnb.guami.amf_ptr = 1;  // 12 example in spec

  // gNB-CU UE F1AP ID List
  // C-ifCUDUseparated 
  gnb.gnb_cu_ue_f1ap_lst_len = (rand() % 4) + 1;
  gnb.gnb_cu_ue_f1ap_lst = calloc(gnb.gnb_cu_ue_f1ap_lst_len, sizeof(uint32_t));
  for (size_t i = 0; i < gnb.gnb_cu_ue_f1ap_lst_len; i++)
  {
    gnb.gnb_cu_ue_f1ap_lst[i] = i;
  }

  //gNB-CU-CP UE E1AP ID List
  //C-ifCPUPseparated 
  gnb.gnb_cu_cp_ue_e1ap_lst_len = 3; //(rand() % 65535) + 1;
  gnb.gnb_cu_cp_ue_e1ap_lst = calloc(gnb.gnb_cu_cp_ue_e1ap_lst_len, sizeof(uint32_t));
  for (size_t i = 0; i < gnb.gnb_cu_cp_ue_e1ap_lst_len; i++)
  {
    gnb.gnb_cu_cp_ue_e1ap_lst[i] = i;
  }

  // RAN UE ID
  // Optional
  // 6.2.3.25
  gnb.ran_ue_id = NULL;

  //  M-NG-RAN node UE XnAP ID
  // C- ifDCSetup
  // 6.2.3.19
  gnb.ng_ran_node_ue_xnap_id = NULL;

  // Global gNB ID
  // 6.2.3.3
  // Optional
  // This IE shall not be used. Global NG-RAN Node ID IE shall replace this IE 
  gnb.global_gnb_id = NULL;

  // Global NG-RAN Node ID
  // C-ifDCSetup
  // 6.2.3.2
  gnb.global_ng_ran_node_id = NULL;

  return gnb;
}

gnb_du_t fill_gnb_du_data(void)
{
  gnb_du_t gnb_du = {0};
  gnb_du.gnb_cu_ue_f1ap = (rand() % 2^32) + 0;

  gnb_du.ran_ue_id = calloc(1, sizeof(*gnb_du.ran_ue_id));
  *gnb_du.ran_ue_id = (rand() % 2^64) + 0;

  return gnb_du;
}

gnb_cu_up_t fill_gnb_cu_up_data(void)
{
  gnb_cu_up_t gnb_cu_up = {0};
  gnb_cu_up.gnb_cu_cp_ue_e1ap = (rand() % 2^32) + 0;

  gnb_cu_up.ran_ue_id = NULL;

  return gnb_cu_up;
}

ng_enb_t fill_ng_enb_data(void)
{
  ng_enb_t ng_enb = {0};

  // 6.2.3.16
  // Mandatory
  // AMF UE NGAP ID
  ng_enb.amf_ue_ngap_id = (rand() % 2^40) + 0;

  // 6.2.3.17
  // Mandatory
  // GUAMI
  ng_enb.guami.plmn_id = (plmn_t) {.mcc = 505, .mnc = 1, .mnc_digit_len = 2};
  
  ng_enb.guami.amf_region_id = (rand() % 2^8) + 0;
  ng_enb.guami.amf_set_id = 1;
  ng_enb.guami.amf_ptr = 1; 

  // 6.2.3.22
  // C-if CU DU separated
  // ng-eNB-CU UE W1AP ID
  ng_enb.ng_enb_cu_ue_w1ap_id = NULL;

  // 6.2.3.19
  // C- ifDCSetup
  // M-NG-RAN node UE XnAP ID
  ng_enb.ng_ran_node_ue_xnap_id = NULL;

  // OPTIONAL
  // This IE shall not be used. Global NG-RAN Node ID IE shall replace this IE
  ng_enb.global_ng_enb_id = NULL;

  // Global NG-RAN Node ID
  // C-ifDCSetup
  // 6.2.3.2
  ng_enb.global_ng_ran_node_id = NULL;

  return ng_enb;
}

ng_enb_du_t fill_ng_enb_du_data(void)
{
  ng_enb_du_t ng_enb_du = {0};

  // 6.2.3.22
  // C-if CU DU separated
  // ng-eNB-CU UE W1AP ID
  ng_enb_du.ng_enb_cu_ue_w1ap_id = (rand() % 2^32) + 0;

  return ng_enb_du;
}

en_gnb_t fill_en_gnb_data(void)
{
  en_gnb_t en_gnb = {0};

  // 6.2.3.23
  // Mandatory
  // MeNB UE X2AP ID
  en_gnb.enb_ue_x2ap_id = (rand() % 4095) + 0;

  // 6.2.3.24
  // OPTIONAL
  // MeNB UE X2AP ID Extension
  en_gnb.enb_ue_x2ap_id_extension = NULL;

  // 6.2.3.9
  // Mandatory
  // Global eNB ID
  en_gnb.global_enb_id.plmn_id = (plmn_t) {.mcc = 505, .mnc = 1, .mnc_digit_len = 2};

  en_gnb.global_enb_id.type = MACRO_ENB_TYPE_ID;
  // rand()%END_ENB_TYPE_ID;

  switch (en_gnb.global_enb_id.type)
  {
  case MACRO_ENB_TYPE_ID:
    en_gnb.global_enb_id.macro_enb_id = (rand() % 2^20) + 0;
    break;
  
  case HOME_ENB_TYPE_ID:
    en_gnb.global_enb_id.home_enb_id = (rand() % 2^28) + 0;
    break;

  case SHORT_MACRO_ENB_TYPE_ID:
    en_gnb.global_enb_id.short_macro_enb_id = (rand() % 2^18) + 0;
    break;

  case LONG_MACRO_ENB_TYPE_ID:
    en_gnb.global_enb_id.long_macro_enb_id = (rand() % 2^21) + 0;
    break;

  default:
    break;
  }

  // 6.2.3.21
  // gNB-CU UE F1AP ID
  // C-ifCUDUseparated 
  en_gnb.gnb_cu_ue_f1ap_lst = NULL;

  // gNB-CU-CP UE E1AP ID List
  // C-ifCPUPseparated 
  en_gnb.gnb_cu_cp_ue_e1ap_lst_len = 3;
  en_gnb.gnb_cu_cp_ue_e1ap_lst = calloc(en_gnb.gnb_cu_cp_ue_e1ap_lst_len, sizeof(uint32_t));
  for (size_t i = 0; i < en_gnb.gnb_cu_cp_ue_e1ap_lst_len; i++)
  {
    en_gnb.gnb_cu_cp_ue_e1ap_lst[i] = i;
  }

  // RAN UE ID
  // Optional
  // 6.2.3.25
  en_gnb.ran_ue_id = NULL;

  return en_gnb;
}

enb_t fill_enb_data(void)
{
  enb_t enb = {0};

  // 6.2.3.26
  // Mandatory
  // MME UE S1AP ID
  enb.mme_ue_s1ap_id = (rand() % 2^32) + 0;

  // 6.2.3.18
  // Mandatory
  // GUMMEI
  enb.gummei.plmn_id = (plmn_t) {.mcc = 505, .mnc = 1, .mnc_digit_len = 2};
  enb.gummei.mme_group_id = (rand() % 2^16) + 0;
  enb.gummei.mme_code = (rand() % 2^8) + 0;

  // 6.2.3.23
  // C-ifDCSetup
  // MeNB UE X2AP ID
  enb.enb_ue_x2ap_id = NULL;

  // 6.2.3.24
  // C-ifDCSetup
  // MeNB UE X2AP ID Extension
  enb.enb_ue_x2ap_id_extension = NULL;

  // 6.2.3.9
  // C-ifDCSetup
  // Global eNB ID
  enb.global_enb_id = calloc(1, sizeof(*enb.global_enb_id));
  assert(enb.global_enb_id != NULL && "Memory exhausted");

  enb.global_enb_id->plmn_id = (plmn_t) {.mcc = 505, .mnc = 1, .mnc_digit_len = 2};

  enb.global_enb_id->type = MACRO_ENB_TYPE_ID;
  // rand()%END_ENB_TYPE_ID;

  switch (enb.global_enb_id->type)
  {
  case MACRO_ENB_TYPE_ID:
    enb.global_enb_id->macro_enb_id = (rand() % 2^20) + 0;
    break;
  
  case HOME_ENB_TYPE_ID:
    enb.global_enb_id->home_enb_id = (rand() % 2^28) + 0;
    break;

  case SHORT_MACRO_ENB_TYPE_ID:
    enb.global_enb_id->short_macro_enb_id = (rand() % 2^18) + 0;
    break;

  case LONG_MACRO_ENB_TYPE_ID:
    enb.global_enb_id->long_macro_enb_id = (rand() % 2^21) + 0;
    break;

  default:
    break;
  }

  return enb;
}

kpm_act_def_format_2_t fill_kpm_action_def_frm_2(void)
{
  kpm_act_def_format_2_t action_def_frm_2 = {0};

  // UE ID
  action_def_frm_2.ue_id.type = GNB_UE_ID; // rand()%END_UE_ID;

  switch (action_def_frm_2.ue_id.type)
  {
  case GNB_UE_ID:
    action_def_frm_2.ue_id.gnb = fill_gnb_data();
    break;

  case GNB_DU_UE_ID:
    action_def_frm_2.ue_id.gnb_du = fill_gnb_du_data();
    break;
  
  case GNB_CU_UP_UE_ID:
    action_def_frm_2.ue_id.gnb_cu_up = fill_gnb_cu_up_data();
    break;

  case NG_ENB_UE_ID:
    action_def_frm_2.ue_id.ng_enb = fill_ng_enb_data();
    break;

  case NG_ENB_DU_UE_ID:
    action_def_frm_2.ue_id.ng_enb_du = fill_ng_enb_du_data();
    break;

  case EN_GNB_UE_ID:
    action_def_frm_2.ue_id.en_gnb = fill_en_gnb_data();
    break;

  case ENB_UE_ID:
    action_def_frm_2.ue_id.enb = fill_enb_data();
    break;
  
  default:
    assert(false && "Unknown UE ID Type");
  }
  

  // Action Definition Format 1

  action_def_frm_2.action_def_format_1 = fill_kpm_action_def_frm_1();

  return action_def_frm_2;
}

kpm_act_def_t fill_kpm_action_def(void)
{
  kpm_act_def_t action_def = {0};

  action_def.type = FORMAT_1_ACTION_DEFINITION;  // rand()%END_ACTION_DEFINITION;

  switch (action_def.type)
  {
  case FORMAT_1_ACTION_DEFINITION:
    action_def.frm_1 = fill_kpm_action_def_frm_1();
    break;

  case FORMAT_2_ACTION_DEFINITION:
    action_def.frm_2 = fill_kpm_action_def_frm_2();
    break;
  
  // to be filled with other formats

  default:
    assert(false && "Unknown KPM Action Definition Format Type");
  }

  return action_def;
}







static
int64_t time_now_us(void)
{
  struct timespec tms;

  /* The C11 way */
  /* if (! timespec_get(&tms, TIME_UTC))  */

  /* POSIX.1-2008 way */
  if (clock_gettime(CLOCK_REALTIME,&tms)) {
    return -1;
  }
  /* seconds, multiplied with 1 million */
  int64_t micros = tms.tv_sec * 1000000;
  /* Add full microseconds */
  micros += tms.tv_nsec/1000;
  /* round up if necessary */
  if (tms.tv_nsec % 1000 >= 500) {
    ++micros;
  }
  return micros;
}



kpm_ric_ind_hdr_format_1_t fill_kpm_ind_hdr_frm_1(void)
{
  kpm_ric_ind_hdr_format_1_t hdr_frm_1 = {0};

  int64_t t = time_now_us();
  hdr_frm_1.collectStartTime = t / 1000000; // needs to be truncated to 32 bits to arrive to a resolution of seconds
  
  hdr_frm_1.fileformat_version = NULL;
  
  hdr_frm_1.sender_name = calloc(1, sizeof(byte_array_t));
  hdr_frm_1.sender_name->buf = calloc(strlen("My OAI-CU") + 1, sizeof(char));
  memcpy(hdr_frm_1.sender_name->buf, "My OAI-CU", strlen("My OAI-CU"));
  hdr_frm_1.sender_name->len = strlen("My OAI-CU");
  
  hdr_frm_1.sender_type = calloc(1, sizeof(byte_array_t));
  hdr_frm_1.sender_type->buf = calloc(strlen("CU") + 1, sizeof(char));
  memcpy(hdr_frm_1.sender_type->buf, "CU", strlen("CU"));
  hdr_frm_1.sender_type->len = strlen("CU");
  
  hdr_frm_1.vendor_name = calloc(1, sizeof(byte_array_t));
  hdr_frm_1.vendor_name->buf = calloc(strlen("OAI") + 1, sizeof(char));
  memcpy(hdr_frm_1.vendor_name->buf, "OAI", strlen("OAI"));
  hdr_frm_1.vendor_name->len = strlen("OAI");

  return hdr_frm_1;
}

kpm_ind_hdr_t fill_kpm_ind_hdr(void)
{
  kpm_ind_hdr_t hdr = {0};

  hdr.type = FORMAT_1_INDICATION_HEADER;
  hdr.kpm_ric_ind_hdr_format_1 = fill_kpm_ind_hdr_frm_1();

  return hdr;
}

kpm_ind_msg_format_1_t fill_kpm_ind_msg_frm_1(void)
{
  kpm_ind_msg_format_1_t msg_frm_1 = {0};
  
  // Measurement Data
  msg_frm_1.meas_data_lst_len = 1 + rand()%10;  // to check with random list length
  msg_frm_1.meas_data_lst = calloc(msg_frm_1.meas_data_lst_len, sizeof(*msg_frm_1.meas_data_lst));
  assert(msg_frm_1.meas_data_lst != NULL && "Memory exhausted" );
  
  for (size_t i = 0; i < msg_frm_1.meas_data_lst_len; i++)
  {
      // Incomplete Flag
      msg_frm_1.meas_data_lst[i].incomplete_flag = NULL;
      
      // Measurement Record
      msg_frm_1.meas_data_lst[i].meas_record_len = 1 + rand()%10;  // to check with random list length
      msg_frm_1.meas_data_lst[i].meas_record_lst = calloc(msg_frm_1.meas_data_lst[i].meas_record_len, sizeof(meas_record_lst_t));
      assert(msg_frm_1.meas_data_lst[i].meas_record_lst != NULL && "Memory exhausted" );
      
      for (size_t j = 0; j < msg_frm_1.meas_data_lst[i].meas_record_len; j++)
      {
          msg_frm_1.meas_data_lst[i].meas_record_lst[j].value = INTEGER_MEAS_VALUE;
          msg_frm_1.meas_data_lst[i].meas_record_lst[j].int_val = i+j;
      }
  }
  
  // Granularity Period - OPTIONAL
  msg_frm_1.gran_period_ms = NULL;
  
  // Measurement Information - OPTIONAL
  msg_frm_1.meas_info_lst_len = 1;
  msg_frm_1.meas_info_lst = calloc(msg_frm_1.meas_info_lst_len, sizeof(meas_info_format_1_lst_t));
  assert(msg_frm_1.meas_info_lst != NULL && "Memory exhausted" );
  
  for (size_t i = 0; i < msg_frm_1.meas_info_lst_len; i++)
  {
      // Measurement Type
      msg_frm_1.meas_info_lst[i].meas_type.type = NAME_MEAS_TYPE;
      char s[100];
      snprintf(s, 100, "RNTI %04x PrbDlUsage", (unsigned) (1111*i + 1111));
      msg_frm_1.meas_info_lst[i].meas_type.name.buf = calloc(strlen(s) + 1, sizeof(char));
      memcpy(msg_frm_1.meas_info_lst[i].meas_type.name.buf, s, strlen(s));
      msg_frm_1.meas_info_lst[i].meas_type.name.len = strlen(s);
      
      // Label Information
      msg_frm_1.meas_info_lst[i].label_info_lst_len = 2;
      msg_frm_1.meas_info_lst[i].label_info_lst = calloc(msg_frm_1.meas_info_lst[i].label_info_lst_len, sizeof(label_info_lst_t));
      assert(msg_frm_1.meas_info_lst[i].label_info_lst != NULL && "Memory exhausted" );
      
      for (size_t j = 0; j < msg_frm_1.meas_info_lst[i].label_info_lst_len; j++)
      {
          // msg_frm_1.meas_info_lst[i].label_info_lst[j].plmn_id = malloc(sizeof(plmn_t));
          // *msg_frm_1.meas_info_lst[i].label_info_lst[j].plmn_id = (plmn_t) {.mcc = 505, .mnc = 1, .mnc_digit_len = 2};
          msg_frm_1.meas_info_lst[i].label_info_lst[j].noLabel = malloc(sizeof(enum_value_e));
          *msg_frm_1.meas_info_lst[i].label_info_lst[j].noLabel = TRUE_ENUM_VALUE;
      }
  }


  return msg_frm_1;
}


kpm_ind_msg_t fill_kpm_ind_msg(void)
{
  kpm_ind_msg_t msg = {0};

  msg.type = FORMAT_1_INDICATION_MESSAGE;
  msg.frm_1 = fill_kpm_ind_msg_frm_1();

  return msg;
}
