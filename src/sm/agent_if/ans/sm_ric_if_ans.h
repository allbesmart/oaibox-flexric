#ifndef SM_RIC_ANSWER_INTERFACE_H
#define SM_RIC_ANSWER_INTERFACE_H


#include "../../mac_sm/ie/mac_data_ie.h"
#include "../../rlc_sm/ie/rlc_data_ie.h"
#include "../../pdcp_sm/ie/pdcp_data_ie.h"
#include "../../slice_sm/ie/slice_data_ie.h"
#include "../../tc_sm/ie/tc_data_ie.h"
#include "../../gtp_sm/ie/gtp_data_ie.h"
#include "../../kpm_sm_v02.03/ie/kpm_data_ie.h"

typedef enum{
  MAC_RIC_IF_SUBS_ANS_V0, 
  RLC_RIC_IF_SUBS_ANS_V0, 
  PDCP_RIC_IF_SUBS_ANS_V0, 
  SLICE_RIC_IF_SUBS_ANS_V0, 
  TC_RIC_IF_SUBS_ANS_V0,
  GTP_RIC_IF_SUBS_ANS_V0,
  KPM_RIC_IF_SUBS_ANS_V0,

  SM_RIC_IF_SUBS_ANS_V0_END,
} sm_ric_if_ans_e;

typedef struct {

  sm_ric_if_ans_e type;

  union {
    mac_sub_data_t mac;
    rlc_sub_data_t rlc;
    pdcp_sub_data_t pdcp;
    slice_sub_data_t slice;
    tc_sub_data_t tc;
    gtp_sub_data_t gtp;
    kpm_ric_subscription_t kpm;
  };
    
} sm_ric_if_ans_t;

#endif
