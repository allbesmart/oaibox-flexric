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
  action_def_frm_1.meas_info_lst_len = 1;
  action_def_frm_1.meas_info_lst = calloc(action_def_frm_1.meas_info_lst_len, sizeof(meas_info_format_1_lst_t));
  assert(action_def_frm_1.meas_info_lst != NULL && "Memory exhausted" );
  
  for (size_t i = 0; i < action_def_frm_1.meas_info_lst_len; i++)
  {
      // Measurement Type
      action_def_frm_1.meas_info_lst[i].meas_type.type = NAME_MEAS_TYPE;
      action_def_frm_1.meas_info_lst[i].meas_type.name.buf = calloc(strlen("test") + 1, sizeof(char));
      memcpy(action_def_frm_1.meas_info_lst[i].meas_type.name.buf, "test", strlen("test"));
      action_def_frm_1.meas_info_lst[i].meas_type.name.len = strlen("test");
      // Label Information
      action_def_frm_1.meas_info_lst[i].label_info_lst_len = 1;
      action_def_frm_1.meas_info_lst[i].label_info_lst = calloc(action_def_frm_1.meas_info_lst[i].label_info_lst_len, sizeof(label_info_lst_t));
      assert(action_def_frm_1.meas_info_lst[i].label_info_lst != NULL && "Memory exhausted" );
      for (size_t j = 0; j < action_def_frm_1.meas_info_lst[i].label_info_lst_len; j++)
      {
          action_def_frm_1.meas_info_lst[i].label_info_lst[j].plmn_id = malloc(sizeof(plmn_t));
          *action_def_frm_1.meas_info_lst[i].label_info_lst[j].plmn_id = (plmn_t) {.mcc = 505, .mnc = 1, .mnc_digit_len = 2};
          // action_def_frm_1.meas_info_lst[i].label_info_lst[j].noLabel = malloc(sizeof(enum_value_e));
          // action_def_frm_1.meas_info_lst[i].label_info_lst[j].noLabel = TRUE_ENUM_VALUE;
      }
  }
  
  // Granularity Period
  action_def_frm_1.gran_period_ms = 1;
  
  // Cell Global ID - OPTIONAL
  action_def_frm_1.cell_global_id = NULL;
  
  // Measurement Bin Range - OPTIONAL
  action_def_frm_1.meas_bin_range_info_lst_len = 0;
  action_def_frm_1.meas_bin_info_lst = NULL;

  return action_def_frm_1;
}

kpm_act_def_t fill_kpm_action_def(void)
{
  kpm_act_def_t action_def = {0};

  action_def.type = FORMAT_1_ACTION_DEFINITION;
  action_def.frm_1 = fill_kpm_action_def_frm_1();

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
  msg_frm_1.meas_data_lst_len = 1;
  msg_frm_1.meas_data_lst = calloc(msg_frm_1.meas_data_lst_len, sizeof(*msg_frm_1.meas_data_lst));
  assert(msg_frm_1.meas_data_lst != NULL && "Memory exhausted" );
  
  for (size_t i = 0; i < msg_frm_1.meas_data_lst_len; i++)
  {
      // Incomplete Flag
      msg_frm_1.meas_data_lst[i].incomplete_flag = NULL;
      
      // Measurement Record
      msg_frm_1.meas_data_lst[i].meas_record_len = 1;
      msg_frm_1.meas_data_lst[i].meas_record_lst = calloc(msg_frm_1.meas_data_lst[i].meas_record_len, sizeof(meas_record_lst_t));
      assert(msg_frm_1.meas_data_lst[i].meas_record_lst != NULL && "Memory exhausted" );
      
      for (size_t j = 0; j < msg_frm_1.meas_data_lst[i].meas_record_len; j++)
      {
          msg_frm_1.meas_data_lst[i].meas_record_lst[j].no_value = INTEGER_MEAS_VALUE;
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
          msg_frm_1.meas_info_lst[i].label_info_lst[j].plmn_id = malloc(sizeof(plmn_t));
          *msg_frm_1.meas_info_lst[i].label_info_lst[j].plmn_id = (plmn_t) {.mcc = 505, .mnc = 1, .mnc_digit_len = 2};
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
