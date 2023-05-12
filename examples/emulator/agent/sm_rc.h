#ifndef SM_RAN_CTRL_READ_WRITE_AGENT_H
#define SM_RAN_CTRL_READ_WRITE_AGENT_H

#include "../../../src/agent/e2_agent_api.h"

void read_rc_sm(sm_ag_if_rd_ind_t*);

void read_rc_setup_sm(sm_ag_if_rd_e2setup_t* data);

sm_ag_if_ans_t write_ctrl_rc_sm(sm_ag_if_wr_ctrl_t const* data);

sm_ag_if_ans_t write_subs_rc_sm(sm_ag_if_wr_subs_t const* src);

#endif

