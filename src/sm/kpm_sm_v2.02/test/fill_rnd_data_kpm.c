#include "fill_rnd_data_kpm.h"

#include <assert.h>
#include <stdlib.h>

kpm_event_trigger_def_t fill_kpm_event_trigger_def(void)
{
  kpm_event_trigger_def_t dst = {0};

  dst.type = rand()%END_FORMAT_RIC_EVENT_TRIGGER;

  if(dst.type == FORMAT_1_RIC_EVENT_TRIGGER  ){
    // Normally the period is not free, need to check in the specs
    dst.kpm_ric_event_trigger_format_1.report_period_ms = rand()%1000;
  } else {
    assert(0 != 0 && "unknown type");
  }

  return dst;
}
