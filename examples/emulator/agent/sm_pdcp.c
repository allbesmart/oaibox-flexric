#include "sm_pdcp.h"
#include "../../../test/rnd/fill_rnd_data_pdcp.h"
#include <assert.h>

void init_pdcp_sm(void)
{
  // No allocation needed
}

void free_pdcp_sm(void)
{
  // No allocation needed
}

bool read_pdcp_sm(void* data)
{
  assert(data != NULL);
  //assert(data->type == PDCP_STATS_V0);

  pdcp_ind_data_t* pdcp = (pdcp_ind_data_t*)data;
  fill_pdcp_ind_data(pdcp);
  return true;
}

void read_pdcp_setup_sm(void* data)
{
  assert(data != NULL);
//  assert(data->type == PDCP_AGENT_IF_E2_SETUP_ANS_V0 );

  assert(0 !=0 && "Not supported");
}

sm_ag_if_ans_t write_ctrl_pdcp_sm(void const* data)
{
  assert(data != NULL);
//  assert(data->type == PDCP_CTRL_REQ_V0 );
  assert(0 !=0 && "Not supported");
  sm_ag_if_ans_t ans = {0};
  return ans;
}


