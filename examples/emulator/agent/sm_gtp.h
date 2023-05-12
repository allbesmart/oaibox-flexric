#ifndef SM_GTP_READ_WRITE_AGENT_H
#define SM_GTP_READ_WRITE_AGENT_H

#include "../../../src/agent/e2_agent_api.h"

void read_gtp_sm(sm_ag_if_rd_ind_t*);

void read_gtp_setup_sm(sm_ag_if_rd_e2setup_t*);

sm_ag_if_ans_t write_ctrl_gtp_sm(sm_ag_if_wr_ctrl_t const*);

#endif

