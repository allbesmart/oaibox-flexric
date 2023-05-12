#include "sm_rlc.h"
#include "../../../test/rnd/fill_rnd_data_rlc.h"

void read_rlc_sm(sm_ag_if_rd_ind_t* data)
{
  assert(data != NULL);
  assert(data->type ==  RLC_STATS_V0);
  fill_rlc_ind_data(&data->rlc);
}

void read_rlc_setup_sm(sm_ag_if_rd_e2setup_t* data)
{
  assert(data != NULL);
  assert(data->type == RLC_AGENT_IF_E2_SETUP_ANS_V0 );

  assert(0 !=0 && "Not supported");
}

sm_ag_if_ans_t write_ctrl_rlc_sm(sm_ag_if_wr_ctrl_t const* data)
{
  (void)data;
  assert(0!=0 && "Not supported");
}

