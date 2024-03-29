#ifndef SM_AMC_READ_WRITE_AGENT_H
#define SM_AMC_READ_WRITE_AGENT_H

#include "../../../src/agent/e2_agent_api.h"

void init_mac_sm(void);

void free_mac_sm(void);

bool read_mac_sm(void*);

void read_mac_setup_sm(void*);

sm_ag_if_ans_t write_ctrl_mac_sm(void const*);

#endif

