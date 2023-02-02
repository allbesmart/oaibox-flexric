#include <assert.h>

#include "fill_kpm_event_trigger_frm_1.h"

void fill_kpm_event_trigger_frm_1(kpm_ric_event_trigger_format_1_t * event_trigger, const char* cmd)
{
    assert(event_trigger != NULL);
    assert(cmd != NULL); 

    const int max_str_sz = 10;
    if(strncmp(cmd, "1_ms", max_str_sz) == 0 ){
      event_trigger->report_period_ms = 1;
    } else if (strncmp(cmd, "2_ms", max_str_sz) == 0 ) {
      event_trigger->report_period_ms = 2;
    } else if (strncmp(cmd, "5_ms", max_str_sz) == 0 ) {
      event_trigger->report_period_ms = 5;
    } else if (strncmp(cmd, "10_ms", max_str_sz) == 0 ) {
      event_trigger->report_period_ms = 10;
    } else if (strncmp(cmd, "100_ms", max_str_sz) == 0 ) {
      event_trigger->report_period_ms = 100;
    } else if (strncmp(cmd, "1000_ms", max_str_sz) == 0 ) {
      event_trigger->report_period_ms = 1000;
    } else {
      assert(0 != 0 && "Invalid input");
    }

}