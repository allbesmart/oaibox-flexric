#ifndef SM_PDCP_READ_WRITE_AGENT_H
#define SM_PDCP_READ_WRITE_AGENT_H

#include "../../../src/agent/e2_agent_api.h"

void read_pdcp_sm(sm_ag_if_rd_ind_t*);

void read_pdcp_setup_sm(sm_ag_if_rd_e2setup_t* data);

sm_ag_if_ans_t write_ctrl_pdcp_sm(sm_ag_if_wr_ctrl_t const* data);

#endif

