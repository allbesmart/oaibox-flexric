#include "sm_mac.h"
#include "../../../test/rnd/fill_rnd_data_mac.h"
#include <assert.h>

void read_mac_sm(sm_ag_if_rd_ind_t* data)
{
  assert(data != NULL);
  assert(data->type == MAC_STATS_V0);

  fill_mac_ind_data(&data->mac);
}

void read_mac_setup_sm(sm_ag_if_rd_e2setup_t* data)
{
  assert(data != NULL);
  assert(data->type == MAC_AGENT_IF_E2_SETUP_ANS_V0 );

  assert(0 !=0 && "Not supported");
}

sm_ag_if_ans_t write_ctrl_mac_sm(sm_ag_if_wr_ctrl_t const* data)
{
  assert(data != NULL);
  assert(data->type == MAC_CTRL_REQ_V0);

  assert(0 !=0 && "Not supported");
}

