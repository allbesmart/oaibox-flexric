#include "sm_gtp.h"
#include "../../../test/rnd/fill_rnd_data_gtp.h"
#include <assert.h>

void read_gtp_sm(sm_ag_if_rd_ind_t* data)
{
  assert(data != NULL);
  assert(data->type == GTP_STATS_V0);

  fill_gtp_ind_data(&data->gtp);
}

void read_gtp_setup_sm(sm_ag_if_rd_e2setup_t* data)
{
  assert(data != NULL);
  assert(data->type == GTP_AGENT_IF_E2_SETUP_ANS_V0);

  assert(0 !=0 && "Not supported");
}

sm_ag_if_ans_t write_ctrl_gtp_sm(sm_ag_if_wr_ctrl_t const* src)
{
  assert(src != NULL);
  assert(src->type == GTP_CTRL_REQ_V0);


  assert(0 !=0 && "Not supported");
}

