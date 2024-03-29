#ifndef SM_SLICE_READ_WRITE_AGENT_H
#define SM_SLICE_READ_WRITE_AGENT_H

#include "../../../src/agent/e2_agent_api.h"

void init_slice_sm(void);

void free_slice_sm(void);

bool read_slice_sm(void*);

void read_slice_setup_sm(void* data);

sm_ag_if_ans_t write_ctrl_slice_sm(void const* data);

#endif

